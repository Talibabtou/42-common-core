#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

# include "utils.h"

class ConfigParser {
public:
	ConfigParser(const char* config_path);
	ConfigParser(const ConfigParser& copy);
	ConfigParser& operator=(const ConfigParser& copy);
	~ConfigParser();
	
	const std::vector<t_config>& getConfigs() const;

private:
	void initDefaultServerConfig(t_config& config);

	void parseServer(std::ifstream& file);
	void parseLine(const std::string& line, t_config& current_config);
	void parseLocation(std::ifstream& file, const std::string& location_line, t_config& current_config);

	std::vector<t_config> _configs;
};

#endif
