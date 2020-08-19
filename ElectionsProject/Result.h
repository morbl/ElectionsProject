#ifndef __RESULT_H
#define __RESULT_H
#include <iostream>
#include "Party.h"
using namespace std;


class Result
{
private:
	Party* party;
	int countVote = 0;

public:

    // Getters
	Party* getParty()					const;
	int getcountVote()					const;

	// Setters
	bool setParty(Party* party);
	bool setcountVote(int countVote);

	// Print result
	void show()							const;

	// Increase vote by one
	void increaseVote() { countVote++; }

	// c'tor
	Result(Party* party, int countVote = 0);
};




#endif// __RESULT_H


