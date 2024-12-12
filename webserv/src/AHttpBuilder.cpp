#include "AHttpBuilder.hpp"

std::map<std::string, std::string> AHttpBuilder::_mapStatus;

// Constructors & Destructor

AHttpBuilder::AHttpBuilder() {}

AHttpBuilder::AHttpBuilder(const AHttpBuilder& other) { (void)other; }

AHttpBuilder& AHttpBuilder::operator=(const AHttpBuilder& other)
{
	(void)other;

	return *this;
}

AHttpBuilder::~AHttpBuilder()  throw() {}

// Getters & Setters

bool AHttpBuilder::getIsCgi() const { return this->_isCgi; }
std::string AHttpBuilder::getType() const { return this->_type; }
std::string AHttpBuilder::getPath() const { return this->_path; }
std::string AHttpBuilder::getCode() const { return this->_code; }
std::string AHttpBuilder::getContentType() const { return this->_contentType; }
ssize_t AHttpBuilder::getContentLength() const { return this->_contentLength; }
std::string AHttpBuilder::getConnection() const { return this->_connection; }
std::string AHttpBuilder::getEtag() const { return this->_etag; }
std::string AHttpBuilder::getLastModified() const { return this->_lastModified; }
std::string AHttpBuilder::getCacheControl() const { return this->_cacheControl; }
std::string AHttpBuilder::getBody() const { return this->_body; }
std::string AHttpBuilder::getHost() const { return this->_host; }
std::string AHttpBuilder::getServer() const { return this->_server_name; }
std::string AHttpBuilder::getAccept() const { return this->_accept; }
std::string AHttpBuilder::getCookie() const { return this->_cookie; }

void AHttpBuilder::setIsCgi(bool isCgi) { this->_isCgi = isCgi; }
void AHttpBuilder::setPath(const std::string& path) { this->_path = path; }
void AHttpBuilder::setType(const std::string& type) { this->_type = type; }
void AHttpBuilder::setCode(const std::string& code) { this->_code = code; }
void AHttpBuilder::setContentType(const std::string& contentType) { this->_contentType = contentType; }
void AHttpBuilder::setContentLength(size_t length) { this->_contentLength = length; }
void AHttpBuilder::setConnection(const std::string& connection) { this->_connection = connection; }
void AHttpBuilder::setEtag(const std::string& etag) { this->_etag = etag; }
void AHttpBuilder::setLastModified(const std::string& lastModified) { this->_lastModified = lastModified; }
void AHttpBuilder::setCacheControl(const std::string& cacheControl) { this->_cacheControl = cacheControl; }
void AHttpBuilder::setBody(const std::string& body) { this->_body = body; }
void AHttpBuilder::setHost(const std::string& host) { this->_host = host; }
void AHttpBuilder::setServer(const std::string& server) { this->_server_name = server; }
void AHttpBuilder::setAccept(const std::string& accept) { this->_accept = accept; }


const std::map<std::string, std::string>& AHttpBuilder::getStatusMessages()
{
	if (_mapStatus.empty())
		initializeStatusMessages();
	return _mapStatus;
}

void AHttpBuilder::initializeStatusMessages(void)
{
	_mapStatus["100"] = "Continue";
	_mapStatus["200"] = "OK";
	_mapStatus["201"] = "Created";
	_mapStatus["202"] = "Accepted";
	_mapStatus["204"] = "No Content";
	_mapStatus["304"] = "Not Modified";
	_mapStatus["400"] = "Bad Request";
	_mapStatus["401"] = "Unauthorized";
	_mapStatus["403"] = "Forbidden";
	_mapStatus["404"] = "Not Found";
	_mapStatus["405"] = "Method Not Allowed";
	_mapStatus["406"] = "Not Acceptable";
	_mapStatus["408"] = "Request Timeout";
	_mapStatus["413"] = "Payload Too Large";
	_mapStatus["414"] = "URI Too Long";
	_mapStatus["415"] = "Unsupported Media Type";
	_mapStatus["500"] = "Internal Server Error";
	_mapStatus["501"] = "Not Implemented";
	_mapStatus["502"] = "Bad Gateway";
	_mapStatus["503"] = "Service Unavailable";
	_mapStatus["504"] = "Gateway Timeout";
	_mapStatus["505"] = "HTTP Version Not Supported";
}