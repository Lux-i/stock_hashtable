#include <string>
#include <vector>
using namespace std;

struct StockData {
	string date;
	double open;
	double close;
	double low;
	double high;
	long volume;
};

class Stock
{
public:
	Stock() = default;
	Stock(string& n, string& w, string& t) : name(n), wkn(w), ticker(t) {};
	string name;
	string wkn;
	string ticker;
	vector<StockData> stockdata;
};

