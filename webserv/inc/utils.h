#ifndef UTILS_HPP
# define UTILS_HPP

# include "define.h"

enum LogLevel {
	INFO,
	ERROR,
	DEBUG
};

// Logging

std::string getTime();
std::string getLogPrefix(LogLevel level, const std::string& component, const std::string& server_name);
void logMessage(LogLevel level, const std::string& component, const std::string& message, const std::string& server_name);

// Files

bool isValidFile(const char* filepath);
std::string readFileToString(const std::string& filename);
int getFileSize(const std::string& filename);
unsigned long djb2Hash(const std::string& str);
std::string getFileModification(const struct stat& fileInfo);
std::string getFileExtension(const std::string& filename);
bool checkFileExist(const std::string& path);
bool checkWritePermission(const std::string& file_path);
bool checkScriptPermission(const std::string& binary_path, const std::string& script_path);
std::string scriptSelector(const std::string& path);
size_t findWebsiteRoot(const std::string& str, char ch);
bool CheckAccept(const std::string& accept, const std::string& contentType);
std::string sanitizePath(const std::string& path);
bool isValidFilename(const std::string& filename);

// Time

int compareTime(std::string& old_date, std::string& new_date);

// Signal

void sig_handler(int signum);

// Templates

template<typename T>
std::string numberToString(T number) {
	std::stringstream ss;
	ss << number;
	return ss.str();
}

#endif
