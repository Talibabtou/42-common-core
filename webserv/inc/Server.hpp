#ifndef SERVER_HPP
# define SERVER_HPP

# include "utils.h"

class Client;

class Server {
public:
	Server(t_config& config);
	~Server();

	void printConfig() const;
	int& getFd();
	const std::string getIpAddr();
	const std::string getServerName();
	std::vector<int> getFdClients();
	const t_config& getConfig() const;
	void createClient(int& fd_client, struct sockaddr_storage& client_addr, socklen_t& addr_size);
	void closeClient(int &fd_client);
	void checkTimeoutClient();
	Client* findClient(int& fd_client);
	void freeAddrInfo();

private:
	Server(const Server& copy);
	Server& operator=(const Server& copy);

	void init_socket();
	void connect_socket();
	
	int _fd;
	int _bytes_sent;
	std::map<int, Client*> _clients;
	struct addrinfo* _res;
	t_config _config;
};

#endif
