#include "Server.hpp"
#include "Client.hpp"

// Constructors & Destructor

Server::Server(t_config& config): _fd(0), _bytes_sent(0), _res(NULL), _config(config)
{
	(void)this->_bytes_sent;

	printConfig();
	init_socket();
	connect_socket();
}

Server::Server(const Server& copy): _fd(copy._fd), _bytes_sent(copy._bytes_sent), _res(copy._res), _config(copy._config)
{
	*this = copy;
}

Server& Server::operator=(const Server& copy)
{
	if (this != &copy) { }
	return *this;
}

Server::~Server()
{
	logMessage(INFO, "Server", "Has been closed", this->getServerName());
}

// Socket

void Server::init_socket()
{
	int opt(1);

	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	logMessage(INFO, "Server", "Socket successfully created with fd " + numberToString(_fd), this->_config.server_name);
	if (this->_fd == -1) {
		logMessage(ERROR, "Server", "socket: " + std::string(strerror(errno)), this->_config.server_name);
		throw std::exception();
	}
	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) == -1){
		logMessage(ERROR, "Server", "fcntl: " + std::string(strerror(errno)), this->_config.server_name);
		throw std::exception();
	}
	if (setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) > 0 ) {
		logMessage(ERROR, "Server", "setsockopt: " + std::string(strerror(errno)), this->_config.server_name);
		throw std::exception();
	}
}

void Server::connect_socket()
{
	struct addrinfo hints;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(this->_config.ip_addr.c_str(), this->_config.port.c_str(), &hints, &this->_res) != 0) {
		logMessage(ERROR, "Server", "getaddrinfo: "+ std::string(gai_strerror(errno)), this->_config.server_name);
		throw std::exception();
	}
	if (bind(this->_fd, this->_res->ai_addr, this->_res->ai_addrlen) == -1) {
		logMessage(ERROR, "Server", "bind: addr already used", this->_config.server_name);
		this->freeAddrInfo();
		throw std::exception();
	}
	logMessage(INFO, "Server", "Bound socket with fd  " + numberToString(_fd) + " to " + this->_config.ip_addr + " with port " + this->_config.port, this->_config.server_name);
	if (listen(this->_fd, BACKLOG) == -1) {
		this->freeAddrInfo();
		logMessage(ERROR, "Server", "listen: "+ std::string(gai_strerror(errno)), this->_config.server_name);
		throw std::exception();
	}
	logMessage(INFO, "Server", "Waiting for a connection...", this->_config.server_name);
}

void Server::freeAddrInfo()
{
	if (this->_res)
		freeaddrinfo(this->_res);
}

// Client

void Server::closeClient(int &fd_client)
{
	std::map<int, Client*>::iterator it;

	close(fd_client);
	it = this->_clients.find(fd_client);
	if (it != this->_clients.end()) {
		delete it->second;
		this->_clients.erase(it);
	}
}

void Server::createClient(int& fd_client, struct sockaddr_storage& client_addr, socklen_t& addr_size)
{
	this->_clients[fd_client] = new Client(fd_client, client_addr, addr_size);
	this->_clients[fd_client]->setServerHost(*this);
}

Client* Server::findClient(int& fd_client)
{
	std::map<int, Client*>::iterator it;

	for (it = this->_clients.begin(); it != this->_clients.end(); ++it) {
		if (it->first == fd_client)
			return (it->second);
	}
	return NULL;
}

void Server::checkTimeoutClient()
{
	std::map<int, Client*>::iterator it;
	std::vector<int>::iterator it_list;
	std::vector<int> list_fd;

	list_fd = this->getFdClients();
	for (it_list = list_fd.begin(); it_list != list_fd.end(); ++it_list) {
		it = this->_clients.find(*it_list);
		if (it != this->_clients.end() && it->second->isTimeout(time(NULL)) == true) {
			logMessage(DEBUG, "Client " + numberToString(it->second->getFd()),"Timedout of " + numberToString(TIMEOUT_CLIENT) + " seconds", this->getServerName());
			closeClient(it->second->getFd());
		}
	}
}

// Print

void Server::printConfig() const
{
	std::stringstream config_str;
	
	config_str << "=== Server Configuration ===\n"
		<< "					Port: '" << this->_config.port << "'\n"
		<< "					Host: '" << this->_config.ip_addr << "'\n"
		<< "					Server name: '" << this->_config.server_name << "'\n"
		<< "					Root: '" << this->_config.path << "'\n"
		<< "					Index: '" << this->_config.index << "'\n";
	config_str << "					Client max body size: " << _config.client_max_body_size << "\n";
	for (std::map<std::string, t_location>::const_iterator it = _config.locations.begin();
		 it != _config.locations.end(); ++it) {
		config_str << "					Location: " << it->first << "\n";
		
		if (!it->second.root.empty())
			config_str << "  					Root: '" << it->second.root << "'\n";
		
		if (!it->second.index.empty())
			config_str << "  					Index: '" << it->second.index << "'\n";
		
		config_str << "  					Autoindex: " << (it->second.autoindex ? "on" : "off") << "\n";
		
		if (!it->second.allowed_methods.empty()) {
			config_str << "  					Allowed methods: ";
			for (std::vector<std::string>::const_iterator mit = it->second.allowed_methods.begin();
				 mit != it->second.allowed_methods.end(); ++mit) {
				if (mit != it->second.allowed_methods.begin())
					config_str << ", ";
				config_str << *mit;
			}
			config_str << "\n";
		}
	}
	config_str << "					=== End Configuration ===";

	logMessage(DEBUG, "Server", config_str.str(), this->_config.server_name);
}

// Getters

int& Server::getFd() { return (this->_fd); }

const std::string Server::getIpAddr() { return (this->_config.ip_addr); }

const std::string Server::getServerName() { return (this->_config.server_name); }

const t_config& Server::getConfig() const { return this->_config; }

std::vector<int> Server::getFdClients()
{
	std::map<int, Client*>::iterator it;
	std::vector<int> list;

	for (it = this->_clients.begin(); it != this->_clients.end(); ++it)
		list.push_back(it->first);
	return list;
}
