#include "Result.h"

Party* Result::getParty() const
{
	return party;
}

bool Result::setParty(Party* party)
{
	this->party = party;
	return true;
}

int Result::getcountVote() const
{
	return countVote;
}

bool Result::setcountVote(int countVote)
{
	this->countVote = countVote;
	return true;
}


void Result::show() const
{
	cout << "Party name: " << party->getName() << " Number of voters: " << countVote << endl;
}

Result::Result(Party* party, int countVote)
{
	setParty(party);
	setcountVote(countVote);
}


