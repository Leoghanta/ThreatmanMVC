#include "ThreatView.h"

void ThreatView::displayThreat(const Threat& t) {
    std::cout << "Threat ID: " << t.getId() << "\t\tLevel: " << t.getLevel() << "\t\tRecorded on: " << t.getTime() << std::endl;
    std::cout << t.getDesc() << std::endl;
    for (int i = 0; i < 80; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
}


void ThreatView::displayMessage(const std::string& message) {
	std::cout << message << std::endl;
}

void ThreatView::displayMenu() {
    std::cout << "\n--- Threat Management System ---\n";
    std::cout << "1. Add Threat\n";
    std::cout << "2. Update Threat\n";
    std::cout << "3. Display All Threats\n";
    std::cout << "4. Display Threats by Threat Level\n";
    std::cout << "5. Remove Threat\n";
    std::cout << "6. Load Threats\n";
    std::cout << "7. Save Threats\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

void ThreatView::promptForInput(const std::string& prompt, std::string& input) {
    std::cout << prompt;
    std::getline(std::cin, input);
}