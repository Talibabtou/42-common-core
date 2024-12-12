#include "ConfigParser.hpp"

// Constructors & Destructor

ConfigParser::ConfigParser(const char* config_path)
{
	std::ifstream file(config_path);

	if (!file.is_open()) {
		logMessage(ERROR, "ConfigParser", "open file: " + std::string(strerror(errno)), "");
		throw;
		}
	std::string line;
	while (std::getline(file, line)) {
		if (line.find("server {") != std::string::npos)
			parseServer(file);
	}
	file.close();
}

ConfigParser::ConfigParser(const ConfigParser& copy) { *this = copy; }

ConfigParser& ConfigParser::operator=(const ConfigParser& copy)
{
	if (this != &copy)
		this->_configs = copy._configs;
	return *this;
}

ConfigParser::~ConfigParser() {}

// Initialization

void ConfigParser::initDefaultServerConfig(t_config& config)
{
	config.path = "";
	config.ip_addr = "127.0.0.1";
	config.server_name = "";
	config.port = "";
	config.index = "index.html";
	config.client_max_body_size = DEFAULT_CLIENT_MAX_BODY_SIZE;

	t_location default_location;
	default_location.path = "/";
	default_location.root = "./";
	default_location.index = config.index;
	default_location.autoindex = false;
	default_location.allowed_methods.push_back("GET");

	config.locations.clear();
	config.locations["/"] = default_location;
}

// Parsing

void ConfigParser::parseServer(std::ifstream& file)
{
	t_config current_config;
	initDefaultServerConfig(current_config);

	std::string line;
	try {
		while (std::getline(file, line)) {
			if (line.find("}") != std::string::npos) {
				_configs.push_back(current_config);
				return;
			}
			if (line.find("location") != std::string::npos) {
				parseLocation(file, line, current_config);
				continue;
			}
			parseLine(line, current_config);
		}
	} catch (const std::exception& e) {
		logMessage(ERROR, "ConfigParser", "Invalid server configuration, skipping server block", "");
		while (std::getline(file, line))
			if (line.find("}") != std::string::npos)
				break;
		return;
	}
}

void ConfigParser::parseLocation(std::ifstream& file, const std::string& location_line, t_config& current_config)
{
	t_location location;
	std::string line;

	std::istringstream iss(location_line);
	std::string dummy, path;
	iss >> dummy >> path;

	if (!path.empty() && path[path.length() - 1] == '{')
		path = path.substr(0, path.length() - 1);

	location.path = path;
	location.autoindex = false;

	while (std::getline(file, line)) {
		if (line.find("}") != std::string::npos)
			break;

		std::istringstream line_stream(line);
		std::string directive;
		line_stream >> directive;

		if (directive == "allow_methods") {
			std::string method;
			while (line_stream >> method) {
				if (!method.empty() && method[method.length() - 1] == ';')
					method = method.substr(0, method.length() - 1);
				location.allowed_methods.push_back(method);
			}
		}
		else {
			std::string value;
			line_stream >> value;
			if (value.empty() || value[value.length() - 1] != ';')
				throw std::runtime_error("Missing semicolon in location block directive: " + directive);
			value = value.substr(0, value.length() - 1);
			if (directive == "autoindex")
				location.autoindex = (value == "on");
			else if (directive == "root")
				location.root = value;
			else if (directive == "index")
				location.index = value;
			else
				throw std::runtime_error("Unknown directive in location block: " + directive);
		}
	}
	if (location.index.empty() && !current_config.index.empty())
		location.index = current_config.index;
	current_config.locations[path] = location;
}

void ConfigParser::parseLine(const std::string& line, t_config& current_config)
{
	std::istringstream iss(line);
	std::string directive;
	iss >> directive;

	if (directive.empty())
		return;

	std::string value;
	iss >> value;
	
	if (value.empty())
		throw std::runtime_error("Invalid directive");
	if (value[value.length() - 1] != ';')
		throw std::runtime_error("Invalid directive");

	value = value.substr(0, value.length() - 1);

	std::string extra;
	if (iss >> extra)
		throw std::runtime_error("Invalid directive");

	if (directive == "listen")
		current_config.port = value;
	else if (directive == "server_name")
		current_config.server_name = value;
	else if (directive == "host")
		current_config.ip_addr = value;
	else if (directive == "root")
		current_config.path = value;
	else if (directive == "index")
		current_config.index = value;
	else if (directive == "client_max_body_size")
		current_config.client_max_body_size = std::atoi(value.c_str());
	else {
		throw std::runtime_error("Invalid directive");
	}
}

// Getter

const std::vector<t_config>& ConfigParser::getConfigs() const { return _configs; }
