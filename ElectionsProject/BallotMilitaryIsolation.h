
#ifndef PLEASEFINAL_BALLOTMILITARYISOLATION_H
#define PLEASEFINAL_BALLOTMILITARYISOLATION_H


#include "BallotMilitary.h"
#include "BallotIsolation.h"

class BallotMilitaryIsolation :  public BallotMilitary, public BallotIsolation{
public:
    //c'tor
    BallotMilitaryIsolation(const Address & ad) : Ballot(ad),BallotMilitary(ad),BallotIsolation(ad){};


};


#endif //PLEASEFINAL_BALLOTMILITARYISOLATION_H
