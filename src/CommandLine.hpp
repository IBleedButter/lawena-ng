#pragma once

#include <string>

#include "SettingsManager.hpp"

class CommandLine
{
protected:
    virtual std::string getBuilderStartTF2(const std::string &gamePath) = 0;
    //virtual std::string getBuilderStartHL2(const std::string &gamepath) = 0;
    virtual std::string getBuilderStartSteam(const std::string &steamPath) = 0;
    virtual std::string getBuilderStartHLAE(const std::string &hlaePath, const std::string &gamePath) = 0;
    virtual std::string getBuilderTF2ProcessKiller(void) = 0;
    //virtual std::string getBuilderHL2ProcessKiller(void) = 0;
    virtual std::string getBuilderHLAEProcessKiller(void) = 0;
public:
    virtual bool isRunningTF2(void) = 0;
    virtual std::string getSteamPath(void) = 0;
    virtual bool isValidSteamPath(const std::string &steamPath) = 0;
    virtual std::string getSystemDxLevel(void) = 0;
    virtual void setSystemDxLevel(const std::string &dxlevel) = 0;
    void startTf(SettingsManager cfg);
};
