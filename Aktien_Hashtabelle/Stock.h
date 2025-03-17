#include <string>
#include <vector>
using namespace std;

struct StockData {
	string date = "NOT INITIALIZED";
	double open = 0;
	double close = 0;
	double low = 0;
	double high = 0;
	unsigned int volume = 0;
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

