#include "Tables.h"

void Tables::addDebt(int d)
{
	debt += d;
}

int Tables::getDebt()
{
	return this->debt;
}

void Tables::addTime(int min)
{
	this->time_in_min += min;
}

int Tables::getTime()
{
	return this->time_in_min;
}

void Tables::set_name(std::string name)
{
	this->name = name;
}

std::string Tables::get_name()
{
	return this->name;
}

bool Tables::getoccupied()
{
	return this->occupied;
}

void Tables::setOccupied(bool state)
{
	this->occupied = state;
}

Tables::~Tables()
{
	
}
