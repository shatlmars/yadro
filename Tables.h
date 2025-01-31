#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class Tables
{
public:
	Tables() : occupied(false), debt(0), time_in_min(0) {}
	void addDebt(int d);
	int getDebt();
	void addTime(int min);
	int getTime();
	void set_name(std::string name);
	std::string get_name();
	bool getoccupied();
	void setOccupied(bool state);
	~Tables();
private:
	std::string name;
	bool occupied;
	int debt;
	int time_in_min;
};

