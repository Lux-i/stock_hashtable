#include "HashTable.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

//polynomial rolling hash based function
unsigned int HashTable::hashString(const string& inputString) {
	unsigned int hash = 0;
	unsigned int iteration = 1; //starting iteration at 1 so one-char characters are not distributed side-by-side
	unsigned int base = 67; //prime as a base
	unsigned int overflow_mod = 2147483647; //huge prime to prevent overflow for multiplier
	for (char c : inputString) {
		//cast char c to u_int so it can be added
		unsigned int uint_c = (unsigned int)c;
		//adding the next character
		//multiplied by a prime to the power of iteration
		unsigned int multiplier = (unsigned int)pow(base, iteration) % overflow_mod;
		hash += uint_c * multiplier;
		iteration++;
	}
	//modulo the result by tableSize so we do not get an overflowing value
	return hash % tableSize;
}

bool HashTable::add() {
	std::string name;
	std::string wkn;
	std::string ticker;
	unsigned int hash;

	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "WKN: ";
	std::cin >> wkn;
	std::cout << "Kürzel: ";
	std::cin >> ticker;
	if (hash = hashString(ticker)){
		if (table[hash].type != EntryType::OCCUPIED) {
			table[hash].stock.name = name;
			table[hash].stock.wkn = wkn;
			table[hash].stock.ticker = ticker;
			table[hash].type = EntryType::OCCUPIED;
			return true;
		}
		else {
			
			return false;
		}
}
}

bool HashTable::remove() {
	std::string ticker;
	unsigned int hash;
	std::cout << "Kuerzel: ";
	std::cin >> ticker;

	if (hash = hashString(ticker)) {
		table[hash].stock.name = "";
		table[hash].stock.wkn = "";
		table[hash].stock.ticker = "";
		table[hash].type = EntryType::DELETED;
		return true;
	}
}

bool HashTable::import() {
	std::string ticker;
	unsigned int hash;
	std::cout << "Kuerzel: ";
	std::cin >> ticker;
	hash = hashString(ticker);
	ticker = ticker + ".csv";


		ifstream fin;
		string line = "", date = "", close = "", volume = "", open = "", high = "", low = "";
		int location = 0;
		int i = 0;

		fin.open(ticker);
		std::getline(fin, line);

		while (getline(fin, line)) {
			stringstream ss(line);
			string token;
			int column = 0;

			while (getline(ss, token, ',')) {
				switch (column) {
				case 0: table[hash].stock.stockdata[i].date = token; break;
				case 1: table[hash].stock.stockdata[i].close = token; break;
				case 2: table[hash].stock.stockdata[i].volume = token; break;
				case 3: table[hash].stock.stockdata[i].open = token; break;
				case 4: table[hash].stock.stockdata[i].high = token; break;
				case 5: table[hash].stock.stockdata[i].low = token; break;
				}
				column++;

			}
			i++;
		}
			return true;
}

int HashTable::search() {
	std::string ticker;
	unsigned int hash;

	std::cout << "Kürzel: ";
	std::cin >> ticker;

	hash = hashString(ticker);
	if (table[hash].stock.ticker == ticker && table[hash].type == EntryType::OCCUPIED) {
		std::cout << "FOUND " << table[hash].stock.ticker << std::endl;

		return 1;
	}
	else {
		std::cout << "NOT FOUND";
		return 0;
	}
}