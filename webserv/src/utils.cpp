#include "utils.h"
#include "Webserv.hpp"

// Logs

std::string getTime()
{
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	std::time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "[%Y-%a-%d-%b][%H:%M:%S]", timeinfo);
	return std::string(buffer);
}

std::string getLogPrefix(LogLevel level, const std::string& component, const std::string& server_name = "")
{
	std::string prefix = getTime();

	if (!server_name.empty())
		prefix += "[" + server_name + "]";
	if (!component.empty())
		prefix += "[" + component + "]";
	switch (level) {
		case ERROR:
			return RED + prefix + END + RED;
		case DEBUG:
			return BLUE + prefix + END + BLUE;
		default:
			return prefix + END;
	}
}

void logMessage(LogLevel level, const std::string& component, const std::string& message, const std::string& server_name)
{
	#ifndef DEBUG_MODE
		if (level == DEBUG)
			return;
	#endif

	std::string prefix = getLogPrefix(level, component, server_name);

	if (level == ERROR)
		std::cerr << BOLD << prefix << " " << ITALIC << message << END << std::endl;
	else
		std::cout << BOLD << prefix << " " << ITALIC << message << END << std::endl;
}

// Files

bool isValidFile(const char* filepath)
{
	if (!filepath) {
		logMessage(ERROR, "utils", "NULL filepath", "");
		return false;
	}
	std::string path(filepath);
	if (path.length() < 5 || path.substr(path.length() - 5) != ".conf") {
		logMessage(ERROR, "utils", "File must have .conf extension", "");
		return false;
	}
	struct stat buffer;
	if (stat(filepath, &buffer) != 0) {
		logMessage(ERROR, "utils", "File does not exist: " + std::string(strerror(errno)), "");
		return false;
	}
	if (!S_ISREG(buffer.st_mode)) {
		logMessage(ERROR, "utils", "Not a regular file", "");
		return false;
	}
	if (access(filepath, R_OK) != 0) {
		logMessage(ERROR, "utils", "No read permission: " + std::string(strerror(errno)), "");
		return false;
	}
	std::ifstream file(filepath);
	if (!file.is_open()) {
		logMessage(ERROR, "utils", "Cannot open file: " + std::string(strerror(errno)), "");
		return false;
	}
	file.seekg(0, std::ios::end);
	if (file.tellg() == 0) {
		file.close();
		logMessage(ERROR, "utils", "Config file is empty", "");
		return false;
	}
	file.close();
	return true;
}

void sig_handler(int signum)
{
	std::cout << DEL_LINE << std::flush;
	if (signum == SIGINT || signum == SIGTSTP)
		Webserv::getWebserv(NULL).stopWebserv();
}

std::string readFileToString(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
			if (errno == EACCES) {
					throw std::runtime_error("Permission denied: " + filename);
			} else if (errno == ENOENT) {
					throw std::runtime_error("File not found: " + filename);
			} else {
					throw std::runtime_error("Unable to open file: " + filename);
			}
	}
	std::ostringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

int getFileSize(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	file.seekg(0, std::ios::end);
	return file.tellg();
}

unsigned long djb2Hash(const std::string& str)
{
	unsigned long hash = 5381;
	int c;
	for (size_t i = 0; i < str.length(); i++) {
		c = str[i];
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	}
	return hash;
}

std::string getFileModification(const struct stat& fileInfo)
{
	char buffer[128];
	struct tm* timeinfo = gmtime(&fileInfo.st_mtime);
	strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeinfo);
	return std::string(buffer);
}

int compareTime(std::string& old_date, std::string& new_date) {
	struct tm old_time = {};
	struct tm new_time = {};
	strptime(old_date.c_str(), "%a, %d %b %Y %H:%M:%S GMT", &old_time);
	strptime(new_date.c_str(), "%a, %d %b %Y %H:%M:%S GMT", &new_time);
	time_t old_time_t = timegm(&old_time);
	time_t new_time_t = timegm(&new_time);
	return old_time_t < new_time_t;
}

std::string getFileExtension(const std::string& filename)
{
	std::string::size_type dot = filename.find_last_of('.');

	if (dot == std::string::npos)
		return "";
	return filename.substr(dot + 1);
}

bool checkFileExist(const std::string& path)
{
	struct stat st;

	if (stat(path.c_str(), &st) == -1)
		return false;
	return true;
}

bool checkScriptPermission(const std::string& binary_path, const std::string& script_path)
{
	struct stat binary_st;
	struct stat script_st;

	if (stat(binary_path.c_str(), &binary_st) == -1 || !S_ISREG(binary_st.st_mode) || !(binary_st.st_mode & S_IXUSR || binary_st.st_mode & S_IXGRP)
			|| stat(script_path.c_str(), &script_st) == -1 || !S_ISREG(script_st.st_mode) || !(binary_st.st_mode & S_IRUSR || binary_st.st_mode & S_IRGRP))
		return false;
	return true;
}

std::string scriptSelector(const std::string& path)
{
	if (getFileExtension(path) == "py")
		return PYTHON_PATH;
	else if (getFileExtension(path) == "sh")
		return BASH_PATH;
	else
		return "";
}

size_t findWebsiteRoot(const std::string& str, char ch) {
	size_t firstPos = str.find(ch);
	if (firstPos == std::string::npos)
		return std::string::npos;
	size_t secondPos = str.find(ch, firstPos + 1);
	return secondPos;
}

bool CheckAccept(const std::string& accept, const std::string& contentType) {
	std::string fileType = contentType.substr(0, contentType.find('/'));
	if (accept.find("*/*") != std::string::npos || accept.find(fileType + "/*") != std::string::npos || accept.find(contentType) != std::string::npos)
		return true;
	return false;
}

bool checkWritePermission(const std::string& path) {
	struct stat st;
	if (stat(path.c_str(), &st) == -1 || !S_ISDIR(st.st_mode) || !(st.st_mode & S_IWUSR))
		return false;
	return true;
}

std::string sanitizePath(const std::string& path)
{
	std::string sanitized;
	bool inQuotes = false;
	
	for (size_t i = 0; i < path.length(); i++) {
		char c = path[i];
		if (c == '"') {
			inQuotes = !inQuotes;
			continue;
		}
		
		if (inQuotes || !std::isspace(c)) {
			sanitized += c;
		} else if (std::isspace(c)) {
			sanitized += "%20";
		}
	}
	return sanitized;
}

bool isValidFilename(const std::string& filename)
{
	if (filename.find('/') != std::string::npos ||
		filename.find('\\') != std::string::npos ||
		filename.find("..") != std::string::npos) {
		return false;
	}
	for (size_t i = 0; i < filename.length(); i++) {
		char c = filename[i];
		if (!std::isalnum(c) && c != '-' && c != '_' && c != '.' && c != ' ')
			return false;
	}
	return true;
}
