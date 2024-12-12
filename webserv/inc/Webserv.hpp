#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "utils.h"
# include "AHttpBuilder.hpp"

class Server;
class Client;

class Webserv {
public:
	~Webserv();

	void runWebserv();
	void stopWebserv();
	static Webserv& getWebserv(const char* config);
	const std::map<int, Server*>& getServers() const;
	std::vector<int> getFdServers();

private:
	Webserv(const char* config);
	Webserv(const Webserv& copy);
	Webserv& operator=(const Webserv& copy);

	void initServers();
	void initEpoll();
	void createServer(t_config& config);
	void closeClient(int& fd_client, Server& server);
	void closeServer(int& fd_server);
	void closeWebserv();
	void checkTimeoutClient();
	bool isServer(int& fd_server);
	Client* findClient(int& fd_client);
	void handleClientsRecv(int& fd_client);
	void handleClientsSend(int& fd_client);
	void handleServers(int& fd_server);
	void handleEpoll();
	void handleRequest(int& fd_client, Client* client);
	void setEv(uint32_t events, int& fd);

	bool _stop;
	std::vector<t_config> _config;
	std::map<int, Server*> _servers;
	int _fd_ev;
	struct epoll_event* _ev;
	struct epoll_event _events[MAX_EVENT];
};

#endif
