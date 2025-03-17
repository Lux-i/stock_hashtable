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
	bool add();
	bool remove();
	bool import();
	int search();
	bool display();
	bool plot();
	bool save();
	bool load();
private:
	int tableSize;
	int count;
	vector<Entry> table;
	unsigned int hashString();
};

