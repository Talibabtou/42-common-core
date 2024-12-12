#include "Webserv.hpp"
#include "HttpResponse.hpp"
#include "utils.h"

std::map<std::string, std::string> HttpResponse::_mimeTypes;

// Constructors & Destructor

HttpResponse::HttpResponse(void) : AHttpBuilder()
{
	this->_isCgi = false;
	this->_path = "";
	this->_type = "";
	this->_code = "";
	this->_contentType = "";
	this->_contentLength = -1;
	this->_message = "";
	this->_connection = "";
	this->_server_name = "";
	this->_date = "";
	this->_body = "";
	this->_etag = "";
	this->_lastModified = "";
	this->_cacheControl = "";
	this->_host = "";
	this->_cookie = "";
	this->_accept = "";
	this->_cgi_args = std::map<std::string, std::string>();
	this->_response = "";
}
HttpResponse::HttpResponse(const HttpRequest& request) : AHttpBuilder()
{
	this->_request = request;
	this->_isCgi = request.getIsCgi();
	this->_path = request.getPath();
	if (this->_isCgi && this->_path.find("delete") != std::string::npos) {
		this->_type = "DELETE";
		this->_connection = "close";
	}
	else
		this->_type = request.getType();
	this->_code = request.getCode();
	this->_contentType = "";
	this->_contentLength = -1;
	this->_body = "";
	if (this->_type == "POST") {
		initializeEnviron(request);
		this->_body = request.getBody();
		this->_contentLength = request.getContentLength();
	}
	if (request.getConnection().empty())
		this->_connection = "keep-alive";
	else if (this->_connection.empty())
		this->_connection = request.getConnection();
	this->_server_name = request.getServerName();
	this->setDate();
	this->_etag = request.getEtag();
	this->_lastModified = request.getLastModified();
	this->_cacheControl = request.getCacheControl();
	this->_cookie = request.getCookie();
	this->_accept = request.getAccept();
	this->_cgi_args = request.getCgiArgs();
	this->_response = "";
}

HttpResponse::HttpResponse(std::string error_code, const HttpRequest& request) : AHttpBuilder()
{
	std::stringstream ss;
	ss << error_code;
	int code;
	ss >> code;
	this->_request = request;
	this->_code = error_code;
	this->_isCgi = false;
	this->_path = this->_request.getPath();
	this->_type = "";
	if (getStatusMessages().find(this->_code) == getStatusMessages().end())
		this->_code = "500";
	this->_message = this->getStatusMessages().at(this->_code);
	this->_contentType = getMimeTypes().at("html");
	this->_contentLength = -1;
	if (code >= 500 || code == 400 || code == 413)
		this->_connection = "close";
	else
		this->_connection = "keep-alive";
	this->_server_name = request.getServerName();
	this->setDate();
	this->_body = "";
	this->_etag = "";
	this->_lastModified = "";
	this->_cacheControl = "";
	this->_cookie = "";
	this->_accept = request.getAccept();
	this->_cgi_args = std::map<std::string, std::string>();
	this->_response = "";
}

HttpResponse::HttpResponse(std::string error_code, Server* server) : AHttpBuilder()
{
	std::stringstream ss;
	ss << error_code;
	int code;
	ss >> code;
	this->_code = error_code;
	this->_isCgi = false;
	this->_path = server->getConfig().path;
	this->_type = "";
	if (getStatusMessages().find(this->_code) == getStatusMessages().end())
		this->_code = "500";
	this->_message = this->getStatusMessages().at(this->_code);
	this->_contentType = getMimeTypes().at("html");
	this->_contentLength = -1;
	if (code >= 500 || code == 400 || code == 413)
		this->_connection = "close";
	else
		this->_connection = "keep-alive";
	this->_server_name = server->getServerName();
	this->setDate();
	this->_body = "";
	this->_etag = "";
	this->_lastModified = "";
	this->_cacheControl = "";
	this->_cookie = "";
	this->_accept = "";
	this->_cgi_args = std::map<std::string, std::string>();
	this->_response = "";
}



HttpResponse::HttpResponse(const HttpResponse& other) : AHttpBuilder(other)
{
	this->_request = other._request;
	this->_isCgi = false;
	this->_path = other._path;
	this->_type = other._type;
	this->_code = other._code;
	this->_contentType = other._contentType;
	this->_contentLength = other._contentLength;
	this->_message = other._message;
	this->_connection = other._connection;
	this->_server_name = other._server_name;
	this->_date = other._date;
	this->_body = other._body;
	this->_etag = other._etag;
	this->_lastModified = other._lastModified;
	this->_cacheControl = other._cacheControl;
	this->_cookie = other._cookie;
	this->_accept = other._accept;
	this->_cgi_args = other._cgi_args;
	this->_response = other._response;
}

HttpResponse& HttpResponse::operator=(const HttpResponse &other)
{
	if (this != &other) {
		this->_request = other._request;
		this->_isCgi = other._isCgi;
		this->_path = other._path;
		this->_type = other._type;
		this->_code = other._code;
		this->_contentType = other._contentType;
		this->_contentLength = other._contentLength;
		this->_message = other._message;
		this->_connection = other._connection;
		this->_server_name = other._server_name;
		this->_date = other._date;
		this->_body = other._body;
		this->_etag = other._etag;
		this->_lastModified = other._lastModified;
		this->_cacheControl = other._cacheControl;
		this->_cookie = other._cookie;
		this->_accept = other._accept;
		this->_cgi_args = other._cgi_args;
		this->_response = other._response;
	}
	return *this;
}


HttpResponse::~HttpResponse() throw() {}

// Initialization

void HttpResponse::initializeMimeTypes(void)
{
	_mimeTypes["jar"] = "application/java-archive";
	_mimeTypes["bin"] = "application/octet-stream";
	_mimeTypes["ogx"] = "application/ogg";
	_mimeTypes["pdf"] = "application/pdf";
	_mimeTypes["xhtml"] = "application/xhtml+xml";
	_mimeTypes["json"] = "application/json";
	_mimeTypes["xml"] = "application/xml";
	_mimeTypes["zip"] = "application/zip";

	_mimeTypes["mp3"] = "audio/mpeg";
	_mimeTypes["wav"] = "audio/wav";

	_mimeTypes["gif"] = "image/gif";
	_mimeTypes["webp"] = "image/webp";
	_mimeTypes["jpeg"] = "image/jpeg";
	_mimeTypes["jpg"] = "image/jpeg";
	_mimeTypes["png"] = "image/png";
	_mimeTypes["tiff"] = "image/tiff";
	_mimeTypes["ico"] = "image/x-icon";
	_mimeTypes["svg"] = "image/svg+xml";

	_mimeTypes["css"] = "text/css";
	_mimeTypes["csv"] = "text/csv";
	_mimeTypes["html"] = "text/html";
	_mimeTypes["js"] = "text/javascript";
	_mimeTypes["txt"] = "text/plain";

	_mimeTypes["mpeg"] = "video/mpeg";
	_mimeTypes["mp4"] = "video/mp4";
	_mimeTypes["mov"] = "video/quicktime";
	_mimeTypes["wmv"] = "video/x-ms-wmv";
	_mimeTypes["avi"] = "video/x-msvideo";
	_mimeTypes["flv"] = "video/x-flv";
	_mimeTypes["webm"] = "video/webm";
}

void HttpResponse::initializeEnviron(const HttpRequest &request)
{
	std::stringstream ss;
	ss << request.getContentLength();

	_envStrings[0] = "REQUEST_METHOD=POST";
	_envStrings[1] = "CONTENT_LENGTH=" + ss.str();
	_envStrings[2] = "CONTENT_TYPE=" + request.getContentType();
	_environ[0] = (char*)_envStrings[0].c_str();
	_environ[1] = (char*)_envStrings[1].c_str();
	_environ[2] = (char*)_envStrings[2].c_str();
	_environ[3] = NULL;
}

// Build methods

void HttpResponse::buildHeader()
{
	if (this->_code == "") {
		if (this->_type == "GET") {
			if (!this->_isCgi)
				this->GetFileHandler();
			else
				this->GetCgiHandler();
		} else if (this->_type == "POST") {
			this->PostHandler();
		} else if (this->_type == "DELETE") {
			this->DelHandler();
		}
	} else {
		this->setErrorResponse();
	}
}

void HttpResponse::GetFileHandler()
{
	try {
		if (!this->_body.empty())
			throw AHttpBuilder::HttpException("400");
		this->fileHandler();
		this->setResponse();
	}
		catch (const HttpException& e) {
		logMessage(ERROR, "HttpResponse", "HTTP Error " +  e.getCode() + ": " + e.what(), this->_server_name);
		HttpResponse errorResponse = HttpResponse(e.getCode(), this->_request);
		*this = errorResponse;
		this->setErrorResponse();
		return ;
	}
}

void HttpResponse::GetCgiHandler()
{
	try {
		size_t lastSlashPos = this->_path.find_last_of('/');
		this->setExecArgs();
		this->cgiHandler(this->_exec_args[0], this->_exec_args);
		std::string tmp_path = this->_path.substr(0, lastSlashPos + 1) + "tmp.html";
		this->_path = tmp_path;
		this->fileHandler();
		if (this->_code <= "300")
			this->setResponse();
	}
		catch (const HttpException& e) {
		logMessage(ERROR, "HttpResponse", "HTTP Error " +  e.getCode() + ": " + e.what(), this->_server_name);
		HttpResponse errorResponse = HttpResponse(e.getCode(), this->_request);
		*this = errorResponse;
		this->setErrorResponse();
	}
}

void HttpResponse::fileHandler()
{
	std::ifstream file(this->_path.c_str(), std::ios::binary);
	struct stat fileInfo;
	if (!file.is_open() || stat(this->_path.c_str(), &fileInfo) != 0) {
		if (errno == EACCES)
			throw AHttpBuilder::HttpException("403");
		else if (errno == ENOENT)
			throw AHttpBuilder::HttpException("404");
		else
			throw AHttpBuilder::HttpException("404");
	}
	std::ostringstream buffer(std::ios::binary);
	std::stringstream ss;
	std::string hash;
	std::string lastModified;
	buffer << file.rdbuf();
	ss << std::hex << djb2Hash(buffer.str());
	hash = "\"" + ss.str() + "\"";
	lastModified = getFileModification(fileInfo);
	if (!this->needCache() || (this->_etag.empty() && this->_lastModified.empty())
			|| hash != this->_etag || compareTime(this->_lastModified, lastModified)) {
		setCode("200");
		setMessage(getStatusMessages().at(this->_code));
		setBody(buffer.str());
		setEtag(hash);
		setContentLength(this->_body.size());
		int lastSlashPos = this->_path.find_last_of('/');
		std::string file = this->_path.substr(lastSlashPos + 1);
		if (file.find(".") == std::string::npos)
			throw AHttpBuilder::HttpException("404");
		else if (getMimeTypes().find(getFileExtension(this->_path)) == getMimeTypes().end())
			throw AHttpBuilder::HttpException("415");
		setContentType(getMimeTypes().at(getFileExtension(this->_path)));
		if (!CheckAccept(this->_accept, this->_contentType))
			throw AHttpBuilder::HttpException("406");
		setLastModified(lastModified);
	} else {
		setCode("304");
		setMessage(getStatusMessages().at(this->_code));
		setBody("");
		setContentLength(0);
	}
}

void HttpResponse::PostHandler()
{
	try {
		if (!this->_isCgi){
			size_t rootPos = findWebsiteRoot(this->_path, '/');
			std::string cgiDefault = this->_path.substr(0, rootPos) + CGI_DEFAULT;
			this->_path = cgiDefault;
		}
		this->setExecArgs();
		this->cgiHandler(this->_exec_args[0], this->_exec_args);
		size_t lastSlashPos = this->_path.find_last_of('/');
		std::string tmp_path = this->_path.substr(0, lastSlashPos + 1) + "tmp.html";
		this->_path = tmp_path;
		this->fileHandler();
		this->setResponse();
		}
		catch (const HttpException& e) {
		logMessage(ERROR, "HttpResponse", "HTTP Error " +  e.getCode() + ": " + e.what(), this->_server_name);
		HttpResponse errorResponse = HttpResponse(e.getCode(), this->_request);
		*this = errorResponse;
		this->setErrorResponse();
		return ;
	}
}

void HttpResponse::DelHandler()
{
	this->setExecArgs();
	try {
		checkDeletePermission(this->_exec_strings[0], this->_path);
		size_t rootPos = findWebsiteRoot(this->_path, '/');
		std::string rootFolder = this->_path.substr(0, rootPos) + "/assets/uploads/";
		if (!checkWritePermission(rootFolder)){
			throw AHttpBuilder::HttpException("403");
		}
	}
	catch (const HttpException& e) {
		logMessage(ERROR, "HttpResponse", "HTTP Error " +  e.getCode() + ": " + e.what(), this->_server_name);
		HttpResponse errorResponse = HttpResponse(e.getCode(), this->_request);
		*this = errorResponse;
		this->setErrorResponse();
		return;
	}
	try {
		this->cgiHandler(this->_exec_args[0], this->_exec_args);

		if (this->_request.getType() == "GET") {
			size_t lastSlashPos = this->_path.find_last_of('/');
			std::string gallery_path = this->_path.substr(0, lastSlashPos + 1) + "display_gallery.py";
			this->_path = gallery_path;
			this->setExecArgs();
			this->cgiHandler(this->_exec_args[0], this->_exec_args);

			std::string tmp_path = this->_path.substr(0, lastSlashPos + 1) + "tmp.html";
			this->_path = tmp_path;
			this->fileHandler();
			this->setResponse();
		} else {
			setCode("204");
			this->_message = getStatusMessages().at(this->_code);
			this->setResponse();
		}
	}
	catch (const HttpException& e) {
		logMessage(ERROR, "HttpResponse", "HTTP Error " +  e.getCode() + ": " + e.what(), this->_server_name);
		HttpResponse errorResponse = HttpResponse(e.getCode(), this->_request);
		*this = errorResponse;
		this->setErrorResponse();
		return;
	}
}

void HttpResponse::cgiHandler(const char* binary_path, char* const args[])
{
	int pipefd[2];
	if (pipe(pipefd) == -1) {
		throw AHttpBuilder::HttpException("500");
	}
	pid_t pid = fork();
	if (pid < 0) {
		close(pipefd[0]);
		close(pipefd[1]);
		throw AHttpBuilder::HttpException("500");
		return ;
	} else if (pid == 0) {
			close(pipefd[1]);
			dup2(pipefd[0], 0);
			execve(binary_path, args, this->_environ);
			close(pipefd[0]);
			return ;
	} else {
			int status;
			close(pipefd[0]);
			write(pipefd[1], this->_body.c_str(), this->_contentLength);
			close(pipefd[1]);
			time_t now = time(0);
			while (time(0) < now + CGI_TIMEOUT) {
				if (waitpid(pid, &status, WNOHANG) > 0)
					break ;
			}
			if (time(0) >= now + CGI_TIMEOUT) {
				kill(pid, SIGKILL);
				HttpResponse errorResponse = HttpResponse("504", this->_request);
				*this = errorResponse;
				this->setErrorResponse();
				throw AHttpBuilder::HttpException("504");
			}
			else if (WEXITSTATUS(status)) {
				int exitStatus = WEXITSTATUS(status);
				if (exitStatus == 1)
					exitStatus = 100;
				exitStatus += 400;
				std::string errorCode = numberToString(exitStatus);
				HttpResponse errorResponse = HttpResponse(errorCode, this->_request);
				*this = errorResponse;
				this->setErrorResponse();
				throw AHttpBuilder::HttpException(errorCode);
			}
	}
}

// Getters & Setters

std::string HttpResponse::getResponse() const { return _response; }

const std::map<std::string, std::string>& HttpResponse::getMimeTypes()
{
	if (_mimeTypes.empty())
			initializeMimeTypes();
	return _mimeTypes;
}

void HttpResponse::setMessage(std::string message) { this->_message = message;}

void HttpResponse::setDate()
{
	time_t now = time(0);
	struct tm timeinfo;
	gmtime_r(&now, &timeinfo);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", &timeinfo);
	this->_date = buffer;
}

void HttpResponse::setErrorResponse()
{
	size_t rootPos = findWebsiteRoot(this->_path, '/');
	std::string errorFolder = this->_path.substr(0, rootPos) + ERROR_PAGES_PATH;
	std::string filename = errorFolder + this->_code + ".html";
	std::ostringstream response;
	response << "HTTP/1.1 " << _code << " " << _message << "\r\n";
	response << "Date: " << _date << "\r\n";
	response << "Connection: " << _connection << "\r\n";
	response << "Server: " << _server_name << "\r\n";
	response << "Content-Type: " << getMimeTypes().at("html") << "\r\n";
	try {
		if (checkFileExist(filename)) {
		response << "Content-Length: " << getFileSize(filename) << "\r\n";
		response << "\r\n";
		response << readFileToString(filename);
		}
		else {
			throw AHttpBuilder::HttpException("404");
		}
	}
	catch (const std::exception& e) {
		std::ostringstream body;
		int contentLength;
		body << "<html><body><h1>Error " << _code << " " << _message << "</h1></body></html>";
		contentLength = body.str().length();
		response << "Content-Length: " << contentLength << "\r\n";
		response << "\r\n";
		response << body.str();
		this->_response = response.str();
		return ;
	}
	this->_response = response.str();
}

void HttpResponse::setResponse()
{
	std::ostringstream response(std::ios::binary);
	response << "HTTP/1.1 " << _code << " " << _message << "\r\n";
	response << "Date: " << _date << "\r\n";
	response << "Connection: " << _connection << "\r\n";
	response << "Server: " << _server_name << "\r\n";
	if (!_cookie.empty())
		response << "Set-Cookie: " << _cookie << "\r\n";
	if (_code != "204") {
		response << "Content-Type: " << _contentType << "\r\n";
		response << "Content-Length: " << _contentLength << "\r\n";
		response << "Cache-Control: " << "public" << "\r\n";
		response << "Last-Modified: " << _lastModified << "\r\n";
		response << "ETag: " << _etag << "\r\n";
		response << "\r\n";
		response.write(_body.c_str(), _body.length());
	}
	else {
		response << "\r\n";
	}
	this->_response = response.str();
}

void HttpResponse::setExecArgs()
{
	size_t pos = this->_path.find_last_of('/');
	std::string binary_path = scriptSelector(this->_path);
	std::string folder = this->_path.substr(0, pos + 1);
	if (binary_path.empty())
		throw AHttpBuilder::HttpException("404");
	memset(_exec_args, 0, sizeof(_exec_args));
	_exec_strings.clear();
	_exec_strings.push_back(binary_path);
	_exec_strings.push_back(this->_path);
	_exec_strings.push_back(folder);
	if (!this->_cgi_args.empty()) {
		for (std::map<std::string, std::string>::iterator it = _cgi_args.begin(); it != _cgi_args.end(); ++it) {
			_exec_strings.push_back(it->first);
			_exec_strings.push_back(it->second);
		}
	}
	size_t i;
	for (i = 0; i < _exec_strings.size(); ++i) {
		_exec_args[i] = (char *)_exec_strings[i].c_str();
	}
	_exec_args[i] = NULL;
}

// Utils

bool checkDeletePermission(const std::string& binary_path, const std::string& script_path)
{
	if (!checkFileExist(binary_path) || !checkFileExist(script_path)) {
		throw AHttpBuilder::HttpException("404");
		return false;
	}
	if (!checkScriptPermission(binary_path, script_path)) {
		throw AHttpBuilder::HttpException("403");
		return false;
	}
	return true;
}

bool HttpResponse::needCache()
{
	if (_cacheControl.find("no-cache") != std::string::npos
			|| _cacheControl.find("must-revalidate") != std::string::npos
			|| _cacheControl.find("no-store") != std::string::npos)
		return false;
	return true;
}

void HttpResponse::logResponseDetails() const
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

	details << "=== Response Details ===\n"
		<< "Code: '" << this->_code << "'\n"
		<< "Message: '" << this->_message << "'\n"
		<< "Path: '" << this->_path << "'\n"
		<< "Date: '" << (this->_date.empty() ? "not set" : this->_date) << "'\n"
		<< "Connection: '" << (this->_connection.empty() ? "not set" : this->_connection) << "'\n"
		<< "Cookie: '" << (this->_cookie.empty() ? "not set" : this->_cookie) << "'\n"
		<< "Server: '" << (this->_server_name.empty() ? "not set" : this->_server_name) << "'\n"
		<< "Content-Type: '" << (this->_contentType.empty() ? "not set" : this->_contentType) << "'\n"
		<< "Content-Length: " << (this->_contentLength == -1 ? "not set" : numberToString(this->_contentLength)) << "\n"
		<< "Cache-Control: '" << (this->_cacheControl.empty() ? "not set" : this->_cacheControl) << "'\n"
		<< "Last-Modified: '" << (this->_lastModified.empty() ? "not set" : this->_lastModified) << "'\n"
		<< "ETag: '" << (this->_etag.empty() ? "not set" : this->_etag) << "'\n"
		<< "Is CGI: " << (this->_isCgi ? "yes" : "no") << "\n"
		<< "Body (truncated): '" << truncatedBody << "'\n"
		<< "=== End Response Details ===";

	logMessage(DEBUG, "HttpResponse", details.str(), server_name);
}
