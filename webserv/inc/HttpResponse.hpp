#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include "AHttpBuilder.hpp"
# include "HttpRequest.hpp"
# include "utils.h"

class HttpResponse : virtual public AHttpBuilder {
public:
	HttpResponse(void);
	HttpResponse(const HttpRequest& request);
	HttpResponse(std::string code, const HttpRequest& request);
	HttpResponse(std::string code, Server* server);
	HttpResponse(const HttpResponse& other);
	HttpResponse &operator=(const HttpResponse &other);
	~HttpResponse() throw();

	void buildHeader();

	std::string getResponse() const;
	void logResponseDetails() const;

	static const std::map<std::string, std::string>& getMimeTypes();

private:
	void cgiHandler(const char* binary_path, char* const args[]);

	void GetFileHandler();
	void GetCgiHandler();
	void PostHandler();
	void DelHandler();
	void fileHandler();

	bool needCache();

	void setMessage(std::string message);
	void setDate();
	void setResponse();
	void setErrorResponse();
	void setExecArgs();

	void initializeEnviron(const HttpRequest& request);
	static void initializeMimeTypes();

	std::string _envStrings[3];
	char* _environ[4];
	HttpRequest _request;
	std::string _message;
	std::string _date;
	std::string _response;
	std::vector<std::string> _exec_strings;
	char* _exec_args[MAX_CGI_ARGS + 1];
	static std::map<std::string, std::string> _mimeTypes;
};

bool checkDeletePermission(const std::string& binary_path, const std::string& script_path);

#endif
