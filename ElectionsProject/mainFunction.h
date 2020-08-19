

#ifndef UNTITLED20_MAINFUNCTIONS_H
#define UNTITLED20_MAINFUNCTIONS_H

#include "ElectionCycle.h"
// Function get the election by ref and starts the interactive menu
void interActiveMenu(ElectionCycle& election);
//The function gets the choice from the user and acts accordingly
void doChoice(int choice, ElectionCycle& election);
// Initialized the result in the each ballot
void initializeBallots(list<Ballot *>& ballots, list<Party *>& parties, const ElectionCycle& election);
// First initialize: citizens ballots and parties all hard coded
void firstInit(ElectionCycle& election);
// Prints the menu for the user
void printMenu();
// Add new ballots to the election
void addNewBallot(ElectionCycle& election);
// Add new citizen to the election
void addNewCitizen(ElectionCycle& election);
// Add new party to the election
void addNewParty(ElectionCycle& election);
// Add new member to the election
void addNewMember(ElectionCycle& election);
// Start the election
void startElection(ElectionCycle& election);
// Clean the buffer
void cleanBuffer();




const int NUM_CITIZEN = 5;
const int NUM_PARTIES = 3;
const int NUM_BALLOT = 2;
const int EXIT = 10;
const int TRIES = 3;






#endif //UNTITLED20_MAINFUNCTIONS_H
