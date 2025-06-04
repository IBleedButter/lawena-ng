
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <string>

enum LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

class Logger : public QObject
{
    Q_OBJECT

public:
    Logger(QObject *parent = nullptr) : QObject(parent), m_logMessages(new QString()) {}

    void log(LogLevel level, const std::string &message);

    QSharedPointer<QString> getLogMessages(void) const { return m_logMessages; }

signals:
    void logUpdated(const QString &newLogString);

private:
    QSharedPointer<QString> m_logMessages;

    std::string level2string(LogLevel level);
};

#endif // LOGGER_HPP
