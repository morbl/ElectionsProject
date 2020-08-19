#include "Candidate.h"
#include "Party.h"
Candidate::Candidate(const char* name, int id, int year, Ballot* ballot,bool isIsolated, Party* party):Citizen(name,id,year,ballot,isIsolated)
{
    setParty(party);
}
Candidate::Candidate(Citizen& citizen, Party* party): Citizen(citizen)
{
    setParty(party);
}

bool Candidate::setParty(Party* party)
{
    this->party = party;
    return true;
}

Party* Candidate::getParty() const
{
    return this->party;
}


void Candidate::toOs(ostream& os) const
{
    os << "Party Name: " << party->getName();
}