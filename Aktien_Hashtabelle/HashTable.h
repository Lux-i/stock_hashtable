#include "Stock.h"

enum EntryType { EMPTY, OCCUPIED, DELETED };

struct Entry {
	Entry() : type(EMPTY) {};
	Stock stock;
	EntryType type;
};

class HashTable
{
public:
	HashTable(int size) : tableSize(size), count(0) {
		table.resize(tableSize);
	}
	bool add(const string&);
	bool remove(const string&);
	bool import(const string&);
	int search(const string&);
	bool display(unsigned int position);
	bool plot(const string&) {};
	bool save(const string&) {};
	bool load(const string&) {};
private:
	int tableSize;
	int count;
	vector<Entry> table;
	unsigned int hashString(const string&);
	bool insert();
};

