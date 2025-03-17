#include "HashTable.h"
#include <cmath>

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