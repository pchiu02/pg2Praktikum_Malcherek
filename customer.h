#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>

#include "travel.h"

using namespace std;


class Customer
{
public:
    Customer(long id, string lastName, string firstName);
    void addTravel(Travel* travel);
    bool hasTravel(const Travel *travel) const;

    long getId() const;
    string getLastName() const;
    string getFirstName() const;
    vector<Travel *> getTravelList() const;

private:
    long id;
    string lastName;
    string firstName;
    vector<Travel*> travelList;

};

#endif // CUSTOMER_H
