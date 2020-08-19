#include "Date.h"

bool Date::setYear(int year)
{
	this->year = year;
	return true;
}


bool Date::setMonth(int month)
{
	if (month < 1 || month >= 13)  //There are only 12 months
	{
		return false;
	}

	else
	{
		this->month = month;
		return true;
	}
}

int Date::getYear() const
{
	return year;
}
int Date::getMonth() const
{
	return month;
}

Date::Date(int year, int month)
{
	setYear(year);
	setMonth(month);
}

ostream& operator <<(ostream& os, const Date& date)
{
    os << "The Year: " << date.getYear() <<" The month: " << date.getMonth()<< endl;
    return os;
}
