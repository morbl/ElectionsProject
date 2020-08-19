
#ifndef PLEASEFINAL_CANDIDATE_H
#define PLEASEFINAL_CANDIDATE_H

#include "Citizen.h"
class Party;
class Candidate : public Citizen
{
private:
    Party* party;

public:
    // c'tors
    Candidate(const char* name, int id, int year, Ballot* ballot,bool isIsolated, Party* party);
    Candidate(Citizen& citizen, Party* party);

    // virtual print
    virtual void toOs(ostream& os)  const override;

    // Getters
    bool setParty(Party* party);

    // Setters
    Party* getParty() const;

};


#endif //PLEASEFINAL_CANDIDATE_H
