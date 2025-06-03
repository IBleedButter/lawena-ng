#include "SettingsManager.hpp"
#include <fstream>
#include <iostream>
#include <string>

SettingsManager::SettingsManager(const std::string &settingsFile) : m_settingsFile(settingsFile)
{
    loadDefaults();
    loadFromFile();
    printAll();
}

void SettingsManager::loadDefaults(void)
{
    m_steamDir = "";
    m_tfDir = "";
    m_movieDir = "";
    m_height = 1920;
    m_width = 1080;
    m_launchMode = "tf2";
    m_launchOptions = "-novid -console";
}

void SettingsManager::loadFromFile(void)
{
    /* Open file */
    std::ifstream settingsFile(m_settingsFile, std::ios::in);

    if (!settingsFile)
    {
        // TODO: replace with Qt6 MessageBox

        std::cerr << "Failed to read settings from file '" << m_settingsFile << "'!" << std::endl;
    }

    /* Read from file */
    std::string buffer;

    while (std::getline(settingsFile, buffer))
    {
        /* Ignore comments */
        if (buffer[0] == '#' || buffer[0] == ';')
        {
            continue;
        }

        /* Don't care about sections */

        /* Ignore non-key-value pairs */
        std::size_t pos = buffer.find('=');

        if (pos == std::string::npos)
        {
            continue;
        }

        /* Extract the key */
        std::string key = buffer.substr(0, pos);
        key.erase(key.find_last_not_of(" \n\r\t") + 1);

        /* Extract the value */
        std::string value = buffer.substr(pos + 1);
        value.erase(0, value.find_first_not_of(" \n\r\t"));

        /* We only care about certain keys */
        if (key == "SteamDir")
        {
            setSteamDir(value);
        } else if (key == "TfDir")
        {
            setTfDir(value);
        } else if (key == "MovieDir")
        {
            setMovieDir(value);
        } else if (key == "Width")
        {
            setHeight(std::stoi(value));
        } else if (key == "Height")
        {
            setWidth(std::stoi(value));

        } else if (key == "LaunchMode")
        {
            setLaunchMode(value);
        } else if (key == "LaunchOptions")
        {
            setLaunchOptions(value);
        }
    }

    /* Close file */
    settingsFile.close();
}

void SettingsManager::saveToFile(void)
{
    /* Open file */
    std::ofstream settingsFile(m_settingsFile, std::ios::out);

    if (!settingsFile)
    {
        std::cerr << "SettingsManager::saveToFile(): failed to open file '" << m_settingsFile << "'!";
        return;
    }

    /* Write to file */
    settingsFile << "SteamDir = " << m_steamDir << '\n';
    settingsFile << "TfDir = " << m_tfDir << '\n';
    settingsFile << "MovieDir = " << m_movieDir << '\n';
    settingsFile << "Width = " << m_width << '\n';
    settingsFile << "Height = " << m_height << '\n';
    settingsFile << "LaunchMode = " << m_launchMode << '\n';
    settingsFile << "LaunchOptions = " << m_launchOptions << '\n';

    /* Close file */
    settingsFile.flush();
    settingsFile.close();
}

void SettingsManager::printAll(void)
{
    std::cout << "SteamDir = " << m_steamDir << '\n';
    std::cout << "TfDir = " << m_tfDir << '\n';
    std::cout << "MovieDir = " << m_movieDir << '\n';
    std::cout << "Width = " << m_width << '\n';
    std::cout << "Height = " << m_height << '\n';
    std::cout << "LaunchMode = " << m_launchMode << '\n';
    std::cout << "LaunchOptions = " << m_launchOptions << '\n';

    std::cout.flush();
}
