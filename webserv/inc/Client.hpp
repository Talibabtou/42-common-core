#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "utils.h"

class Server;

class Client {
public:
	Client(int fd_client, struct sockaddr_storage client_addr, socklen_t addr_size);
	~Client();

	void resetRequest();
	void resetResponse();
	void resetBytesRead();
	void resetBytesSend();

	Server* getServer();
	std::string& getRequest();
	int& getFd();
	bool getReadyToSend();
	bool getMustBeClose();
	std::string& getResponse();
	size_t getBytesRead();
	size_t getBytesSend();

	void setServerHost(Server& server);
	void setLastActivity(time_t current_time);
	void setReadyToSend(bool ready);
	void setMustBeClose(bool state);
	void setResponse(std::string response);

	void appendBytesSend(int& bytes_send);
	void appendBytesRead(int& bytes_read);
	void appendRequest(const char buffer[BUFFER_SIZE], int& bytes_read);

	size_t contentLength();
	size_t countBoundarySize(std::string boundary_id);
	bool isTimeout(time_t current_time);
	bool isPost();
	bool isFull();

private:
	Client(const Client& copy);
	Client& operator=(const Client& copy);

	bool _ready_to_send;
	bool _must_be_close;
	int _fd;
	size_t _bytes_read;
	size_t _bytes_send;
	time_t _last_activity;
	Server* _server;
	std::string _request;
	std::string _response;
	socklen_t _addr_size;
	struct sockaddr_storage _client_addr;
};

#endif
