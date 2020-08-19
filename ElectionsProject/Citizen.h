#ifndef __CITIZEN_H
#define __CITIZEN_H
#pragma warning (disable: 4996)
#include <iostream>
#include "CitizenException.h"

class Ballot;

using namespace std;

class Citizen
{
private:
	string name;
	int id;
	int year;
	Ballot* ballot;
	bool isIsolated;
public:

    // Getters
    bool getIsIsolated()                const;
    void setIsIsolated(bool isIsolated);
	int getYear()						const;
	Ballot* getBallot()					const;
	int getID()							const;
	string getName()				    const;

	//Setters
	bool setYear(int year);
	bool setBallot(Ballot* ballot);
	bool setID(int id);
	bool setName(const string& name);

	//c'tor
    Citizen(const string& name, int id, int year, Ballot* ballot,bool isIsolated) throw(CitizenException);

    //d'tor
    virtual ~Citizen()= default;

    // print operator
    friend ostream& operator<<(ostream& os, const Citizen& citizen);

    // virtual os
    virtual void toOs(ostream& os) const {};

    // Show function
    void show()                         const;
};

#endif // __CITIZEN_H