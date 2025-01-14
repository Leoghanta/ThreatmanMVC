#include "ThreatController.h"


void ThreatController::addThreat(const std::string& id, const std::string& level, const std::string& desc, const std::string& time) {
	for (const Threat t : threats) {
		if (t.getId() == id) {
			view.displayMessage("Thread " + id + " already exists in the system.");
			return;
		}
	}
	try {
		threats.push_back(Threat(id, level, desc, time));
		view.displayMessage("Threat " + id + " has been logged.");
	}
	catch (const std::exception ex){
		view.displayMessage(ex.what());
	}
}

void ThreatController::updateThreat(const std::string& id, const std::string& newlevel, const std::string& newdesc) {
	for (Threat t : threats) {
		if (t.getId() == id) {
			try {
				t.setLevel(newlevel);
				t.setDesc(newdesc);
				view.displayMessage("Thread has been updated.");
			}
			catch (const std::exception ex)
			{
				view.displayMessage(ex.what());
			}
		}
	}
	view.displayMessage("Thread ID " + id + " was not found on the system.");
}

void ThreatController::listThreats() {
	if (threats.empty()) {
		view.displayMessage("No threats on the system!");
	}
	else {
		view.displayMessage("___Logged Threats___");
		for (Threat t : threats) {
			view.displayThreat(t);
		}
	}
}


void ThreatController::listThreatsByLevel(const std::string& level) {
	int numberOfThreats = 0;
	if (threats.empty()) {
		view.displayMessage("No threats on the system!");
	}
	else {
		view.displayMessage("___" + level + " Level Threats___");
		for (Threat t : threats) {
			if (t.getLevel() == level) {
				view.displayThreat(t);
				numberOfThreats++;
			}
		}
		if (numberOfThreats < 1) {
			view.displayMessage("There are no " + level + " level threats to display.");
		}
	}
}

void ThreatController::removeThreat(const std::string& id) {
	bool removed = false;
	for (int i = 0; i < threats.size(); i++) {
		if (threats[i].getId() == id) {
			threats.erase(threats.begin() + i);
			view.displayMessage("Threat ID " + id + " has been removed.");
			removed = true;
			break;
		}
	}

	if (!removed) {
		view.displayMessage("Threat ID " + id + " was not found on the system.");
	}
}


void ThreatController::saveThreatsToFile(const std::string& filename) {
	int items = 0;
	std::ofstream file(filename);
	if (!file) {
		view.displayMessage("Error: Unable to open file.");
		return;
	}

	for (const Threat t : threats) {
		file << t.getId() << "|" << t.getLevel() << "|" << t.getDesc() << "|" << t.getTime() << std::endl;
		items++;
	}
	file.close();
	view.displayMessage("Saved: " + std::to_string(items) + " saved to " + filename);
}

void ThreatController::loadThreatsFromFile(const std::string& filename) {
	int items = 0;
	std::ifstream file(filename);
	if (!file) {
		view.displayMessage("No file found to load threats.");
		return;
	}
	threats.clear();


	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string id, level, description, timestamp;

		if (std::getline(iss, id, '|') &&
			std::getline(iss, level, '|') &&
			std::getline(iss, description, '|') &&
			std::getline(iss, timestamp)) {
			threats.push_back(Threat(id, level, description, timestamp));
			items++;
		}

	}
	file.close();
	view.displayMessage(std::to_string(items) + " have been loaded successfully.");
}

void ThreatController::runProgram() {
	char choice;
	do {
		std::string userInput;
		view.displayMenu();
		view.promptForInput("Enter Choice>> ", userInput);

		choice = userInput[0];

		switch (choice) {
		case '1': {
			std::string id, level, desc, time;
			view.promptForInput("Enter new ID: ", id);
			view.promptForInput("Enter Threat Level [Low|Medium|High|Critical]: ", level);
			view.promptForInput("Enter Description of threat:", desc);
			view.promptForInput("Enter Date of incident [dd-mm-yyyy]", time);
			addThreat(id, level, desc, time);
			break;
		}
		case '2': {
			std::string id, newlevel, newdesc;
			view.promptForInput("Enter id to update: ", id);
			view.promptForInput("Enter new level: ", newlevel);
			view.promptForInput("Enter new description: ", newdesc);
			updateThreat(id, newlevel, newdesc);
			break;
		}
		case '3':
			listThreats();
			break;
		case '4': {
			std::string level;
			view.promptForInput("Enter level [Low|Medium|High|Critical] ", level);
			listThreatsByLevel(level);
			break;
		}
		case '5': {
			std::string id;
			view.promptForInput("Enter name of user to remove: ", id);
			removeThreat(id);
			break;
		}
		case '6': {
			std::string filename;
			view.promptForInput("Enter Filename: ", filename);
			loadThreatsFromFile(filename);
			break;
		}
		case '7': {
			std::string filename;
			view.promptForInput("Enter Filename: ", filename);
			saveThreatsToFile(filename);
			break;
		}
		default:
			view.displayMessage("Invalid choice. Please try again.");
		}
	} while (choice != '0');
}