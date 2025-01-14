#pragma once
#include <string>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include <iomanip>


class Threat {
private:
    std::string threatId;
    std::string threatLevel;
    std::string threatDescription;
    time_t timestamp;

    std::string validThreatLevels[4] = { "Low", "Medium", "High", "Critical" };
    
    bool validateThreatLevel(const std::string& level);

public:
    Threat(std::string id, std::string level, std::string desc, time_t time);
    Threat(std::string id, std::string level, std::string desc, std::string time);

    std::string getId() const;
    std::string getLevel() const;
    std::string getDesc() const;
    std::string getTime() const;

    void setId(const std::string& id);
    void setLevel(const std::string& level);
    void setDesc(const std::string& desc);
    void setTime(const time_t time);
    void setTime(const std::string& time);


};