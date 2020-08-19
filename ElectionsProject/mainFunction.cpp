#include "mainFunction.h"
int currBallot = NUM_BALLOT;
int currParties = NUM_PARTIES;
int currCitizen = NUM_CITIZEN;

void cleanBuffer()
{
	int c;
	do
	{
		c = getchar();
	} while (c != EOF && c != '\n');
}

void printMenu()
{
	cout << "Please make a choice: \n1- To add a ballot\n2- To add a citizen\n"
		<< "3- To add a party\n4- To add a citizen as a candidate on behalf of a particular party\n"
		<< "5- To show all the ballots\n6- To show all the citizens\n7- To show all the parties\n"
		<< "8- Start election\n9- To show the result of election\n10-To exit " << endl;
}

void interActiveMenu(ElectionCycle& election)
{
	int choice;
	do
	{
		printMenu();

		cin >> choice;

		if (choice != EXIT)
		{
			doChoice(choice, election);
		}

	} while (choice != EXIT);

	election.saveElectionToFile();

	cout << "GoodBye Thank you for using our system!" << endl;
}


void doChoice(int choice, ElectionCycle& election)
{
	switch (choice)
	{

	case 1:
		addNewBallot(election);
		break;

	case 2:
		addNewCitizen(election);
		break;

	case 3:
		addNewParty(election);
		break;

	case 4:
		addNewMember(election);
		break;

	case 5:
		election.showBallots();
		break;

	case 6:
		election.showVoters();
		break;

	case 7:
		election.showParties();
		break;

	case 8:
		startElection(election);
		break;

	case 9:
		election.resultPerBallot();
		election.finalResult();

		break;

	default:
		cout << "Choice doesnt exist Please Choose again\n";
	}
}

void initializeBallots(list<Ballot *>& ballots, list<Party *>& parties, const ElectionCycle& election)
{
    list<Ballot *>::const_iterator itr = ballots.begin();
    list<Ballot *>::const_iterator itrEnd = ballots.end();

    for (;itr!=itrEnd;++itr)
    {
		for (int j = 0; j < election.getLogicalParties(); j++)
		{
            (*itr)->addResult(election.getPartyByIndex(j), 0);
		}
	}
}

void firstInit(ElectionCycle& election)
{
    if(!election.loadElectionFromFile()) // First tries to load information from a file if fails goes to the hard coded init
    {
        // Create the parties
        Date temp(1973, 9);
        election.addParty("LIKUD", temp, (Party::eFaction) 2);
        Date temp_2(2019, 2);
        election.addParty("BLUEWHITE", temp_2, (Party::eFaction) 3);
        Date temp_3(1968, 1);
        election.addParty("WORD", temp_3, (Party::eFaction) 1);

        // Create the ballots
        Address address("Hashmonaim", 10, "Tel aviv");
        election.addBallot(address, 0);


        Address address_2("Gardom", 3, "Jerusalem");
        election.addBallot(address_2, 2);


        Address address_3("Ribel", 11, "Tel aviv");
        election.addBallot(address_3, 1);


        Address address_4("Gardom", 4, "Rehovot");
        election.addBallot(address_4, 3);



        // Create the citizens
        election.addVoter("Mor", 307307307, 1995, 1, false);
        election.addVoter("Lia", 209209209, 1997, 1, false);
        election.addVoter("Omer", 307307304, 1995, 2, true);
        election.addVoter("Yarin", 307307308, 1995, 2, true);
        election.addVoter("Keren", 307307309, 1995, 1, false);

        // Create members
        election.addMember("BIBI", 123456789, 1948, 2, 0, true);
        election.addMember("MIRI", 123456788, 1955, 1, 0, false);

        election.addMember("GANTZ", 123455789, 1948, 1, 1, false);
        election.addMember("LAPID", 123466789, 1960, 2, 1, true);

        election.addMember("SHELLY", 113456789, 1948, 2, 2, true);
        election.addMember("PEREZ", 223456789, 1948, 1, 2, false);
    }
}


void addNewBallot(ElectionCycle& election)
{
	string street, city;
	int numAddress;
	int ballotType;

	cout << "Please enter the address of ballot: first the street and then its number\n";
	cin >> street >> numAddress;
	cout << "Please enter city\n";
	//cleanBuffer();
	cin >> city;
	Address address(street, numAddress, city);

	cout << "Please enter 0 -  for regular ballot\n 1 - for military  ballot\n 2 - for isolation 3 - for military and isolation" << endl;
    cin >> ballotType;
	election.addBallot(address,ballotType);
	currBallot++;
}

void addNewCitizen(ElectionCycle& election)
{
	string name;
	int id;
	int year;
	int ballotNum;
	int flag = 1;
	bool isolation=false;

	while (flag)
	{
		cout << "Please enter the i.d and year of birth of the citizen:  \n";
		cin >> id;
		cin >> year;

		if (election.isIdExist(id))
		{
			cout << "ID already Exist. Do you want to try again? 1 for yes 0 for no" << endl;
			cleanBuffer();
			cin >> flag;
		}
		else
		{
			cout << "Please enter the name of the citizen: \n";
			//cleanBuffer();
			cin >> name;

            cout << "Please enter 0 for free and 1 for isolation"<<endl;
            cin >> isolation;

            int res=election.printBallotPerUser(2020-year,isolation);
            if(res==0)
            {
                cout<<"You are back to the main menu"<<endl<<endl;
                election.printLine();
                flag=0;
            }
            else
             {
                cout << "Please enter the serial number of ballot in the list"<< endl;
                cin >> ballotNum;
                if(election.checkBallot(ballotNum,isolation,2020-year))
                   election.addVoter(name, id, year, ballotNum, isolation);
                else
                {
                    cout<<"You are back to the main menu"<<endl<<endl;
                    election.printLine();
                }
                flag = 0;
            }
		}
	}
}

void addNewParty(ElectionCycle& election)
{
	string nameParty;
	int yearCreation, month;
	int faction;
	int flag = 1;


	while (flag)
	{
		cout << "Please enter the name of the party\n";
		cin >> nameParty;
		if (election.isPartyExist(nameParty))
		{
			cout << "Do you want to try again? 1 for yes 0 for no" << endl;
			cleanBuffer();
			cin >> flag;
		}
		else
		{
			cout << "Please enter the date of creation: year and after month\n";
			cin >> yearCreation >> month;
			cout << "Please enter faction: 1 for left, 2 for right, 3 for center\n";
			cin >> faction;
			Date date(yearCreation, month);

			election.addParty(nameParty, date, (Party::eFaction) faction);
			currParties++;
			flag = 0;
		}
	}
}

void addNewMember(ElectionCycle& election)
{
	string nameMember;
	int idMember;
	int yearOfBirth = INT_MIN;
	int ballotNumOfMember = INT_MIN;
	int partyNum;
	int flag = 1;
    bool isolation=false;
    int res=1;


	while (flag)
	{
		cout << "Please enter the i.d and year of birth of the member:  \n";
		cin >> idMember >> yearOfBirth;

		if (election.isMemberExist(idMember))
		{
			cout << "Do you want to try again? 1 for yes 0 for no" << endl;
			cleanBuffer();
			cin >> flag;
		}
		else
		{
			if (!election.isIdExist(idMember))
			{
				cout << "Please enter the name of the member: \n";
				cin >> nameMember;

                cout << "Please enter 0 for free and 1 for isolation"<<endl;
                cin >> isolation;

                res=election.printBallotPerUser(2020-yearOfBirth,isolation);

                if(res==0)
                {
                    cout<<"You are back to the main menu"<<endl<<endl;
                    election.printLine();
                    flag=0;
                }
                else
                {
                    cout << "Please choose ballot from the list" << endl<<endl;
                    cin >> ballotNumOfMember;

                }
			}
			else
			{
				cout << "The id number is already exist in the citizen array so he will be added only as member" << endl;
			}

            if(((res!=0)&&(election.checkBallot(ballotNumOfMember,isolation,2020-yearOfBirth)))||(election.isIdExist(idMember)))
            {
                for (int i = 0; i < election.getLogicalParties(); i++)
                {
                    cout << "For Party: " << election.getPartyByIndex(i)->getName() << " enter " << i + 1 << endl;
                }

                cin >> partyNum;

                election.addMember(nameMember, idMember, yearOfBirth, ballotNumOfMember, partyNum - 1, isolation);
                currCitizen++;

                flag = 0;
            }
            else
                {
                cout<<"You are back to the main menu"<<endl<<endl;
                election.printLine();
                flag=0;
            }
		}
	}
}

void startElection(ElectionCycle& election)
{
	initializeBallots(election.getBallotsArray(), election.getPartiesArray(),election);
	char option;
	bool isProtected;

    list<Citizen *>::const_iterator itr = election.getCitizenArray().begin();
    list<Citizen *>::const_iterator itrEnd = election.getCitizenArray().end();

    for (;itr!=itrEnd;++itr)
    {
		cout << (*itr)->getName() << " do you want to vote: Press \"y\" for yes or \"n\" for no" << endl;
		cin >> option;


		int partyChoice;
		if (option == 'y')
		{
            if((*itr)->getIsIsolated())
            {
                cout << "Are you protected? Press 0 for no or 1 for yes"<<endl;
                cleanBuffer();
                cin >> isProtected;
            }
            else{
                //
                isProtected = true;
            }

            if(isProtected) {
                cout << "please choose the party by its number\n" << endl;
                for (int k = 0; k < election.getLogicalParties(); k++) {
                    cout << "For Party: " << election.getPartyByIndex(k)->getName() << " enter " << k + 1 << endl;
                }
                for (int j = 0, flag = 1; j < TRIES && flag; j++) {
                    cin >> partyChoice;
                    if (partyChoice <= currParties) {
                        election.addVote((*itr), partyChoice - 1);
                        flag = 0;
                    } else {
                        cout << "Party doesn't exists try again. Do you want to try again? 1 - yes 0 - no \n" << endl;
                        cin >> flag;
                    }
                }
            }
            else
            {
                cout << "Sorry you are in isolation and you came not protected you cant vote moving to the next citizen" <<endl;
            }
		}
		else if (option == 'n')
		{
			cout << "O.K " << (*itr)->getName() << ", moving to the next voter\n" << endl;
		}
		else
		{
			cout << "Sorry you chose a non existent option moving to the next voter\n" << endl;
		}
	}
	election.setElectionFlag(true);
	//At the end we update the percentage pre ballot
	election.updatePrecentage();
}