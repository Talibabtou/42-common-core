#include "Client.hpp"
#include "Server.hpp"

// Contructors & Destructor

Client::Client(int fd_client, struct sockaddr_storage client_addr, socklen_t addr_size):
	_ready_to_send(false), _must_be_close(false), _fd(fd_client), _bytes_read(0), _bytes_send(0), _server(NULL), _addr_size(addr_size), _client_addr(client_addr)
{
	(void)this->_addr_size;
	(void)this->_client_addr;
	this->_last_activity = std::time(NULL);
}

Client::Client(const Client& copy) { *this = copy; }

Client& Client::operator=(const Client& copy)
{
	if (this != &copy) {}
	return *this;
}

Client::~Client()
{
	logMessage(INFO, "Client " +  numberToString(this->_fd), "Has been closed", this->_server->getServerName());
}

// Getters & Setters

int& Client::getFd() { return this->_fd; }

Server* Client::getServer() { return this->_server; }

std::string& Client::getResponse() { return this->_response; }

bool Client::getReadyToSend() { return this->_ready_to_send; }

std::string& Client::getRequest()
{
	if (!this->_request.empty() && this->_request[this->_request.length() - 1] == '\n') {
		this->_request.erase(this->_request.length() - 1);
	}
	return this->_request;
}

size_t Client::getBytesRead() { return this->_bytes_read; }

size_t Client::getBytesSend() { return this->_bytes_send; }

bool Client::getMustBeClose() { return this->_must_be_close; }

void Client::setServerHost(Server& server) { this->_server = &server; }

void Client::setLastActivity(time_t current_time) { this->_last_activity = current_time; }

void Client::setReadyToSend(bool ready) { this->_ready_to_send = ready; }

void Client::setResponse(std::string response) { this->_response = response; }

void Client::setMustBeClose(bool state) { this->_must_be_close = state; }

void Client::appendBytesSend(int& bytes_send) { this->_bytes_send += bytes_send; }

void Client::appendBytesRead(int& bytes_read) { this->_bytes_read += bytes_read; }

void Client::appendRequest(const char buffer[BUFFER_SIZE], int& bytes_read) { this->_request.append(buffer, bytes_read); }

// Reset

void Client::resetRequest() { this->_request.clear(); }

void Client::resetResponse() { this->_response.clear(); }

void Client::resetBytesRead() { this->_bytes_read = 0; }

void Client::resetBytesSend() { this->_bytes_send = 0; }

// Utils

bool Client::isTimeout(time_t current_time)
{
	if (current_time - this->_last_activity >= TIMEOUT_CLIENT)
		return true;
	return false;
}

bool Client::isPost()
{
	std::stringstream parser(this->_request);
	std::string token;
	
	parser >> token;
	if (token == "POST")
		return true;
	return false;
}

size_t Client::countBoundarySize(std::string boundary_id) {
	size_t pos_end(0);
	size_t pos(0);

	for (int i = 0; i < 2; i++)
		pos = this->_request.find(boundary_id, pos + boundary_id.size());
	pos_end = this->_request.find(boundary_id, pos + boundary_id.size());
	pos += boundary_id.size();
	return pos_end - pos;
}

bool Client::isFull()
{
	size_t body_len(0);
    size_t pos(0);
	std::stringstream parser(this->_request);
	std::string content_type;
	std::string token;
	std::string boundary_id;

	if (this->_request.find("\r\n\r\n") == std::string::npos)
		return false;
	if (this->isPost()) {
		while (content_type != "Content-Type:" && !parser.eof())
			parser >> content_type;
		if (parser.eof())
			return false;
		parser >> token;
		if (token == "application/x-www-form-urlencoded" || token == "plain/text") {
			body_len = this->contentLength();
			if (body_len > this->_server->getConfig().client_max_body_size)
				throw std::exception();
			pos = this->_request.find("\r\n\r\n") + 4;
			while (this->_request[pos++] && (this->_request[pos - 1] != '\r' && this->_request[pos != '\n']))
				body_len--;
			if (body_len != 0)
				return false;
		}
		else if (token == "multipart/form-data;") {
			parser >> token;
			boundary_id = token.substr(9, token.size() - 9);
			for (int i = 0; i < 3; i++) {
				pos = this->_request.find(boundary_id, pos + boundary_id.size());
				if (pos == std::string::npos)
					return false;
			}
			if (countBoundarySize(boundary_id) > this->_server->getConfig().client_max_body_size)
				throw std::exception();
		}
	}
	return true;
}

size_t Client::contentLength()
{
	size_t length(0);
	std::string token;

	if (this->_request.find("POST") != std::string::npos && this->_request.find("Content-Length:") != std::string::npos) {
		std::stringstream parser(this->_request);
		while(token != "Content-Length:" && !parser.eof())
			parser >> token;
		parser >> token;
		length = std::atoi(token.c_str());
	}
	return length;
}
