#include "Address.h"


string Address::getStreet() const
{
	return street;
}

string Address::getCity() const
{
	return city;
}

int Address::getNumber() const
{
	return number;
}

bool Address::setStreet(const string& street)
{
	this->street=street;
	return true;
}

bool Address::setNumber(int number)
{
	if (number <= 0)
	{
		return false;
	}
	else
	{
		this->number = number;
		return true;
	}
}

bool Address::setCity(const string& city)
{
	this->city=city;
	return true;
}

Address::Address(const string& street, int number, const string& city)
{
	setStreet(street);
	setNumber(number);
	setCity(city);
}
ostream& operator <<(ostream& os, const Address& address)
{
    os << "Street: " << address.street << " " << address.number << " City: " << address.city << endl;
    os << "---------------------------------------------";
    return os;
}

