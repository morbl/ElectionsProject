#ifndef __PARTY_H
#define __PARTY_H
#include <iostream>
using namespace std;
#include "Date.h"
#include "Candidate.h"
#include "list"
#pragma warning (disable: 4996)


class Party
{
public:

    // enum
	enum eFaction { LEFT = 1, RIGHT, CENTER };
	const string factionName[3] = { "Left", "Right", "Center" };

	// Getters
	string getName()				    const;
	eFaction getFaction()		        const;
	const Date& getCreation()           const;
    list<Candidate*> getMembers()		const;
    bool operator>(const Party& other)  const;
    int getSerialNumber() const {return serialNumber;};

    // Setters
	bool setName(const string& name);
	bool setFaction(eFaction faction);
	bool setCreation(const Date& creation);
	bool setMembers(list<Candidate*> members);

	// Add memeber to the party
	bool addMember(Candidate* citizen);

	// Print party
	void show()					        const;

	// c'tor
	Party(const string& name, Date& creation, eFaction faction);

	//d'tor
	~Party()= default;


private:
	string name;
	eFaction faction;
	Date creation;
    list<Candidate*> members;
	int serialNumber;
	static int serialGenerator;
	Party(const Party&);
};

#endif // __PARTY_H