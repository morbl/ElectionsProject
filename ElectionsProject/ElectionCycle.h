#ifndef CPP_ELECTIONCYCLE_H
#define CPP_ELECTIONCYCLE_H

#include "Date.h"
#include "Party.h"
#include "Ballot.h"
#include <fstream>
#include <string>
#include <list>
class ElectionCycle
{
public:

    // Getters
	list<Ballot*>& getBallotsArray();
	list<Party*>& getPartiesArray();
    list<Citizen*>& getCitizenArray();
	const Date& getDateOfElection()	            const;
	bool getElectionFlag()                      const;
	bool setElectionFlag(bool flag);
	bool setDateOfElection(const Date& dateOfElection);

	// c'tor
	ElectionCycle(const Date& dateOfElection);

	// d'tor
	~ElectionCycle();

	// Add new ballot to the list
	bool addBallot(const Address& address, int ballotType);
	// Add new voter to the list
	bool addVoter(const string& name, int id, int year, int ballotIndex,bool isIsolated);
	// Add new party to the list
	bool addParty(const string& name, Date& creation, Party::eFaction faction);
	// Add new candidate to the list
	bool addMember(const string& name, int id, int year, int ballotIndex, int partyNum,bool isIsolated);

	// Operator to add a citizen
    void operator+= (Citizen& citizen);

    // Get ballot index in list
    int getBallotIndex(Ballot * b)               const;

    //Get the balot by its index
    Ballot * getBallotByIndex(int i) const;

    // Get the iterator of a citizen by id
    list<Citizen *>::const_iterator getCitizenByID(int i) const;

    //Get the party by index
    Party * getPartyByIndex(int i) const;

    // Get the sizes of the lists
	int getLogicalVoters()                       const
	{
		return premittedVoters.size();
	}
    int getLogicalBallots() const
    {
        return ballots.size();
    }
    int getLogicalParties() const
    {
        return parties.size();
    }

    // Save the elections information to a file
    void saveElectionToFile();
	// Load elections information from a file
	bool loadElectionFromFile();

	// Find ballot type
    int getBallotType(Ballot* b);

    //Find if its a regular citizen or a candidate
    int getCitizenType(Citizen* c);

    // Add vote by the party num
    void addVote(Citizen * citizenNum, int partyNum);
    //Update the Precentage of voters oer ballot
    void updatePrecentage();



	// Prints

	// Prints the all result per ballot
    void resultPerBallot()						const;
    // Print the final result of the all election
    void finalResult()							const;


	// Print ballots
	void showBallots()							const;
	// Print voters
	void showVoters()							const;
	// Print parties
	void showParties()							const;
	// Print ballots oer user - so the user knows what ballot to choose from
    int printBallotPerUser(int age, bool isolation) const;
    // Print line to look pretty
    void printLine() const;


	// Validators
	bool isIdExist(int id)                      const;
    bool checkBallot(int ballotNum,bool isolation,int age)        const;
	bool isPartyExist(string name)				const;
	bool isBallotExist(int sn)					const;
	bool isMemberExist(int id)                  const;




private:
	Date dateOfElection;
	list<Citizen*> premittedVoters;
	list<Party*> parties;
	list<Ballot*> ballots;
	bool electionFlag = false;
	ElectionCycle(const ElectionCycle&);

};


#endif //CPP_ELECTIONCYCLE_H