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

bool HashTable::add(const string& name) {
	string wkn;
	string ticker;

	std::cout << "WKN: ";
	std::getline(cin, wkn);
	std::cout << "Kuerzel: ";
	std::getline(cin, ticker);

	unsigned int hash = hashString(ticker);

	if (table[hash].type != EntryType::OCCUPIED) {
		table[hash].stock.name = name;
		table[hash].stock.wkn = wkn;
		table[hash].stock.ticker = ticker;
		table[hash].type = EntryType::OCCUPIED;
		return true;
	}
	else {
		//quadratic probing loop
		for (int i = 1; i <= tableSize; i++) {
			unsigned int quadratic = (hash + i * i) % tableSize;
			if (table[quadratic].type != EntryType::OCCUPIED) {
				table[quadratic].stock.name = name;
				table[quadratic].stock.wkn = wkn;
				table[quadratic].stock.ticker = ticker;
				table[quadratic].type = EntryType::OCCUPIED;
				return true;
			}
		}
	}
	return false;
}

bool HashTable::remove(const string& ticker) {
	unsigned int hash = hashString(ticker);

	table[hash].stock.name = "";
	table[hash].stock.wkn = "";
	table[hash].stock.ticker = "";
	table[hash].type = EntryType::DELETED;
	return true;
	return false;
}

bool HashTable::import(const string & ticker) {
	unsigned int hash = hashString(ticker);
	string filename = ticker + ".csv";

	ifstream fin;
	string line;
	int location = 0;
	int i = 0;

	fin.open(filename, ios::in);
	getline(fin, line);

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

int HashTable::search(const string& ticker) {
	unsigned int hash = hashString(ticker);

	if (table[hash].type == EntryType::OCCUPIED) {
		if (table[hash].stock.ticker == ticker) {
			std::cout << "FOUND " << table[hash].stock.ticker << std::endl;
			return hash;
		}
		else {
			//quadratic probing loop
			for (int i = 1; i <= tableSize; i++) {
				int quadratic = (hash + i * i) % tableSize;
				if (table[quadratic].type == EntryType::EMPTY) break;
				if (table[quadratic].stock.ticker == ticker) {
					std::cout << "FOUND " << table[hash].stock.name << std::endl;
					return quadratic;
				}
			}
		}

	}
	std::cout << "NOT FOUND";
	return -1;
}

bool HashTable::display(unsigned int position) {
	std::cout << "Name: " << table[position].stock.name << std::endl;
	std::cout << "Date: " << table[position].stock.stockdata[0].date << std::endl;
	std::cout << "Close: " << table[position].stock.stockdata[0].close << std::endl;
	std::cout << "Volume: " << table[position].stock.stockdata[0].volume << std::endl;
	std::cout << "Open: " << table[position].stock.stockdata[0].open << std::endl;
	std::cout << "High: " << table[position].stock.stockdata[0].high << std::endl;
	std::cout << "Low: " << table[position].stock.stockdata[0].low << std::endl;
	return 1;
}