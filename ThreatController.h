#pragma once
#include "Threat.h"
#include "ThreatView.h"
#include <vector>
#include <algorithm>
#include <fstream>

class ThreatController {
private:
	std::vector<Threat> threats;
	ThreatView view;
public:
	void addThreat(const std::string& id, const std::string& level, const std::string& desc, const std::string& time);
	void updateThreat(const std::string& id, const std::string& newlevel, const std::string& newdesc);
	void listThreats();
	void listThreatsByLevel(const std::string& level);
	void removeThreat(const std::string& id);
	void saveThreatsToFile(const std::string& filename);
	void loadThreatsFromFile(const std::string& filename);
	void runProgram();
};