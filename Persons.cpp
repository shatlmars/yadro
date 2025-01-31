#include "Persons.h"

void Persons::set_in_club(bool state)
{
	in_club = state;
}

void Persons::set_start_gaming(int time)
{
	this->start_gaming = time;
}

void Persons::set_name(std::string name)
{
	this->name = name;
}

int Persons::get_allTime()
{
	int result = (time_end - this->start_gaming);
	return result;
}

bool Persons::get_status_in_club()
{
	return in_club;
}

void Persons::set_number_table(int number)
{
	this->number_table = number;
}

int Persons::get_number_table()
{
	return number_table;
}

void Persons::set_angry(bool state)
{
	this->angry = state;
}

int Persons::get_start_gaming()
{
	return this->start_gaming;
}

void Persons::set_time_end(int time)
{
	this->time_end = time;
}

void Persons::set_fail(bool state)
{
	this->fail = state;
}

std::string Persons::timeToStr(int time)
{
	std::string hour;
	std::string mins;

	if ((time / 60) < 10)
	{
		hour = "0" + std::to_string(time / 60);
	}
	else
	{
		hour = std::to_string(time / 60);
	}
	if ((time % 60) < 10)
	{
		mins = "0" + std::to_string(time % 60);
	}
	else
	{
		mins = std::to_string(time % 60);
	}


	std::string result = hour + ":" + mins;
	return result;
}

Persons::~Persons()
{
	if(!fail)
	{
		if (this->in_club)
		{
			if (this->angry)
			{
				std::cout << timeToStr(time_end) << " 11 " << name << std::endl;
			}
		}
		else
		{
			std::cout << " 13 ClientUnkown!" << std::endl;
		}
	}
}
