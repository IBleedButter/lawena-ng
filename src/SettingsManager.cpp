#include "SettingsManager.hpp"

SettingsManager::SettingsManager(const std::string &settingsFile)
{
    filename = settingsFile;

    // Load default settings from memory
    LoadDefaults();

    // Load settings from file
    if (LoadFromFile() != EXIT_SUCCESS)
    {
        std::cerr << "[WARNING] Failed to load settings from file '" << settingsFile << "': falling back to defaults" << std::endl;
    } else
    {
        // Failed to load file: do nothing, we already loaded defaults
        std::cout << "[INFO] Loaded settings from file '" << settingsFile << "'" << std::endl;
    }
}

void SettingsManager::LoadDefaults(void)
{
    for (int i = 0; i < DEFAULTS_SIZE; i++)
    {
        properties[defaults[i][0]] = defaults[i][1];
    }
}

int SettingsManager::LoadFromFile(void)
{
    // Open file handle
    std::ifstream fp;

    fp.open(filename);

    if (!fp.is_open())
    {
        return EXIT_FAILURE;
    }

    // Iterate through file
    std::string buffer;

    while (std::getline(fp, buffer))
    {
        // Skip comments
        if (buffer[0] == '#') { continue; }

        // Only add valid options
        for (int i = 0; i < DEFAULTS_SIZE; i++)
        {
            if (buffer.compare(defaults[i][0]) == 0)
            {
                // Split string at '='
                size_t pos = buffer.find('=');
                if (pos == std::string::npos) { continue; }
                std::string key = buffer.substr(0, pos);
                std::string value = buffer.substr(pos + 1);
                properties[key] = value;
            }
        }
    }

    // Close file handle
    fp.close();

    return EXIT_SUCCESS;
}

int SettingsManager::SaveToFile(void)
{
    // Open file handle
    std::ofstream fp;

    fp.open(filename);

    if (!fp.is_open())
    {
        return EXIT_FAILURE;
    }

    // Iterate through properties and write to file
    for (const auto& [key, value] : properties)
    {
        fp << key << "=" << value << std::endl;
    }

    // Close file handle
    fp.close();

    return EXIT_SUCCESS;
}

void SettingsManager::PrintProperties(void)
{
    for (const auto& [key, value] : properties)
    {
        std::cout << key << "=" << value << std::endl;
    }
}
