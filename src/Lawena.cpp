#include "Lawena.hpp"

int main(int argc, char **argv)
{
    std::string filename;

    if (argc == 1)
    {
        // No arguments were given: load default file
        filename = "lawena.lwf";
    }

    if (argc >= 2)
    {
        // Arguments were given: load from argv
        filename = argv[1];
    }

    SettingsManager settings(filename);

    std::cout << "=== lawena-ng 0.0.1 === " << std::endl;
    std::cout << "Use 'help' for a list of commands" << std::endl;
    std::string buffer;
    while (true)
    {
        std::cout << ">> ";

        (void) std::getline(std::cin, buffer);

        if (buffer.compare("help") == 0)
        {
            std::cout << "help - prints this menu" << std::endl;
            std::cout << "print - prints settings" << std::endl;
            std::cout << "save - saves settings to file" << std::endl;
            std::cout << "exit - exits lawena-ng" << std::endl << std::endl;
        }

        else if (buffer.compare("print") == 0)
        {
            settings.PrintProperties();
            std::cout << std::endl;
        }

        else if (buffer.compare("save") == 0)
        {
            settings.SaveToFile();
            std::cout << "[INFO] saving settings..." << std::endl << std::endl;
        }

        else if (buffer.compare("exit") == 0 || buffer.compare("quit") == 0)
        {
            std::cout << "Exiting!" << std::endl << std::endl;
            break;
        }

        // Need this or Ctrl+D / EOF puts program in infinite loop
        else if (buffer.compare("") == 0)
        {
            std::cout << std::endl << std::endl;
            break;
        }

        else
        {
            std::cout << "'" << buffer << "' is not a valid command!" << std::endl << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
