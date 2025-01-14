#pragma once
#include "Threat.h"
#include <iostream>

class ThreatView {
public:
    void displayThreat(const Threat& threat);
    void displayMessage(const std::string& message);
    void displayMenu();
    void promptForInput(const std::string& prompt, std::string& input);
};