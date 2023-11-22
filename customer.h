#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>

#include "travel.h"

using namespace std;


class Customer
{
public:
    Customer();
    void addTravel(Travel* travel);

private:
    long id;
    string lastName;
    string firstName;
    vector<Travel*> travelList;

};

#endif // CUSTOMER_H
