#ifndef AHTTPBUILDER_HPP
#define AHTTPBUILDER_HPP

#include "utils.h"

class AHttpBuilder {
public:
	AHttpBuilder(void);
	AHttpBuilder(const AHttpBuilder& other);
	AHttpBuilder &operator=(const AHttpBuilder &other);
	virtual ~AHttpBuilder() throw();

	virtual void buildHeader() = 0;

	bool getIsCgi() const;
	std::string getType() const;
	std::string getPath() const;
	std::string getCode() const;
	std::string getContentType() const;
	ssize_t getContentLength() const;
	std::string getConnection() const;
	std::string getEtag() const;
	std::string getLastModified() const;
	std::string getCacheControl() const;
	std::string getBody() const;
	std::string getHost() const;
	std::string getServer() const;
	std::string getAccept() const;
	std::string getCookie() const;
	static const std::map<std::string, std::string>& getStatusMessages();

		class HttpException : public std::exception {
	public:
		HttpException(std::string code) : _code(code) {

			try {
				_message = AHttpBuilder::getStatusMessages().at(_code);
			} catch (const std::out_of_range&) {
				_code = "500";
				_message = AHttpBuilder::getStatusMessages().at("500");
			}
		}
		virtual ~HttpException() throw() {}
		virtual const char* what() const throw() {
			return _message.c_str();
		}
		std::string getCode() const { return _code; }
	private:
		std::string _code;
		std::string _message;
	};

protected:
	bool _isCgi;
	std::string _type;
	std::string _path;
	std::string _code;
	std::string _contentType;
	ssize_t _contentLength;
	std::string _connection;
	std::string _etag;
	std::string _lastModified;
	std::string _cacheControl;
	std::string _body;
	std::string _host;
	std::string _server_name;
	std::string _accept;
	std::map<std::string, std::string> _cgi_args;
	std::string _cookie;
	static std::map<std::string, std::string> _mapStatus;

	void setIsCgi(bool is_cgi);
	void setPath(const std::string& path);
	void setType(const std::string& type);
	void setCode(const std::string& code);
	void setContentType(const std::string& contentType);
	void setContentLength(size_t length);
	void setConnection(const std::string& connection);
	void setEtag(const std::string& etag);
	void setLastModified(const std::string& lastModified);
	void setCacheControl(const std::string& cacheControl);
	void setBody(const std::string& body);
	void setHost(const std::string& host);
	void setServer(const std::string& server);
	void setAccept(const std::string& accept);
	static void initializeStatusMessages();
};

#endif