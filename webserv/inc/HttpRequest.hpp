#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include "AHttpBuilder.hpp"
# include "Server.hpp"

class HttpRequest : public AHttpBuilder {
public:
	HttpRequest();
	HttpRequest(Client& client);
	HttpRequest(const HttpRequest& other);
	HttpRequest& operator=(const HttpRequest& other);
	~HttpRequest() throw();

	void buildHeader();

	const std::string& getHost() const;
	const Server* getServer() const;
	const std::string& getServerName() const;
	const std::string& getType() const;
	std::string getVersion() const;
	const std::string& getPath() const;
	const std::string& getConnection() const;
	const std::string& getAccept() const;
	bool getIsCgi() const;
	const std::map<std::string, std::string>& getCgiArgs() const;

	void setBody(const std::string& raw_request);

private:
	std::string normalizePath(const std::string& path);
	void processPath(const std::string& path);
	void buildFinalPath(const std::string& matchedLocation, const std::string& basePath,
						const t_location& locationConfig, const t_config& config,
						const std::string& queryParams);

	void parseRequestLine(const std::string& line);
	void parseHeader(const std::string& line);
	void parseQueryString(const std::string& queryString);
	void parseFormData(const std::string& boundary);
	std::string urlDecode(const std::string& encoded);

	void validateRequestComponents(const std::string& method, const std::string& path, const std::string& version);
	bool validateLocationAccess(const std::string& normalizedPath, const t_config& config);

	void logRequestDetails() const;

	Server* _server;
	std::string _version;
	std::map<std::string, std::string> _cgi_args;
};

#endif
