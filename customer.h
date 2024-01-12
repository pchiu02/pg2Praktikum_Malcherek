#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <memory>

#include "travel.h"

using namespace std;


class Customer
{
public:
    Customer(long id, string lastName, string firstName);
    void addTravel(std::shared_ptr<Travel> travel);
    bool hasTravel(const std::shared_ptr<Travel> travel) const;
    int getTravelCount();

    long getId() const;
    string getLastName() const;
    string getFirstName() const;
    vector<std::shared_ptr<Travel>> getTravelList() const;

private:
    long id;
    string lastName;
    string firstName;
    vector<std::shared_ptr<Travel>> travelList;

};

#endif // CUSTOMER_H
