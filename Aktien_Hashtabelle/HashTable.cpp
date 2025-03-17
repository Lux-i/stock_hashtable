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

bool HashTable::import(const string & ticker, unsigned int position) {
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
			case 0: table[position].stock.stockdata[i].date = token; break;
			case 1: table[position].stock.stockdata[i].close = stod(token.substr(1)); break;
			case 2: table[position].stock.stockdata[i].volume = stoul(token); break;
			case 3: table[position].stock.stockdata[i].open = stod(token.substr(1)); break;
			case 4: table[position].stock.stockdata[i].high = stod(token.substr(1)); break;
			case 5: table[position].stock.stockdata[i].low = stod(token.substr(1)); break;
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
			return hash;
		}
		else {
			//quadratic probing loop
			for (int i = 1; i <= tableSize; i++) {
				int quadratic = (hash + i * i) % tableSize;
				if (table[quadratic].type == EntryType::EMPTY) break;
				if (table[quadratic].stock.ticker == ticker) {
					return quadratic;
				}
			}
		}

	}
	std::cout << "NOT FOUND";
	return -1;
}

void HashTable::display(unsigned int position) {
	std::cout << "Name: " << table[position].stock.name << std::endl;
	std::cout << "Date: " << table[position].stock.stockdata[0].date << std::endl;
	std::cout << "Open: " << table[position].stock.stockdata[0].open << "$" << std::endl;
	std::cout << "Close: " << table[position].stock.stockdata[0].close << "$" << std::endl;
	std::cout << "Low: " << table[position].stock.stockdata[0].low << "$" << std::endl;
	std::cout << "High: " << table[position].stock.stockdata[0].high << "$" << std::endl;
	std::cout << "Volume: " << table[position].stock.stockdata[0].volume << std::endl;
}

void HashTable::plot(unsigned int position) {
	const auto& data = table[position].stock.stockdata;
	string startDate = data[0].date, endDate;
	int count = 0; //counter for valid entries (if not full array has imported values)
	double minPrice = data[0].close, maxPrice = data[0].close;
	for (const auto& d : data) {
		if (d.date == "NOT INITIALIZED") break;
		minPrice = min(minPrice, d.close);
		maxPrice = max(maxPrice, d.close);
		endDate = d.date;
		count++;
	}

	int plotHeight = 10;
	for (int row = plotHeight; row >= 0; row--) {
		double threshold = minPrice + (maxPrice - minPrice) * row / plotHeight;
		for (size_t i = 0; i <= 4; i++) {
			std::cout << "  ";
		}
		for (size_t i = 0; i < count; i++) {
			std::cout << (data[i].close >= threshold ? "* " : "  ");
		}
		std::cout << "\n";
	}
	std::cout << startDate;
	for (size_t i = 0; i < count; i++) {
		std::cout << "--";
	}
	std::cout << endDate;
	std::cout << "\n";
}