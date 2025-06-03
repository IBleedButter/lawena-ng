#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <QString>
#include <cstdint>
#include <string>

class SettingsManager
{
public:
    SettingsManager(const std::string &settingsFile);

    void loadDefaults(void);
    void loadFromFile(void);
    void saveToFile(void);
    void printAll(void);

    /* Getters */
    std::string getSteamDir(void) { return m_steamDir; }
    std::string getTfDir(void) { return m_tfDir; }
    std::string getMovieDir(void) { return m_movieDir; }
    std::uint16_t getWidth(void) { return m_width; }
    std::uint16_t getHeight(void) { return m_height; }
    std::string getLaunchMode(void) { return m_launchMode; }
    std::string getLaunchOptions(void) { return m_launchOptions; }

    /* Setters */
    void setSteamDir(const std::string &steamDir) { m_steamDir = steamDir; }
    void setSteamDir(const QString &steamDir) { m_steamDir = steamDir.toStdString(); }
    void setTfDir(const std::string &tfDir) { m_tfDir = tfDir; }
    void setTfDir(const QString &tfDir) { m_tfDir = tfDir.toStdString(); }
    void setMovieDir(const std::string &movieDir) { m_movieDir = movieDir; }
    void setMovieDir(const QString &movieDir) { m_movieDir = movieDir.toStdString(); }
    void setWidth(const std::uint16_t width) { m_width = width; }
    void setWidth(const QString &width) { m_width = width.toUInt(); }
    void setHeight(const std::uint16_t height) { m_height = height; }
    void setHeight(const QString &height) { m_height = height.toUInt(); }
    void setLaunchMode(const std::string &launchMode) { m_launchMode = launchMode; }
    void setLaunchMode(const QString &launchMode) { m_launchMode = launchMode.toStdString(); }
    void setLaunchOptions(const std::string &launchOptions) { m_launchOptions = launchOptions; }
    void setLaunchOptions(const QString &launchOptions) { m_launchOptions = launchOptions.toStdString(); }

private:
    std::string m_settingsFile;

    std::string m_steamDir{""};
    std::string m_tfDir{""};
    std::string m_movieDir{""};

    std::uint16_t m_width{0};
    std::uint16_t m_height{0};

    std::string m_launchMode{""};
    std::string m_launchOptions{""};
};

#endif // SETTINGSMANAGER_HPP
