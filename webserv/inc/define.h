#ifndef DEFINE_HPP
# define DEFINE_HPP

// Includes
# include <iostream>
# include <string>
# include <map>
# include <vector>
# include <iterator>
# include <cstdlib>
# include <cstring>
# include <sys/epoll.h>
# include <exception>
# include <errno.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <signal.h>
# include <netdb.h>
# include <sys/socket.h>
# include <cstdlib>
# include <ctime>
# include <fstream>
# include <sstream>
# include <sys/stat.h>
# include <stdexcept>
# include <sys/wait.h>
#include <algorithm>
#include <cctype>

// Globals
# define TIMEOUT_CLIENT 60
# define TIMEOUT_CHECK_INTERVAL 1
# define MAX_EVENT 21
# define BACKLOG 21
# define BUFFER_SIZE 1024
# define IP_ADDR "0.0.0.0"
# define CGI_TIMEOUT 10
# define PYTHON_PATH "/usr/bin/python3"
# define BASH_PATH "/usr/bin/bash"
# define MAX_CGI_ARGS 9
# define MAX_URI_LENGTH 4096
# define DEFAULT_CLIENT_MAX_BODY_SIZE 1048576
# define CGI_DEFAULT "/cgi-bin/default.py"

// Error pages
# define ERROR_PAGES_PATH "/assets/errors/"

// ASCII
# define GREY "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define ORANGE "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define LIGHTBLUE "\033[36m"
# define WHITE "\033[37m"
# define END "\033[0m"
# define BOLD "\033[1m"
# define ITALIC "\033[3m"
# define UNDERLINE "\033[4m"
# define DEL_LINE "\r\033[2K"

// Debug Mode
#ifdef DEBUG_MODE
# define DEBUG_LOG(level, component, message, server_name) logMessage(level, component, message, server_name)
#else
# define DEBUG_LOG(level, component, message, server_name) ((void)0)
#endif

// Structs
typedef struct s_location {
	std::string path;
	std::vector<std::string> allowed_methods;
	bool autoindex;
	std::string root;
	std::string index;
} t_location;

typedef struct s_config {
	std::string path;
	std::string ip_addr;
	std::string server_name;
	std::string port;
	std::string index;
	size_t client_max_body_size;
	std::map<std::string, t_location> locations;
} t_config;

#endif
