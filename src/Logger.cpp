#include "Logger.hpp"

#include <iostream>

void Logger::log(LogLevel level, const std::string &message)
{
    /* Get the current datetime */
    time_t now = time(0);
    tm *timeinfo = localtime(&now);
    if (timeinfo == nullptr)
    {
        return;
    }
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    /* Construct log message */
    std::string logMessage;
    logMessage += "[";
    logMessage += timestamp;
    logMessage += "] ";
    logMessage += level2string(level);
    logMessage += ": ";
    logMessage += message;

    /* Print it out to stdout */
    std::cout << logMessage << std::endl;

    /* Append it to the list as well */
    m_logMessages->append(QString::fromStdString(logMessage) + '\n');

    emit logUpdated(*m_logMessages);
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
