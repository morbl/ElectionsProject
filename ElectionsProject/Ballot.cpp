#include "Ballot.h"

int Ballot::serialGenerator = 0;

int Ballot::getSerialNum() const
{
	return serialNum;
}

const Address& Ballot::getAddress() const
{
	return address;
}


list<Citizen *> Ballot::getVoters() const
{
	return voters;
}

bool Ballot::setVoters(list<Citizen *> voters)
{
	this->voters = voters;
	return true;
}

float Ballot::getVotePrecent() const
{
	return votePrecent;
}

bool Ballot::setVotePrecent(float votePrecent)
{
	if (votePrecent >= 0 && votePrecent <= 100)
	{
		this->votePrecent = votePrecent;
		return true;
	}
	else
	{
		cout << "Illegal percent";
		return false;
	}
}

Array<Result*> Ballot::getResult() const
{
	return result;
}

bool Ballot::setResult(Array<Result*> result)
{
	this->result = result;
	return true;
}

int Ballot::getVotedNum() const
{
	return votedNum;
}

int Ballot::getLogicalVoters() const
{
	return voters.size();
}

bool Ballot::addResult(Party* party, int count)
{

	result += new Result(party, count);
	return true;
}

bool Ballot::addVoter(Citizen* citizen)
{
    voters.push_back(citizen);
	return true;
}

void Ballot::show() const
{
	cout << "Serial number: " << serialNum << endl;
    cout << "Ballot Type: " << typeid(*this).name() << endl;
	cout << "Address: ";
	cout << address;
	cout << endl;
}

void Ballot::showResult() const
{
	for (int i = 0; i < result.getSize()-1; i++)
	{
		result[i]->show();
	}
}

bool Ballot::addVote(int partyNum)
{
	result[partyNum]->increaseVote();
	votedNum++;
	return true;
}

Ballot::Ballot(const Address& address) : address(address)
{
	serialNum = ++serialGenerator;
}

Ballot::~Ballot()
{
	voters.clear();
	for (int i = 0; i < logicalResultSize; i++)
	{
		delete result[i];
	}
}



