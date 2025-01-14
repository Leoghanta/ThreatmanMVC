#include "Threat.h"


Threat::Threat(std::string id, std::string level, std::string desc, time_t time) {
	setId(id);
	setLevel(level);
	setDesc(desc);
	setTime(time);
}


//Polymorphed so time can be added as a string.
Threat::Threat(std::string id, std::string level, std::string desc, std::string time) {
	setId(id);
	setLevel(level);
	setDesc(desc);
	setTime(time);
}

std::string Threat::getId() const {
	return threatId;
}

std::string Threat::getLevel() const {
	return threatLevel;
}

std::string Threat::getDesc() const {
	return threatDescription;
}

std::string Threat::getTime() const {
	//localtime is deprecated: use localtime_s (https://stackoverflow.com/questions/14386923/localtime-vs-localtime-s-and-appropriate-input-arguments)
	struct tm localTime;
	localtime_s(&localTime, &timestamp);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%d-%m-%Y", &localTime);
	return std::string(buffer);
}



void Threat::setId(const std::string& id) {
	if (id.empty()) {
		throw std::invalid_argument("ID can not be left blank!");
	}
	threatId = id;
}
void Threat::setLevel(const std::string& level) {
	if (level.empty()) {
		throw std::invalid_argument("Threat Level can not be left blank!");
	}
	if (!validateThreatLevel(level)) {
		throw std::invalid_argument("Invalid Level:: Valid levels are Low, Medium, High, Critical");
	}
	threatLevel = level;
}

void Threat::setDesc(const std::string& desc) {
	if (desc.empty()) {
		throw std::invalid_argument("Description can not be left blank!");
	}
	threatDescription = desc;
}

void Threat::setTime(const time_t time) {
	timestamp = time;
}

void Threat::setTime(const std::string& time) {
	//from https://www.geeksforgeeks.org/how-to-convert-string-to-date-in-cpp/

	tm tm = {};
	std::istringstream ss(time);
	ss >> std::get_time(&tm, "%d-%m-%Y");
	if (ss.fail() || tm.tm_year < 0) {
		throw std::invalid_argument("Date is not correctly formatted, use dd-mm-yyyy");
	}
	timestamp = mktime(&tm);

}

bool Threat::validateThreatLevel(const std::string& level) {
	for (const std::string& validLevel : validThreatLevels) {
		if (level == validLevel) {
			return true;
		}
	}
	return false;
}