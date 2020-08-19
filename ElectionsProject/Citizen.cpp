#include "Citizen.h"
#include "Ballot.h"


bool Citizen::setYear(int year)
{
	if (year < 1900 || year >= 2002)  //assuming the oldest is 120
	{
		return false;
	}
	else
	{
		this->year = year;
		return true;
	}
}

int Citizen::getYear() const
{
	return year;
}


Ballot* Citizen::getBallot() const
{
	return ballot;
}

bool Citizen::setBallot(Ballot* ballot)
{
	this->ballot = ballot;
	return true;
}


int Citizen::getID() const
{
	return id;
}

bool Citizen::setID(int id)
{
	if (id < 99999999 || id >= 1000000000)
	{
		return false;
	}

	else
	{
		this->id = id;
		return true;
	}
}

string Citizen::getName() const
{
	return name;
}

bool Citizen::setName(const string& name)
{
	this->name=name;
	return true;
}

void Citizen::show() const
{
	cout << "Name: " << name << " ID: " << id << " Year: " << year << "\n Ballot: \n";
	ballot->show();
	cout << endl;
	cout << "---------------------------------------------" << endl;
}

Citizen::Citizen(const string& name, int id, int year, Ballot* ballot,bool isIsolated) throw(CitizenException)
{

	if(!setYear(year))
    {
	    throw ageException(year);
    }
	if(!setID(id))
    {
        throw IdException(id);
    }
	setBallot(ballot);
	setName(name);
	setIsIsolated(isIsolated);
}


bool Citizen::getIsIsolated() const {
    return isIsolated;
}

void Citizen::setIsIsolated(bool isIsolated) {
    this->isIsolated = isIsolated;
}

ostream& operator<<(ostream& os, const Citizen& citizen)
{
    os << "Name: " << citizen.getName() << " ID: " << citizen.getID() << " Year: " << citizen.getYear() << "\n Ballot: \n";
    citizen.getBallot()->show();
    citizen.toOs(os);
    os << endl;
    os << "---------------------------------------------" << endl;
    return os;
}

