#pragma once
#include <iostream>
#include <string>
class Persons
{
public:
	Persons() : in_club(false), angry(false), debt(0), time(0),time_end(0), start_gaming(0), fail(false) {}
	void set_in_club(bool state);
	void set_start_gaming(int time);
	void set_name(std::string name);
	int get_allTime(); 
	bool get_status_in_club();
	void set_number_table(int number);
	int get_number_table();
	void set_angry(bool state);
	int get_start_gaming();
	void set_time_end(int time);
	void set_fail(bool state);
	std::string timeToStr(int time);
	~Persons();
private:
	std::string name;
	bool in_club;
	int number_table;
	int debt;
	int time;
	int time_end;
	int start_gaming;
	bool angry;
	bool fail;
};

