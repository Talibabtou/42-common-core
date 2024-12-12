#include "Webserv.hpp"
#include "ConfigParser.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "utils.h"

// Constructors & Destructor

Webserv::Webserv(const char* config_path): _stop(false), _fd_ev(0), _ev(NULL)
{
	try {
		if (config_path) {
			ConfigParser parser(config_path);
			this->_config = parser.getConfigs();
			if (_config.empty()) {
				logMessage(ERROR, "Webserv", "No server to run", "");
				throw std::exception();
			}
		} else {
			t_config default_config;
			default_config.path = "/";
			default_config.ip_addr = IP_ADDR;
			default_config.server_name = "default";
			default_config.port = "8080";
			this->_config.push_back(default_config);
		}
		std::memset(_events, 0, sizeof(epoll_event));
	} catch (const std::exception& e) {
		this->closeWebserv();
	}
}

Webserv::Webserv(const Webserv& copy) { *this = copy; }

Webserv& Webserv::operator=(const Webserv& copy)
{
	if (this != &copy) { }
	return *this;
}

Webserv::~Webserv()
{
	logMessage(INFO, "Webserv", "Webserv successfully stopped", "");
}

// Run

void Webserv::runWebserv()
{
	try {
		std::cout << BLUE << BOLD << "																	" << std::endl;
		std::cout << "																		" << std::endl;
		std::cout << "																		" << std::endl;
		std::cout << "			██╗    ██╗███████╗██████╗ ███████╗███████╗██████╗ ██╗   ██╗	" << std::endl;
		std::cout << "			██║    ██║██╔════╝██╔══██╗██╔════╝██╔════╝██╔══██╗██║   ██║	" << std::endl;
		std::cout << "			██║ █╗ ██║█████╗  ██████╔╝███████╗█████╗  ██████╔╝██║   ██║	" << std::endl;
		std::cout << "			██║███╗██║██╔══╝  ██╔══██╗╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝	" << std::endl;
		std::cout << "			╚███╔███╔╝███████╗██████╔╝███████║███████╗██║  ██║ ╚████╔╝ 	" << std::endl;
		std::cout << "			 ╚══╝╚══╝ ╚══════╝╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  	" << std::endl;
		std::cout << "			                                    " << END << BLUE << ITALIC << std::endl;
		std::cout << "			                                                  by bboissen, gdumas, jmougel." << std::endl;
		std::cout << "			                                    " << std::endl;
		std::cout << "			                                    " << END << std::endl;

		signal(SIGINT ,sig_handler);
		signal(SIGTSTP, sig_handler);
		logMessage(INFO, "Webserv", "Init Epoll...", "");
		initEpoll();
		logMessage(INFO, "Webserv", "Init Servers...", "");
		initServers();
		if (this->_servers.empty()) {
			logMessage(ERROR, "Webserv", "No server to run", "");
			throw std::exception();
		}
		logMessage(INFO, "Webserv", "Running Webserv...", "");
		handleEpoll();
	}
	catch (const std::exception& e) {
		this->closeWebserv();
	}
}

// Create

void Webserv::createServer(t_config& config)
{
	Server* ptr;
	try {
		ptr = new Server(config);
		this->_servers[ptr->getFd()] = ptr;
		setEv(EPOLLIN, ptr->getFd());
	}
	catch (const std::exception& e) {
		this->closeServer(ptr->getFd());
		logMessage(ERROR, "Webserv", "Impossible to create a server", "");
	}
}

// Close & Stop

void Webserv::closeClient(int& fd_client, Server& server)
{
	if (epoll_ctl(this->_fd_ev, EPOLL_CTL_DEL, fd_client, this->_ev) != 0) {
		logMessage(ERROR, "Webserv", "epoll_ctl: " + std::string(strerror(errno)), "");
		throw std::exception();
	}
	server.closeClient(fd_client);
}

void Webserv::closeServer(int& fd_server)
{
	std::map<int, Server*>::iterator it;
	std::vector<int>::iterator it_list;
	std::vector<int> list_fd;

	it = this->_servers.find(fd_server);
	if (it != this->_servers.end()) {
		list_fd = it->second->getFdClients();
		for (it_list = list_fd.begin(); it_list != list_fd.end(); ++it_list)
			closeClient(*it_list, *it->second);
		if (epoll_ctl(this->_fd_ev, EPOLL_CTL_DEL, fd_server, this->_ev) != 0) {
			logMessage(ERROR, "Webserv", "epoll_ctl: " + std::string(strerror(errno)), "");
			throw std::exception();
		}
		close(fd_server);
		it->second->freeAddrInfo();
		delete this->_servers[fd_server];
		this->_servers.erase(it);
	}
}

void Webserv::closeWebserv()
{
	std::map<int, Server*>::iterator it;
	std::vector<int>::iterator it_list;
	std::vector<int> list_fd;

	list_fd = this->getFdServers();
	for (it_list = list_fd.begin(); it_list != list_fd.end(); ++it_list)
		closeServer(*it_list);
	if (this->_fd_ev)
		close(this->_fd_ev);
	this->_config.clear();
	if (this->_ev)
		delete this->_ev;
}

void Webserv::stopWebserv() { this->_stop = true; }

// Init

void Webserv::initServers()
{
	std::vector<t_config>::iterator it;

	for (it = this->_config.begin(); it != this->_config.end(); ++it)
		createServer(*it);
}

void Webserv::initEpoll()
{
	this->_fd_ev = epoll_create(1);
	if (this->_fd_ev == -1) {
		logMessage(ERROR, "initEpoll: ", strerror(errno), "");
		throw std::exception();
	}
	this->_ev = new struct epoll_event;
	memset(*(&_ev), 0, sizeof(struct epoll_event));
	memset(&_events, 0, sizeof(_events));
}

// Handlers

void Webserv::handleEpoll()
{
	int nfds(0);
	Client* client;
	time_t last_timeout_check = time(NULL);

	while (this->_stop == false) {
		time_t current_time = time(NULL);

		if (current_time - last_timeout_check >= TIMEOUT_CHECK_INTERVAL) {
			this->checkTimeoutClient();
			last_timeout_check = current_time;
		}
		nfds = epoll_wait(this->_fd_ev, this->_events, MAX_EVENT, 0);
		for (int i = 0; i < nfds; i++) {
			int current_fd = this->_events[i].data.fd;
			uint32_t events = this->_events[i].events;
			if (events & EPOLLERR || events & EPOLLHUP) {
				client = this->findClient(current_fd);
				if (client) {
					Server* server = client->getServer();
					if (server) {
						logMessage(INFO, "Webserv",
							"Client disconnected (EPOLLHUP/EPOLLERR) with fd: " +
							numberToString(current_fd), server->getServerName());
						this->closeClient(current_fd, *server);
					} else
						logMessage(ERROR, "Webserv", "Server not found (EPOLLHUP/EPOLLERR)", "");
				} else if (isServer(current_fd)) {
						logMessage(INFO, "Webserv",
							"Server issue (EPOLLHUP/EPOLLERR) with fd: " +
							numberToString(current_fd), this->_servers[current_fd]->getServerName());
						this->closeServer(current_fd);
				} else
					logMessage(ERROR, "Webserv", "Epoll error (EPOLLHUP/EPOLLERR)", "");
				continue;
			}
			else if (events & EPOLLIN) {
				if (this->isServer(current_fd)) {
					this->handleServers(current_fd);
				}
				else {
					client = this->findClient(current_fd);
					if (client)
						this->handleClientsRecv(current_fd);
				}
			}
			else if (events & EPOLLOUT) {
				client = this->findClient(current_fd);
				if (client && client->getReadyToSend()) {
					this->handleClientsSend(current_fd);
				}
			}
		}
	}
	this->closeWebserv();
}

void Webserv::handleServers(int& fd_server)
{
	int fd_client;
	socklen_t addr_size;
	struct sockaddr_storage client_addr;

	addr_size = sizeof(client_addr);
	fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addr_size);
	if (fd_client < 0) {
		logMessage(ERROR, "Webserv", "accept: " + std::string(strerror(errno)), this->_servers[fd_server]->getServerName());
		return;
	}
	this->_servers[fd_server]->createClient(fd_client, client_addr, addr_size);
	if (fcntl(fd_client, F_SETFL, O_NONBLOCK) < 0) {
		logMessage(ERROR, "Webserv", "fcntl: setting file descriptor " + numberToString(fd_client) + " to non-blocking mode failed", this->_servers[fd_server]->getServerName());
	}
	logMessage(INFO, "Webserv", "A client has been connected with fd: " + numberToString(fd_client), this->_servers[fd_server]->getServerName());
	this->setEv(EPOLLIN | EPOLLOUT, fd_client);
}

void Webserv::handleClientsSend(int& fd_client)
{
	int bytes_sent(0);
	Client* client;
	Server* server;
	size_t response_size;

	client = this->findClient(fd_client);
	client->setLastActivity(time(NULL));
	server = this->_servers[client->getServer()->getFd()];
	response_size = client->getResponse().length();
	bytes_sent = send(fd_client, client->getResponse().c_str(), response_size, 0);
	client->appendBytesSend(bytes_sent);
	if (bytes_sent == -1) {
		logMessage(ERROR, "Webserv", "Client issue when sending, with fd: ", server->getServerName());
		this->closeClient(fd_client, *server);
	}
	else if (bytes_sent == 0) {
		logMessage(INFO, "Webserv", "SEND: Client disconnected (EOF) with fd: " + numberToString(fd_client), server->getServerName());
		this->closeClient(fd_client, *server);
	}
	else if (client->getBytesSend() == response_size) {
		logMessage(DEBUG, "Webserv", "Response sent to fd " + numberToString(fd_client), server->getServerName());
		client->resetBytesSend();
		client->resetResponse();
		client->setReadyToSend(false);
		if (client->getMustBeClose() == true) {
			this->closeClient(fd_client, *server);
		}
	}
	return;
}

void Webserv::handleRequest(int& fd_client, Client* client)
{
	HttpRequest request(*client);

	try {
		request.buildHeader();
		logMessage(INFO, "Client " + numberToString(fd_client), "Request received: "
			+ request.getType() + " " + request.getPath() + " "
			+ request.getVersion(), request.getServerName());
		std::string connection_header;
		if (request.getConnection() == "close") {
			connection_header = "Connection: close\r\n";
			client->setMustBeClose(true);
		} else {
			connection_header = "Connection: keep-alive\r\n";
			client->setMustBeClose(false);
		}
	}
	catch (const AHttpBuilder::HttpException& e) {
		logMessage(ERROR, "Request", "Failed to build request header: " +  e.getCode() + ": " + e.what(), client->getServer()->getServerName());
		HttpResponse response(e.getCode(), client->getServer());
		response.buildHeader();
		response.logResponseDetails();

		response.getResponse();
		client->setResponse(response.getResponse());
		return;
	}
	catch (const std::exception& e) {
		logMessage(ERROR, "Request", std::string("Failed to catch HTTP exception: 400 ") + e.what(), client->getServer()->getServerName());
		HttpResponse response("400", client->getServer());
		response.buildHeader();
		response.logResponseDetails();
		response.getResponse();
		client->setResponse(response.getResponse());
		return;
	}
	try {
		HttpResponse response(request);
		response.buildHeader();
		response.logResponseDetails();
		client->setResponse(response.getResponse());
	}
	catch (const std::exception& e) {
		logMessage(ERROR, "Response", std::string("Failed to process response: 500 ") + e.what(), client->getServer()->getServerName());
		HttpResponse response("500", client->getServer());
		response.buildHeader();
		client->setResponse(response.getResponse());
	}
}

void Webserv::handleClientsRecv(int& fd_client)
{
	Client* client;
	Server* server;
	int bytes_read(0);
	char buffer[BUFFER_SIZE] = {0};
	bool status(false);

	client = this->findClient(fd_client);
	if (client == NULL) {
		logMessage(ERROR, "Webserv", "Client not found", "");
		return;
	}
	server = this->_servers[client->getServer()->getFd()];
	if (server == NULL) {
		logMessage(ERROR, "Webserv", "Server not found", "");
		return;
	}
	while ((bytes_read = recv(fd_client, &buffer, sizeof(buffer) - 1, O_NONBLOCK)) > 0) {
		buffer[bytes_read] = '\0';
		client->appendRequest(buffer, bytes_read);
		client->appendBytesRead(bytes_read);
		client->setLastActivity(time(NULL));
		memset(buffer, 0, BUFFER_SIZE);
		if (bytes_read < BUFFER_SIZE - 2)
			break;
	}
	try {
		status = client->isFull();
	} catch (const std::exception& e) {
		logMessage(ERROR, "Webserv", "Client " + numberToString(fd_client) + ", 413 Payload too large (" + numberToString(server->getConfig().client_max_body_size) + " Bytes) reached", server->getServerName());
		HttpResponse response("413", client->getServer());
		response.buildHeader();
		client->setResponse(response.getResponse());
		client->setReadyToSend(true);
		client->resetRequest();
		client->resetBytesRead();
		return;
	}
	if (status == true) {
		this->handleRequest(fd_client, client);
		client->setReadyToSend(true);
		client->resetRequest();
		client->resetBytesRead();
		return;
	}
	else if (bytes_read == 0) {
		logMessage(INFO, "Webserv", "RECV: Client disconnected (EOF) with fd: " + numberToString(fd_client), server->getServerName());
		this->closeClient(fd_client, *server);
	}
	else if (bytes_read == -1) {
		logMessage(INFO, "Webserv", "Client issue when reading, with fd: " + numberToString(fd_client), server->getServerName());
		this->closeClient(fd_client, *server);
	}
}

// Getters & Setter

const std::map<int, Server*>& Webserv::getServers() const { return _servers; }

std::vector<int> Webserv::getFdServers()
{
	std::map<int, Server*>::iterator it;
	std::vector<int> list;

	for (it = this->_servers.begin(); it != this->_servers.end(); ++it)
		list.push_back(it->first);
	return list;
}

Webserv& Webserv::getWebserv(const char* config)
{
	static Webserv instance(config);
	return instance;
}

void Webserv::setEv(uint32_t events, int& fd)
{
	this->_ev->events = events;
	this->_ev->data.fd = fd;
	if (epoll_ctl(this->_fd_ev, EPOLL_CTL_ADD, this->_ev->data.fd, this->_ev) == -1) {
		logMessage(ERROR, "setEv: ", strerror(errno), "");
		throw std::exception();
	}
}

// Utils

void Webserv::checkTimeoutClient()
{
	std::map<int, Server*>::iterator it;

	for (it = this->_servers.begin(); it != this->_servers.end(); ++it)
		it->second->checkTimeoutClient();
}

bool Webserv::isServer(int& fd_server)
{
	std::map<int, Server*>::iterator it;

	for (it = this->_servers.begin(); it != this->_servers.end(); ++it) {
		if (it->first == fd_server)
			return true;
	}
	return false;
}

Client* Webserv::findClient(int& fd_client)
{
	Client* ptr(NULL);
	std::map<int, Server*>::iterator it;

	for (it = this->_servers.begin(); it != this->_servers.end(); ++it) {
		if ((ptr = it->second->findClient(fd_client)))
			return ptr;
	}
	return ptr;
}
