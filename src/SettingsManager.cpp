#include "SettingsManager.hpp"

SettingsManager::SettingsManager(const std::string &settingsFile)
{
    filename = settingsFile;

    // Load default settings from memory
    loadDefaults();

    // Load settings from file
    if (loadFromFile() != EXIT_SUCCESS)
    {
        // Failed to load file, but that's fine: we already loaded defaults
        std::cerr << "[WARNING] Failed to load settings from file '" << settingsFile << "': falling back to defaults" << std::endl;
    }
    else
    {
        std::cout << "[INFO] Loaded settings from file '" << settingsFile << "'" << std::endl;
    }
}

void SettingsManager::loadDefaults(void)
{
    for (int i = 0; i < DEFAULTS_SIZE; i++)
    {
        properties[defaults[i][0]] = defaults[i][1];
    }
}

int SettingsManager::loadFromFile(void)
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

int SettingsManager::saveToFile(void)
{
    // Open file handle
    std::ofstream fp;

    fp.open(filename);

    if (!fp.is_open())
    {
        return EXIT_FAILURE;
    }

    // Iterate through properties and write to file
    for (const auto &[key, value] : properties)
    {
        fp << key << "=" << value << std::endl;
    }

    // Close file handle
    fp.close();

    return EXIT_SUCCESS;
}

int SettingsManager::saveToCfg(void)
{
    // Open file handle
    std::ofstream fp;

    fp.open("settings.cfg");

    if (!fp.is_open())
    {
        return EXIT_FAILURE;
    }

    std::vector<std::string> lines;
    lines.push_back("alias recframerate host_framerate " + properties["Framerate"]);
    lines.push_back("alias currentfpsup 240fps");
    lines.push_back("alias currentfpsdn 60fps");
    lines.push_back("mat_picmip -10");
    lines.push_back("cl_autorezoom 0");
    lines.push_back("cl_autoreload 0");
    lines.push_back("hud_saytext_time 0");
    lines.push_back("net_graph 0");
    lines.push_back("alias voice_menu_1 \"\"");
    lines.push_back("alias voice_menu_2 \"\"");
    lines.push_back("alias voice_menu_3 \"\"");
    lines.push_back("alias +taunt \"\"");
    lines.push_back("alias +context_action \"\"");
    lines.push_back("cl_showfps 0");
    lines.push_back("volume 1");
    lines.push_back("hud_fastswitch 1");
    lines.push_back("cl_hud_playerclass_playermodel_showed_confirm_dialog 1");
    lines.push_back("engine_no_focus_sleep 0");
    lines.push_back("cl_spec_carrieditems 0");
    lines.push_back("tf_hud_target_id_disable_floating_health 1");
    lines.push_back("cl_crosshair_red 255");
    lines.push_back("cl_crosshair_green 255");
    lines.push_back("cl_crosshair_blue 255");
    lines.push_back("alias net_graph \"\"");
    lines.push_back("alias cl_showfps \"\"");
    lines.push_back("alias voice_enable \"\"");
    lines.push_back("cl_jiggle_bone_framerate_cutoff 0");
    lines.push_back("alias cl_jiggle_bone_framerate_cutoff \"\"");
    lines.push_back("violence_agibs 1");
    lines.push_back("violence_hgibs 1");
    lines.push_back("violence_ablood 1");
    lines.push_back("violence_hblood 1");
    lines.push_back("alias violence_agibs \"\"");
    lines.push_back("alias violence_hgibs \"\"");
    lines.push_back("alias violence_ablood \"\"");
    lines.push_back("alias violence_hblood \"\"");
    lines.push_back("r_portalsopenall 1");
    lines.push_back("alias r_portalsopenall \"\"");
    lines.push_back("hud_saytext_time 0");
    lines.push_back("alias hud_saytext_time \"\"");
    lines.push_back("tf_use_min_viewmodels 0");
    lines.push_back("alias tf_use_min_viewmodels \"\"");
    lines.push_back("gameui_preventescapetoshow");

    for (const auto& line : lines)
    {
        fp << line << std::endl;
    }

    // Close file handle
    fp.close();

    return EXIT_SUCCESS;
}

void SettingsManager::printProperties(void)
{
    for (const auto& [key, value] : properties)
    {
        std::cout << key << "=" << value << std::endl;
    }
}
