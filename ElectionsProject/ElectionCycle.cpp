#include "ElectionCycle.h"
#include "BallotMilitary.h"
#include "BallotIsolation.h"
#include "BallotMilitaryIsolation.h"

const Date& ElectionCycle::getDateOfElection() const
{
	return dateOfElection;
}

bool ElectionCycle::setDateOfElection(const Date& dateOfElection)
{
	return this->dateOfElection.setYear(dateOfElection.getYear()) && this->dateOfElection.setMonth(dateOfElection.getMonth());
}

void ElectionCycle::showBallots() const
{
	cout << "---------------------------------------------" << endl;
    list<Ballot *>::const_iterator itr = ballots.begin();
    list<Ballot *>::const_iterator itrEnd = ballots.end();

    for (;itr!=itrEnd;++itr)
    {
        (*itr)->show();
    }
}

void ElectionCycle::showParties() const
{
    cout << "---------------------------------------------" << endl;

    list<Party *>::const_iterator itr = parties.begin();
    list<Party *>::const_iterator itrEnd = parties.end();
    for (;itr!=itrEnd;++itr)
    {
        (*itr)->show();
    }
}

void ElectionCycle::showVoters() const
{
    int i = 1;
	cout << "---------------------------------------------" << endl;

    list<Citizen *>::const_iterator itr = premittedVoters.begin();
    list<Citizen *>::const_iterator itrEnd = premittedVoters.end();
    for (;itr!=itrEnd;++itr)
    {
        cout << *(*itr);
        i++;
    }
}

bool  ElectionCycle::addBallot(const Address& address, int ballotType)
{
	switch(ballotType)
    {
        case 0 :
            ballots.push_back(new Ballot(address));
            break;
        case 1:
            ballots.push_back(new BallotMilitary(address));
            break;
        case 2:
            ballots.push_back(new BallotIsolation(address));
            break;
        case 3:
            ballots.push_back(new BallotMilitaryIsolation(address));
            break;
        default:
            cout << "Invalid option"<<endl;
            break;
    }

	return true;
}

Ballot * ElectionCycle::getBallotByIndex(int i) const
{
    list<Ballot *>::const_iterator itr = ballots.begin();
    list<Ballot *>::const_iterator itrEnd = ballots.end();

    for (;itr!=itrEnd;++itr)
    {
        if((*itr)->getSerialNum() == i)
            return (*itr);
    }
}

list<Citizen *>::const_iterator ElectionCycle::getCitizenByID(int i) const
{
    list<Citizen *>::const_iterator itr = premittedVoters.begin();
    list<Citizen *>::const_iterator itrEnd = premittedVoters.end();

    for (;itr!=itrEnd;++itr)
    {
        if((*itr)->getID() == i)
            return itr;
    }
}

Party * ElectionCycle::getPartyByIndex(int i) const
{
    list<Party *>::const_iterator itr = parties.begin();
    list<Party *>::const_iterator itrEnd = parties.end();

    int index =0 ;
    for (;itr!=itrEnd;++itr)
    {
        if(index == i)
            return (*itr);
        index++;
    }
}
bool  ElectionCycle::addVoter(const string& name, int id, int year, int ballotIndex,bool isIsolated)
{
	try
	{
	    Ballot * b = getBallotByIndex(ballotIndex);
	    Citizen * temp = new Citizen(name, id, year, b, isIsolated);
        premittedVoters.push_back(temp);
        b->addVoter(temp);
        return true;
    }
	catch(CitizenException& ex)
    {
	    ex.show();
	    cout << "Cant add user you are back to the main menu" << endl << endl << endl <<endl;
	    return false;
    }
	catch (...)
    {
	    cout << "Unknown issue";
        cout << "Cant add user you are back to the main menu" << endl << endl << endl <<endl;
    }
}

bool ElectionCycle::addParty(const string& name, Date& creation, Party::eFaction faction)
{
	parties.push_back(new Party(name, creation, faction));
	return true;
}

list<Ballot*>& ElectionCycle::getBallotsArray()
{
	return ballots;
}

list<Party*>& ElectionCycle::getPartiesArray()
{
	return parties;
}

list<Citizen*>& ElectionCycle::getCitizenArray()
{
	return premittedVoters;
}

void ElectionCycle::resultPerBallot() const
{
	if (!electionFlag) // add to read me
	{
		cout << "There has been no election no result to show!" << endl;
	}
	else
	{
	    int i =1;
		printLine();
		cout << "Results per ballot" << endl;
        list<Ballot *>::const_iterator itr = ballots.begin();
        list<Ballot *>::const_iterator itrEnd = ballots.end();

        for (;itr!=itrEnd;++itr)
        {
			cout << "Ballot Number " << i  << ":\nPercentage voted: " << (*itr)->getVotePrecent() << "%" << endl;
			cout << " Results:" << endl;
            (*itr)->showResult();
		}
        i++;
		printLine();
	}
}

void ElectionCycle::finalResult() const
{
	if (!electionFlag) // add to read me
	{
		cout << "No results" << endl;
	}
	else
	{
		int* arr = new int[parties.size()];
		for (int i = 0; i < parties.size(); i++)
		{
			arr[i] = 0;
		}


        list<Ballot *>::const_iterator itrB = ballots.begin();
        list<Ballot *>::const_iterator itrEndB = ballots.end();
        for (;itrB!=itrEndB;++itrB)
		{
			for (int j = 0; j < parties.size(); j++)
			{
				arr[j] += (*itrB)->getResult()[j]->getcountVote();
			}
		}

		printLine();
		cout << "Final Results of the election" << endl;

        list<Party *>::const_iterator itr = parties.begin();
        list<Party *>::const_iterator itrEnd = parties.end();
        for (int i=0;itr!=itrEnd;++itr)
        {
            cout << " Party name : "<< (*itr)->getName();
            cout<<". Result: " << arr[i] << endl;
            i++;
        }

		delete[]arr;
	}

}

void ElectionCycle::addVote(Citizen * citizenNum, int partyNum)
{
    citizenNum->getBallot()->addVote(partyNum);
}

void ElectionCycle::updatePrecentage()
{
    list<Ballot *>::const_iterator itr = ballots.begin();
    list<Ballot *>::const_iterator itrEnd = ballots.end();

    for (;itr!=itrEnd;++itr)
    {

	    if((*itr)->getLogicalVoters()!=0)
            (*itr)->setVotePrecent(((float)(*itr)->getVotedNum() / (float)(*itr)->getLogicalVoters()) * 100);
	}
}

bool ElectionCycle::isIdExist(int id) const
{
    list<Citizen *>::const_iterator itr = premittedVoters.begin();
    list<Citizen *>::const_iterator itrEnd = premittedVoters.end();
    for (;itr!=itrEnd;++itr)
    {
        if((*itr)->getID() == id)
        {
            return true;
        }

    }
    return false;
}

bool ElectionCycle::isPartyExist(string name) const
{
    list<Party *>::const_iterator itr = parties.begin();
    list<Party *>::const_iterator itrEnd = parties.end();

    for (;itr!=itrEnd;++itr)
    {
        if(name.compare((*itr)->getName())==0)
        {
            cout << "The party is already exist" << endl;
            return true;
        }
    }
	return false;
}

bool ElectionCycle::isBallotExist(int sn) const {
    list<Ballot *>::const_iterator itr = ballots.begin();
    list<Ballot *>::const_iterator itrEnd = ballots.end();

    for (; itr != itrEnd; ++itr) {
        {
            if ((*itr)->getSerialNum() == sn) {
                cout << "The ballot is already exist" << endl;
                return true;
            }
        }
        return false;
    }
}


bool ElectionCycle::isMemberExist(int id) const
{

    list<Party *>::const_iterator itrP = parties.begin();
    list<Party *>::const_iterator itrEndP = parties.end();

    for (;itrP!=itrEndP;++itrP)
	{
        list<Candidate *>::const_iterator itr = (*itrP)->getMembers().begin();
        list<Candidate *>::const_iterator itrEnd = (*itrP)->getMembers().end();
        for (;itr!=itrEnd;++itr)
        {
			if ((*itr)->getID() == id)
			{
				cout << "The citizen is already a member in a party" << endl;
				return true;
			}
		}
	}
	return false;
}

bool ElectionCycle::addMember(const string& name, int id, int year, int ballotIndex, int partyNum,bool isIsolated)
{
	if (isIdExist(id))
	{
        list<Citizen *>::const_iterator c = getCitizenByID(id);
	    Party * p = getPartyByIndex(partyNum);
	    Candidate * newMember = new Candidate(*(*c),p);
		p->addMember(newMember);
        premittedVoters.push_back(newMember);
        premittedVoters.erase(c);

		return true;
	}
	else
	{
		if (addVoter(name, id, year, ballotIndex,isIsolated))
		{
            list<Citizen *>::const_iterator c = getCitizenByID(id);
            Party * p = getPartyByIndex(partyNum);
            Candidate * newMember = new Candidate(*(*c),p);
            p->addMember(newMember);
            premittedVoters.pop_back();
            premittedVoters.push_back(newMember);
			return true;
		}
		else
		{
			false;
		}
	}
}

void ElectionCycle::printLine() const
{
	cout << "---------------------------------------------" << endl;
}

bool ElectionCycle::getElectionFlag() const
{
	return electionFlag;
}

bool ElectionCycle::setElectionFlag(bool flag)
{
	electionFlag = flag;
	return true;
}

ElectionCycle::ElectionCycle(const Date& dateOfElection) : dateOfElection(dateOfElection)
{
}

ElectionCycle::~ElectionCycle()
{

    list<Citizen*>::iterator itrBeginCitizen = premittedVoters.begin();
    list<Citizen*>::iterator itrEndCitizen = premittedVoters.end();

    for (; itrBeginCitizen != itrEndCitizen; ++itrBeginCitizen)
    {
        delete (*itrBeginCitizen);
    }

    list<Party*>::iterator itrBeginParty = parties.begin();
    list<Party*>::iterator itrEndParty = parties.end();

    for (; itrBeginParty != itrEndParty; ++itrBeginParty)
    {
        delete (*itrBeginParty);
    }

    list<Ballot*>::iterator itrBeginBallot = ballots.begin();
    list<Ballot*>::iterator itrEndBallot = ballots.end();

    for (; itrBeginBallot != itrEndBallot; ++itrBeginBallot)
    {
        delete (*itrBeginBallot);
    }
}

void ElectionCycle::operator+= (Citizen& citizen)
{
    addVoter(citizen.getName(),citizen.getID(),citizen.getYear(),getBallotIndex(citizen.getBallot()),citizen.getIsIsolated());
}

int ElectionCycle::getBallotIndex(Ballot * b) const
{
    list<Ballot *>::const_iterator itr = ballots.begin();
    list<Ballot *>::const_iterator itrEnd = ballots.end();
    int i = 0;
    for (;itr!=itrEnd;++itr)
    {
        if(b->getSerialNum()==(*itr)->getSerialNum())
        {
            return i;
        }
        i++;
    }
}


int ElectionCycle::printBallotPerUser(int age, bool isolation) const
{
    list<Ballot *>::const_iterator itr = ballots.begin();
    list<Ballot *>::const_iterator itrEnd = ballots.end();

    int count =0;
    if((18<=age)&&(age<=21)&&(isolation))
    {
        for (;itr!=itrEnd;++itr)
        {
            if(strcmp(typeid(*(*itr)).name(),typeid(BallotMilitaryIsolation).name())==0)
            {
                count++;
                (*itr)->show();
            }
        }
    }

    else if((18<=age)&&(age<=21)&&(!isolation))
    {
        for (;itr!=itrEnd;++itr)
        {
            if(strcmp(typeid(*(*itr)).name(),typeid(BallotMilitary).name())==0)
            {
                count++;
                (*itr)->show();
            }
        }
    }

    else if(isolation)
    {
        for (;itr!=itrEnd;++itr)
        {
            if(strcmp(typeid(*(*itr)).name(),typeid(BallotIsolation).name())==0)
            {
                count++;
                (*itr)->show();
            }
        }
    }
    else
        {
            for (;itr!=itrEnd;++itr)
        {
            if(strcmp(typeid(*(*itr)).name(),typeid(Ballot).name())==0)
            {
                count++;
                (*itr)->show();
            }
        }
    }

    if(count==0)
    {
        cout << "You cant create this user because there is no available ballot for." << endl;
    }
    return count;

}

bool ElectionCycle::checkBallot(int ballotNum,bool isolation,int age) const
{

    Ballot * b = getBallotByIndex(ballotNum);
    if((age<=20 && age>=18) && (isolation))
    {
        if( strcmp(typeid(*b).name(), typeid(BallotMilitaryIsolation).name())==0)
            return true;
    }

    else if((age<=20 && age>=18) && (!isolation))
    {
        if( strcmp(typeid(*b).name(), typeid(BallotMilitary).name())==0)
            return true;
    }

    else if(isolation)
    {
        if( strcmp(typeid(*b).name(), typeid(BallotIsolation).name())==0)
            return true;
    }

    else if(!isolation)
    {
        if( strcmp(typeid(*b).name(), typeid(Ballot).name())==0)
            return true;
    }

    cout << "You chose a ballot the user cannot vote in" <<endl;
    return false;

}

// Saves the election information into a file
void ElectionCycle::saveElectionToFile()
{
    ofstream outFile("electionCycle.txt", ios::out);

    //First we insert the ballots

    //Ballots size
    outFile << ballots.size()<< endl;

    //Now their information
    list<Ballot*>::iterator itrBeginBallot = ballots.begin();
    list<Ballot*>::iterator itrEndBallot = ballots.end();

    for (; itrBeginBallot != itrEndBallot; ++itrBeginBallot)
    {
        outFile << (*itrBeginBallot)->getAddress().getStreet() << endl;
        outFile << (*itrBeginBallot)->getAddress().getNumber() << endl;
        outFile << (*itrBeginBallot)->getAddress().getCity() << endl;
        outFile << getBallotType((*itrBeginBallot))<<endl; // finds the type of ballot our function support adding a ballot by num type
    }

    // Now we insert the parties

    //Parties size
    outFile << parties.size() << endl;


    //Now their information
    list<Party*>::iterator itrBeginParty = parties.begin();
    list<Party*>::iterator itrEndParty = parties.end();

    for (; itrBeginParty != itrEndParty; ++itrBeginParty)
    {
        outFile << (*itrBeginParty)->getName() << endl;
        outFile << (*itrBeginParty)->getCreation().getMonth() << endl;
        outFile << (*itrBeginParty)->getCreation().getYear() << endl;
        outFile << (*itrBeginParty)->getFaction() << endl;
    }

    //Finally we insert the Citizens( - also the candidates)

    // Citizens size
    outFile << premittedVoters.size() << endl;

    //Now their information
    list<Citizen*>::iterator itrBeginCitizen = premittedVoters.begin();
    list<Citizen*>::iterator itrEndCitizen = premittedVoters.end();
    for (; itrBeginCitizen != itrEndCitizen; ++itrBeginCitizen)
    {
        outFile << getCitizenType((*itrBeginCitizen)) << endl; // first I save the type of the user candidate or citizen
        outFile << (*itrBeginCitizen)->getName() << endl;
        outFile << (*itrBeginCitizen)->getID() << endl;
        outFile << (*itrBeginCitizen)->getYear() << endl;
        outFile << (*itrBeginCitizen)->getBallot()->getSerialNum() << endl;
        outFile << (*itrBeginCitizen)->getIsIsolated() << endl;

        Candidate * temp = dynamic_cast<Candidate*>((*itrBeginCitizen));
        if(temp)
        {
            outFile << temp->getParty()->getSerialNumber() <<endl;
        }

    }

    outFile.close();

}

bool  ElectionCycle::loadElectionFromFile()
{
    int citizenSize, ballotSize, partySize;
    bool res = true;

    //Open the file
    ifstream inFile("electionCycle.txt", ios::in);
    if (inFile.peek() == ifstream::traits_type::eof())
    {
        inFile.close();
        res = false;
    }
    else
    {
        // First load the ballots
        inFile >> ballotSize;
        for (int i = 0; i < ballotSize; i++)
        {

            string street;
            int num;
            string city;
            int type;
            char c;

            getline(inFile, street);
            inFile>>num;

            getline(inFile, city);
            inFile>>type;


            Address temp(street,num,city);
            addBallot(temp,type);
        }

        // Now we load the parties

        char c;
        inFile.get(c);
        inFile >> partySize;
        for (int i = 0; i < partySize; i++)
        {
            string name;
            int month;
            int year;
            int faction;


            char c;
            inFile.get(c);
            getline(inFile, name);
            inFile>>month;
            inFile.get(c);
            inFile>>year;
            inFile.get(c);
            inFile>>faction;


            Date temp(month,year);
            addParty(name,temp,Party::eFaction(faction));
        }

        inFile.get(c);
        //Finally the citizens
        inFile >> citizenSize;
        for (int i = 0; i < citizenSize; i++)
        {
            int type;
            string name;
            int id;
            int year;
            int ballotIndex;
            int isolation;
            int partyIndex;


            char c;
            inFile.get(c);
            inFile>>type;
            inFile.get(c);
            getline(inFile, name);
            inFile>>id;
            inFile.get(c);
            inFile>>year;
            inFile.get(c);
            inFile>>ballotIndex;
            inFile.get(c);
            inFile>>isolation;


            if(type==1)
            {
                inFile.get(c);
                inFile>>partyIndex;
                addMember(name,id,year,ballotIndex,partyIndex-1,isolation);
            }
            else
            {
                addVoter(name,id,year,ballotIndex,isolation);
            }
           // inFile.get(c);

        }


    }

    inFile.close();
    return res;

}


// Finds the type of ballot by pointer to the ballot
int ElectionCycle::getBallotType(Ballot* b)
{
    if(dynamic_cast<BallotMilitaryIsolation*>(b))
    {
        return 3;
    }
    else if(dynamic_cast<BallotIsolation*>(b))
    {
        return 2;
    }
    else if(dynamic_cast<BallotMilitary*>(b))
    {
        return 1;
    }
    else
    {
       return 0;
    }
}

int ElectionCycle::getCitizenType(Citizen* c)
{
    if(dynamic_cast<Candidate*>(c))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}