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
		std::cin >> input;
		/*string command;
		string arg;
		std::size_t pos = input.find(' ');
		command = input.substr(0, pos);
		arg = input.substr(pos + 1);
		std::cout << hashtable.hash(input) << "\n";
		if (arg == "") {
			std::cout << "Missing argument!\n";
		}*/
		if (input == "8" || input == "QUIT") {
			break;
		}
		else if (input == "1" || input == "ADD") {
			if (hashtable.add()) {
				std::cout << "Successfully added\n";
			}
			else {
				std::cout << "Error\n";
			}
		}
		else if (input == "2" || input == "DEL") {
			hashtable.remove();
		}
		else if (input == "3" || input == "IMPORT") {

		}
		else if (input == "4" || input == "SEARCH") {
			hashtable.search();
		}
	}
}