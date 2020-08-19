
#ifndef PLEASEFINAL_BALLOTISOLATION_H
#define PLEASEFINAL_BALLOTISOLATION_H


#include "Ballot.h"

class BallotIsolation : virtual public Ballot{
public:
    //c'tor
    BallotIsolation(const Address & ad): Ballot(ad){};



};


#endif //PLEASEFINAL_BALLOTISOLATION_H
