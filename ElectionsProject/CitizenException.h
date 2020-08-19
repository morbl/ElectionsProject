
#ifndef PLEASEFINAL_CITIZENEXCEPTION_H
#define PLEASEFINAL_CITIZENEXCEPTION_H
#include <iostream>
using namespace std;
class CitizenException
{
public:
    virtual  void show() const = 0;
};

class IdException: public CitizenException
{
private:
    int id;
public:
    IdException(int id): id(id){}
    virtual void show() const
    {
        cout << "Invalid ID" << endl;
    }
};


class ageException: public CitizenException
{
private:
    int age;
public:
    ageException(int age): age(age){}
    virtual void show() const
    {
        cout << "Wrong age" << endl;
    }
};

#endif //PLEASEFINAL_CITIZENEXCEPTION_H
