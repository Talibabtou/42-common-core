#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Webserv.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "utils.h"

// Constructors & Destructor

HttpRequest::HttpRequest() : AHttpBuilder()
{
	this->_path = "";
	this->_type = "";
	this->_code = "";
	this->_contentType = "";
	this->_contentLength = -1;
	this->_connection = "";
	this->_etag = "";
	this->_lastModified = "";
	this->_cacheControl = "";
	this->_host = "";
	this->_accept = "";
	this->_isCgi = false;
	this->_server_name = "";
	this->_server = NULL;
}

HttpRequest::HttpRequest(Client& client) : AHttpBuilder()
{
	this->_path = "";
	this->_type = "";
	this->_code = "";
	this->_contentType = "";
	this->_contentLength = -1;
	this->_connection = "";
	this->_etag = "";
	this->_lastModified = "";
	this->_cacheControl = "";
	this->_accept = "";
	this->_isCgi = false;
	this->_server = client.getServer();
	this->_server_name = _server->getServerName();
	this->_body = client.getRequest();
}

HttpRequest::HttpRequest(const HttpRequest& other) : AHttpBuilder(other) { *this = other; }

HttpRequest& HttpRequest::operator=(const HttpRequest& other) {
	if (this != &other) {
		this->_path = other._path;
		this->_type = other._type;
		this->_code = other._code;
		this->_contentType = other._contentType;
		this->_contentLength = other._contentLength;
		this->_connection = other._connection;
		this->_etag = other._etag;
		this->_lastModified = other._lastModified;
		this->_cacheControl = other._cacheControl;
		this->_accept = other._accept;
		this->_isCgi = other._isCgi;
		this->_server = other._server;
		this->_server_name = other._server_name;
		this->_body = other._body;
	}
	return *this;
}

HttpRequest::~HttpRequest() throw() {}

// Parsing

void HttpRequest::validateRequestComponents(const std::string& method, const std::string& path, const std::string& version)
{
	if (method.empty() || path.empty() || version.empty())
		throw AHttpBuilder::HttpException("400");
	if (method != "GET" && method != "POST" && method != "DELETE")
		throw AHttpBuilder::HttpException("405");
	if (version != "HTTP/1.1")
		throw AHttpBuilder::HttpException("505");
}

std::string HttpRequest::normalizePath(const std::string& path)
{
	std::string normalizedPath = path;
	while (normalizedPath.length() > 1 && normalizedPath[normalizedPath.length() - 1] == '/')
		normalizedPath = normalizedPath.substr(0, normalizedPath.length() - 1);
	return normalizedPath;
}

bool HttpRequest::validateLocationAccess(const std::string& normalizedPath, const t_config& config)
{
	if (normalizedPath == "/" || normalizedPath.empty())
		return true;
	for (std::map<std::string, t_location>::const_iterator it = config.locations.begin();
		 it != config.locations.end(); ++it) {
		std::string locationPath = normalizePath(it->first);
		if (normalizedPath == locationPath ||
			normalizedPath.find(locationPath + "/") == 0 ||
			locationPath == "/") {
			return true;
		}
	}
	return false;
}

std::string HttpRequest::urlDecode(const std::string& encoded)
{
	std::string decoded;
	std::string::size_type i;

	for (i = 0; i < encoded.length(); ++i) {
		if (encoded[i] == '%') {
			if (i + 2 < encoded.length()) {
				std::string hex = encoded.substr(i + 1, 2);
				int value;
				std::istringstream iss(hex);
				iss >> std::hex >> value;
				decoded += static_cast<char>(value);
				i += 2;
			}
		} else if (encoded[i] == '+')
			decoded += ' ';
		else
			decoded += encoded[i];
	}
	return decoded;
}

void HttpRequest::parseQueryString(const std::string& queryString)
{
	std::string key, value;
	std::istringstream iss(queryString);

	while (std::getline(iss, key, '&')) {
		size_t equalPos = key.find('=');
		if (equalPos != std::string::npos) {
			value = key.substr(equalPos + 1);
			key = key.substr(0, equalPos);
			value = urlDecode(value);
			key = urlDecode(key);
			if (value.find('/') != std::string::npos)
				throw AHttpBuilder::HttpException("403");
			this->_cgi_args[key] = value;
		}
	}
}

void HttpRequest::parseFormData(const std::string& boundary)
{
	std::string delimiter = "--" + boundary;
	size_t pos = 0;
	std::string body = this->getBody();

	while ((pos = body.find(delimiter)) != std::string::npos) {
		size_t headerEnd = body.find("\r\n\r\n", pos);
		if (headerEnd == std::string::npos)
			break;
		std::string header = body.substr(pos + delimiter.length(), headerEnd - (pos + delimiter.length()));
		size_t filenamePos = header.find("filename=\"");
		if (filenamePos != std::string::npos) {
			filenamePos += 10;
			size_t filenameEnd = header.find("\"", filenamePos);
			if (filenameEnd != std::string::npos) {
				std::string filename = header.substr(filenamePos, filenameEnd - filenamePos);
				filename = urlDecode(filename);
				if (getFileExtension(filename) == "png")
					throw AHttpBuilder::HttpException("415");
			}
		}
		size_t namePos = header.find("name=\"");
		if (namePos != std::string::npos) {
			namePos += 6;
			size_t nameEnd = header.find("\"", namePos);
			if (nameEnd != std::string::npos) {
				std::string name = header.substr(namePos, nameEnd - namePos);
				name = urlDecode(name);
				size_t contentStart = headerEnd + 4;
				size_t contentEnd = body.find(delimiter, contentStart);
				if (contentEnd == std::string::npos) break;
				std::string content = body.substr(contentStart, contentEnd - contentStart - 2);
				this->_cgi_args[name] = content;
			}
		}
		body = body.substr(pos + 1);
	}
}

void HttpRequest::processPath(const std::string& path)
{
	size_t queryPos = path.find('?');
	std::string basePath = (queryPos != std::string::npos) ? path.substr(0, queryPos) : path;
	std::string queryParams = (queryPos != std::string::npos) ? path.substr(queryPos + 1) : "";
	const t_config& config = this->getServer()->getConfig();
	std::string matchedLocation;
	t_location locationConfig;

	if (basePath == "/" || basePath.empty()) {
		std::map<std::string, t_location>::const_iterator rootIt = config.locations.find("/");
		if (rootIt != config.locations.end()) {
			matchedLocation = "/";
			locationConfig = rootIt->second;
		}
	} else {
		for (std::map<std::string, t_location>::const_iterator it = config.locations.begin();
			 it != config.locations.end(); ++it) {
			if (basePath.find(it->first) == 0 &&
				(matchedLocation.empty() || it->first.length() > matchedLocation.length())) {
				matchedLocation = it->first;
				locationConfig = it->second;
			}
		}
	}
	if (matchedLocation.empty()) {
		throw AHttpBuilder::HttpException("404");
	}
	bool methodAllowed = false;
	for (std::vector<std::string>::const_iterator it = locationConfig.allowed_methods.begin();
		 it != locationConfig.allowed_methods.end(); ++it) {
		if (*it == this->_type) {
			methodAllowed = true;
			break;
		}
	}
	if (this->_type == "GET" && basePath.find("delete.sh") != std::string::npos) {
		size_t filenamePos = path.find("filename=");
		if (filenamePos != std::string::npos) {
			std::string filename = path.substr(filenamePos + 9);
			if (filename.find('/') != std::string::npos) {
				throw AHttpBuilder::HttpException("400");
			}
		}

		bool deleteAllowed = false;
		std::map<std::string, t_location>::const_iterator cgiBin = config.locations.find("/cgi-bin/");
		if (cgiBin != config.locations.end()) {
			for (std::vector<std::string>::const_iterator it = cgiBin->second.allowed_methods.begin();
				 it != cgiBin->second.allowed_methods.end(); ++it) {
				if (*it == "DELETE") {
					deleteAllowed = true;
					break;
				}
			}
		}
		methodAllowed = deleteAllowed;
	}
	if (!methodAllowed) {
		throw AHttpBuilder::HttpException("405");
	}

	buildFinalPath(matchedLocation, basePath, locationConfig, config, queryParams);
	if (this->_isCgi) {
		if (!queryParams.empty()) {
			parseQueryString(queryParams);
		} else if (this->_contentType.find("multipart/form-data") != std::string::npos) {
			size_t boundaryPos = this->_contentType.find("boundary=");
			if (boundaryPos != std::string::npos) {
				std::string boundary = this->_contentType.substr(boundaryPos + 9);
				parseFormData(boundary);
			}
		}
	}
}

void HttpRequest::buildFinalPath(const std::string& matchedLocation, const std::string& basePath,
								const t_location& locationConfig, const t_config& config,
								const std::string& queryParams)
{
	this->_isCgi = (matchedLocation == "/cgi-bin/");

	if (basePath == "/" || basePath.empty()) {
		std::string root = locationConfig.root;
		if (!root.empty() && root[root.length() - 1] == '/')
			root = root.substr(0, root.length() - 1);
		this->_path = root + "/" +
					 (locationConfig.index.empty() ? config.index : locationConfig.index);
	} else {
		std::string root = locationConfig.root;
		if (!root.empty() && root[root.length() - 1] == '/')
			root = root.substr(0, root.length() - 1);
		std::string relativePath = basePath.substr(matchedLocation.length());
		if (!relativePath.empty() && relativePath[0] != '/')
			relativePath = "/" + relativePath;
		if (getFileExtension(relativePath).empty()) {
		for (std::map<std::string, t_location>::const_iterator it = _server->getConfig().locations.begin();
			 it != _server->getConfig().locations.end(); ++it) {
			if (it->first == relativePath || normalizePath(it->first) == normalizePath(relativePath)) {
				this->_path = it->second.root +  it->second.index;
				break ;
				}
			}
		}
		else
			this->_path = root + relativePath;
	}
	if (this->_isCgi && !queryParams.empty())
		this->_body = queryParams.substr(1);
}

void HttpRequest::parseRequestLine(const std::string& line)
{
	std::istringstream iss(line);
	std::string method, path, version;
	iss >> method >> path >> version;

	validateRequestComponents(method, path, version);

	const t_config& config = this->getServer()->getConfig();
	std::string normalizedPath = normalizePath(path);

	std::string ext = getFileExtension(path);
	if (!validateLocationAccess(normalizedPath, config))
		throw AHttpBuilder::HttpException("403");
	this->_type = method;
	processPath(path);
	this->_version = version;
}

void HttpRequest::parseHeader(const std::string& line)
{
	size_t separator = line.find(':');
	if (separator == std::string::npos)
		return;

	std::string key = line.substr(0, separator);
	std::string value = line.substr(separator + 1);
	value.erase(0, value.find_first_not_of(" "));
	value.erase(value.find_last_not_of(" ") + 1);

	if (key == "Host")
		this->_host = value;
	else if (key == "Connection")
		this->_connection = value;
	else if (key == "Content-Type")
		this->_contentType = value;
	else if (key == "Content-Length")
		this->_contentLength = std::atoi(value.c_str());
	else if (key == "Accept")
		this->_accept = value;
	else if (key == "If-None-Match")
		this->_etag = value;
	else if (key == "If-Modified-Since")
		this->_lastModified = value;
	else if (key == "Cache-Control")
		this->_cacheControl = value;
	else if (key == "Cookie")
		this->_cookie = value;
}

void HttpRequest::buildHeader()
{
	try {
		if (_body.empty() || _body.find_first_not_of(" \t\n\r") == std::string::npos)
			throw AHttpBuilder::HttpException("400");

		std::istringstream request_stream(_body);
		std::string line;
		bool first_line = true;
		std::string request_body;
		bool headers_done = false;

		while (std::getline(request_stream, line)) {
			if (!line.empty() && line[line.length()-1] == '\r')
				line = line.substr(0, line.length()-1);
			if (!headers_done) {
				if (line.empty()) {
					headers_done = true;
					continue;
				}
				if (first_line) {
					parseRequestLine(line);
					first_line = false;
				}
				else
					parseHeader(line);
			} else {
				request_body += line;
				if (!request_stream.eof())
					request_body += "\n";
			}
		}
		if (_type == "POST" && _contentType.find("multipart/form-data") != std::string::npos) {
			size_t boundaryPos = _contentType.find("boundary=");
			if (boundaryPos != std::string::npos) {
				std::string boundary = _contentType.substr(boundaryPos + 9);
				parseFormData(boundary);
			}
		}
		if (_type.empty() || _path.empty())
			throw AHttpBuilder::HttpException("400");
		if (_type == "POST")
			_body = request_body;
		else
			_body = "";
		logRequestDetails();
	}
	catch (const AHttpBuilder::HttpException& e) {
		std::cout << "HttpException: " << e.getCode() << std::endl;
		throw AHttpBuilder::HttpException(e.getCode());
	}
	catch (const std::exception& e) {
		logMessage(ERROR, "HttpRequest", "Unexpected error: " + std::string(e.what()), this->_server_name);
		throw AHttpBuilder::HttpException("500");
	}
}

// Getters & setters

const std::string& HttpRequest::getHost() const { return this->_host; }
const std::string& HttpRequest::getServerName() const { return this->_server_name; }
const Server* HttpRequest::getServer() const { return this->_server; }
const std::string& HttpRequest::getType() const { return this->_type; }
const std::string& HttpRequest::getPath() const { return this->_path; }
std::string HttpRequest::getVersion() const { return this->_version; }
bool HttpRequest::getIsCgi() const { return this->_isCgi; }
const std::string& HttpRequest::getAccept() const { return this->_accept; }
const std::map<std::string, std::string>& HttpRequest::getCgiArgs() const { return this->_cgi_args; }

const std::string& HttpRequest::getConnection() const
{
	if (this->_connection.empty()) {
		static const std::string keepAlive = "keep-alive";
		return keepAlive;
	}
	return this->_connection;
}

void HttpRequest::setBody(const std::string& raw_request) { this->_body = raw_request; }

// Utils

void HttpRequest::logRequestDetails() const
{
	std::string server_name = this->_server_name.empty() ? "unknown" : this->_server_name;
	std::stringstream details;
	const size_t MAX_BODY_LENGTH = 100;
	std::string truncatedBody;

	if (!this->_body.empty()) {
		truncatedBody = this->_body.substr(0, MAX_BODY_LENGTH);
		if (this->_body.length() > MAX_BODY_LENGTH) {
			truncatedBody += "... [truncated]";
		}
	} else {
		truncatedBody = "not set";
	}

	details << "=== Request Details ===\n"
		<< "Method: '" << this->_type << "'\n"
		<< "Path: '" << this->_path << "'\n"
		<< "Host: '" << (this->_host.empty() ? "not set" : this->_host) << "'\n"
		<< "Connection: '" << (this->_connection.empty() ? "not set" : this->_connection) << "'\n"
		<< "Content-Type: '" << (this->_contentType.empty() ? "not set" : this->_contentType) << "'\n"
		<< "Content-Length: " << (this->_contentLength == -1 ? "not set" : numberToString(this->_contentLength)) << "\n"
		<< "ETag: '" << (this->_etag.empty() ? "not set" : this->_etag) << "'\n"
		<< "Last-Modified: '" << (this->_lastModified.empty() ? "not set" : this->_lastModified) << "'\n"
		<< "Cache-Control: '" << (this->_cacheControl.empty() ? "not set" : this->_cacheControl) << "'\n"
		<< "Accept: '" << (this->_accept.empty() ? "not set" : this->_accept) << "'\n"
		<< "Is CGI: " << (this->_isCgi ? "yes" : "no");
	if (!this->_cgi_args.empty()) {
		details << "\nCGI Arguments:";
		for (std::map<std::string, std::string>::const_iterator it = this->_cgi_args.begin();
			 it != this->_cgi_args.end(); ++it) {
			details << "\n  '" << it->first << "' = '" << it->second << "'";
		}
	}
	details << "\nBody (truncated): '" << truncatedBody << "'";
	details << "\n=== End Request Details ===";
	logMessage(DEBUG, "HttpRequest", details.str(), server_name);
}
