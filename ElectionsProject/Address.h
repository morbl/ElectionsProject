#ifndef __ADDRESS_H
#define __ADDRESS_H
#include <iostream>
#include <string>
using namespace std;
#pragma warning (disable: 4996)

class Address
{
private:
	string street;
	int number;
    string city;

public:
    //getters
    string getStreet()					const;
	int getNumber()						const;
    string getCity()					const;
    //Setters
	bool setNumber(int number);
	bool setCity(const string& city);
	bool setStreet(const string& street);

	// Print operator for address
    friend ostream& operator <<(ostream& os, const Address& address);

    // c'tor
	Address(const string& street, int number, const string& city);

};

#endif // __ADDRESS_H