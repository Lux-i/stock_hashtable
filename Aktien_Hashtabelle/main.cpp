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

		//command and arg parser
		std::getline(cin, input);
		string command;
		string arg;
		int pos = input.find(' ');
		command = input.substr(0, pos);
		arg = input.substr(pos + 1);

		if (command == "8" || command == "QUIT") {
			break;
		}
		//only check if argument is empty if command is not exit
		if (pos == -1 || arg == (string)"") {
			std::cout << "Missing argument!\n";
		}
		else if (command == "1" || command == "ADD") {
			if (hashtable.add(arg)) {
				std::cout << "Successfully added\n";
			}
			else {
				std::cout << "Error\n";
			}
		}
		else if (command == "2" || command == "DEL") {
			hashtable.remove(arg);
		}
		else if (command == "3" || command == "IMPORT") {
			int position = hashtable.search(arg);
			if (position != -1) {
				hashtable.import(arg, position);
			}
			else {
				std::cout << "\nThis ticker has not been added yet!\n";
				std::cout << "Name: ";
				string name;
				std::getline(cin, name);
				if (hashtable.add(name)) {
					int position = hashtable.search(arg);
					if (position != -1) {
						hashtable.import(arg, position);
					}
				}
				else {
					std::cout << "Error\n";
				}
			}

		}
		else if (command == "4" || command == "SEARCH") {
			int position = hashtable.search(arg);
			if (position != -1) {
				hashtable.display(position);
			}
			else {
				std::cout << "Ticker not found\n";
			}
		}
		else if (command == "5" || command == "PLOT") {
			int position = hashtable.search(arg);
			if (position != -1) {
				hashtable.plot(position);
			}
			else {
				std::cout << "Ticker not found\n";
			}
		}
		else if (command == "6" || command == "SAVE") {
			hashtable.save(arg);
		}
	}
}