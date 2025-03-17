#include "HashTable.h"
#include <iostream>

void showMenu() {
	std::cout << "\nMenu:\n" << "1. ADD\n" << "2. DEL\n" << "3. IMPORT\n" << "4. SEARCH\n" << "5. PLOT\n" << "6. SAVE <filename>\n" << "7. LOAD <filename>\n" << "8. QUIT\n";
	std::cout << "Your choice: ";
}

int main() {
	HashTable hashtable(2003); //2003 is a prime number
	string input;
	while (true) {
		showMenu();
		std::getline(cin, input);
		if (input == "1" || input == "ADD") {

		}
		else if (input == "2" || input == "DEL") {

		}
		else if (input == "3" || input == "IMPORT") {

		}
		else if (input == "4" || input == "SEARCH") {

		}
	}
}