#ifndef __DATE_H
#define __DATE_H
#include <iostream>
using namespace std;


class Date
{
private:
	int year;
	int month;

public:
	int getYear()					const;
	int getMonth()					const;
	bool setYear(int year);
	bool setMonth(int month);
	Date(int year, int month);
    friend ostream& operator <<(ostream& os, const Date& date);
};


#endif // __DATE_H