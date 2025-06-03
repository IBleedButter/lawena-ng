#include "Logger.hpp"
#include <iostream>

Logger::Logger(const std::string &logFile)
{

    m_logFile.open(logFile, std::ios::app);

    if (!m_logFile)
    {
        std::cerr << "Logger::Logger(): failed to open file '" << logFile << "'!" << std::endl;
        return;
    }
}

Logger::~Logger()
{
    m_logFile.flush();
    m_logFile.close();
}

std::string Logger::level2string(LogLevel level)
{
    switch (level)
    {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        case CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
    }
}
