#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <vector>

class SettingsManager
{
public:
    SettingsManager(const std::string &settingsFile);
    void loadDefaults(void);
    int loadFromFile(void);
    int saveToFile(void);
    int saveToCfg(void);
    void printProperties(void);
private:
    std::string filename;

    std::unordered_map<std::string, std::string> properties;

    #define DEFAULTS_SIZE 42
    const std::string defaults[DEFAULTS_SIZE][2] = 
    {
        { "TfDir", "" },
        { "MovieDir", "" },
        { "SteamDir", "" },
        { "AltSteamDir", "" },
        { "Width", "1920" },
        { "Height", "1080" },
        { "Framerate", "120" },
        { "DxLevel", "98" },
        { "Hud", "hud_medic" },
        { "Skybox", "Default" },
        { "CustomResources", "no_announcer_voices.vpk|no_applause_sounds.vpk|no_domination_sounds.vpk" },
        { "ViewmodelSwitch", "on" },
        { "ViewmodelFov", "90" },
        { "MotionBlur", "false" },
        { "Crosshair", "true" },
        { "CrosshairSwitch", "false" },
        { "CombatText", "true" },
        { "Hitsounds", "true" },
        { "Voice", "false" },
        { "SteamCloud", "false" },
        { "Condebug", "true" },
        { "HudMinmode", "false" },
        { "HudPlayerModel", "false" },
        { "Particles", "" },
        { "LaunchTimeout", "60" },
        { "Insecure", "true" },
        { "VdmSkipMode", "SKIP_AHEAD" },
        { "VdmSkipStartCommand", "demo_timescale 5" },
        { "VdmSkipStopCommand", "demo_timescale 1" },
        { "VdmTickPadding", "500" },
        { "InstallFonts", "true" },
        { "CopyUserConfig", "true" },
        { "CustomSettings", "// Custom User Settings" },
        { "SourceRecorderVideoFormat", "tga" },
        { "SourceRecorderAudioFormat", "wav" },
        { "SourceRecorderJpegQuality", "50" },
        { "DeleteBackupsWhenRestoring", "false" },
        { "BigFolderMBThreshold", "200" },
        { "SetSystemLookAndFeel", "true" },
        { "HlaePath", "" },
        { "LaunchMode", "tf2" },
        { "LaunchOptions", "-novid -console" }
    };
};
