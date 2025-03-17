#include <string>
#include <vector>
using namespace std;

struct StockData {
	string date;
	string open;
	string close;
	string low;
	string high;
	string volume;
};

class Stock
{
public:
	Stock() = default;
	Stock(string& n, string& w, string& t) : name(n), wkn(w), ticker(t) {};
	string name;
	string wkn;
	string ticker;
	StockData stockdata[30];
};

