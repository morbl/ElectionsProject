#ifndef __BALLOT_H
#define __BALLOT_H
#include <iostream>

#include "Citizen.h"
#include "Address.h"
#include "Result.h"
#include "Array.h"
using namespace std;
#include <list>

class Ballot
{
private:


protected:
	static int serialGenerator;
	int serialNum;
	Address address;
	list<Citizen *> voters;
	float votePrecent;
	Array<Result*> result;
	int votedNum = 0;


	int logicalResultSize = 0;
	int physicalResultSize = 1;
    Ballot(const Ballot& other);




public:
    // Getters
	int getSerialNum()						const;
	int getVotedNum()                       const;
	int getLogicalVoters()                  const;
    list<Citizen *> getVoters()					const;
	const Address& getAddress()				const;
	float getVotePrecent()					const;
    Array<Result*> getResult()					const;

    //Setters
	bool setResult(Array<Result*> result);
	bool setVoters(list<Citizen *> voters);
	bool setVotePrecent(float votePrecent);

	//Add result to ballot
	bool addResult(Party* party, int count);
	//Add voter to ballot
	bool addVoter(Citizen* citizen);

	//Add another vote to ballot by party index
	bool addVote(int partyNum);

	// Print the ballot
	void show()								const;

	//Show all the result per ballot
	void showResult()						const;

	//c'tor
	Ballot(const Address& ad);

	//d'tor
	virtual ~Ballot();
};

#endif // __BALLOT_H