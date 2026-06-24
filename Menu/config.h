#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <iomanip>

class CConfig
{
protected:
    class C_ConfigItem
    {
    public:
        std::string name;
        void* pointer;
        std::string type;
        C_ConfigItem(std::string name, void* pointer, std::string type)
        {
            this->name = name;
            this->pointer = pointer;
            this->type = type;
        }
    };
    std::vector <C_ConfigItem*> items;
private:
    void AddItem(void* pointer, const char* name, const std::string& type);
    void setup_item(int*, int, const std::string&);
    void setup_item(bool*, bool, const std::string&);
    void setup_item(float*, float, const std::string&);
    void setup_item(double*, double, const std::string&);
    void setup_item(std::vector< int >*, int, const std::string&);
    void setup_item(std::vector< std::string >*, const std::string&);
    void setup_item(std::string*, const std::string&, const std::string&);
    void SetupAimbot();
    void SetupVisuals();
    void SetupChams();
    void SetupExploits();
    void SetupMisc();
public:
    void Initialize();
    void LoadSettings(const std::string& szIniFile);
    void SaveSettings(const std::string& szIniFile);
    std::string folder;
};
extern CConfig* Config;
