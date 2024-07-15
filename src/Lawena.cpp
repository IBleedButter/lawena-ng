#include "Lawena.hpp"

int main(int argc, char **argv)
{
    std::string settingsFile;
    if (argc == 1)
    {
        settingsFile = "lawena.lwf";
    }
    else
    {
        settingsFile = argv[1];
    }
    
    SettingsManager settings(settingsFile);
    
    return EXIT_SUCCESS;
}
