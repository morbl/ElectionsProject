
#ifndef PLEASEFINAL_BALLOTMILITARY_H
#define PLEASEFINAL_BALLOTMILITARY_H


#include "Ballot.h"

class BallotMilitary : virtual public Ballot{
public:
    //c'tor
BallotMilitary(const Address & ad): Ballot(ad){};


};


#endif //PLEASEFINAL_BALLOTMILITARY_H
