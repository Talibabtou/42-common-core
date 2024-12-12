#include "Webserv.hpp"

int main(int ac, char* av[])
{
	const char* config_path;

	try {
		if (ac > 2) {
			logMessage(ERROR, "main", "Usage: " + std::string(av[0]) + " [config_file.conf]", "");
			return 1;
		}
		config_path = (ac == 2) ? av[1] : "config/default.conf";
		if (!isValidFile(config_path))
			return 1;
		logMessage(INFO, "main", "Starting webserver with config: " + std::string(config_path), "");
		Webserv::getWebserv(config_path).runWebserv();
	}
	catch (const std::exception& e) {
		logMessage(ERROR, "main", "Fatal error: " + std::string(e.what()), "");
		return 1;
	}
	return 0;
}
