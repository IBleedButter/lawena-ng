
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

enum LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

class Logger
{
public:
    Logger(const std::string &logFile);
    ~Logger();

private:
    std::ofstream m_logFile;

    std::string level2string(LogLevel level);
};

#endif // LOGGER_HPP
