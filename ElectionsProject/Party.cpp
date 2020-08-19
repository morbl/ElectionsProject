#include "Party.h"

int Party::serialGenerator = 0;

string Party::getName()	const
{
	return name;
}

bool Party::setName(const string& name)
{
	this->name=name;
	return true;
}

Party::eFaction Party::getFaction()		const
{
	return (Party::eFaction) faction;
}

bool Party::setFaction(eFaction faction)
{
	if (!(faction == eFaction::LEFT || faction == eFaction::RIGHT || faction == eFaction::CENTER))
		return false;
	else
	{
		this->faction = faction;
		return true;
	}
}

const Date& Party::getCreation() const
{
	return creation;
}

bool Party::setCreation(const Date& creation)
{
	this->creation = creation;
	return true;
}

list<Candidate*> Party::getMembers() const
{
	return members;
}

bool Party::setMembers(list<Candidate*> members)
{
	this->members = members;
	return true;
}

bool  Party::addMember(Candidate* citizen)
{
	if (citizen != nullptr)
	{
		members.push_back(citizen);
		return true;
	}
	else
	{
		return false;
	}
}


void Party::show() const
{
    int i = 1;
	cout << "Name: " << name << "\nSerial number: " << serialNumber << "\nCreation date: " << creation.getYear() << "\nMonth: " << creation.getMonth() << "\nFaction: " << factionName[faction - 1] << endl
		<< "The Members: \n" << endl;

	list<Candidate *>::const_iterator itr = members.begin();
    list<Candidate *>::const_iterator itrEnd = members.end();
	for (;itr!=itrEnd;++itr)
	{
		cout << "Member number" << i << endl;
		(*itr)->show();
		i++;
	}
}


Party::Party(const string& name, Date& creation, eFaction faction) : creation(creation)
{
	serialNumber = ++serialGenerator;
	setName(name);
	setFaction(faction);
}


bool Party::operator> (const Party& other) const
{
    return (members.size() > other.members.size());
}