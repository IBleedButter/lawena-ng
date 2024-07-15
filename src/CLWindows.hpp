#pragma once

#include "CommandLine.hpp"

class CLWindows : public CommandLine
{
private:
    std::string tf2 = "tf_win64.exe";
    //std::string hl2 = "hl2.exe";
public:
    std::string getBuilderStartTF2(const std::string &gamePath) override;
    //std::string getBuilderStartHL2(const std::string &gamePath) override;
    std::string getBuilderStartSteam(const std::string &steamPath) override;
    std::string getBuilderStartHLAE(const std::string &hlaePath, const std::string &gamePath) override;
    std::string getBuilderTF2ProcessKiller(void) override;
    //std::string getBuilderHL2ProcessKiller(void) override;
    std::string getBuilderHLAEProcessKiller(void) override;
    std::string getSteamPath(void) override;
    bool isValidSteamPath(const std::string &steamPath) override;
    std::string getSystemDxLevel(void) override;
    void setSystemDxLevel(const std::string &dxlevel) override;
    bool isRunningTF2(void) override;
};
