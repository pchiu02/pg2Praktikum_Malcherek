#include "customer.h"

Customer::Customer(long id, string lastName, string firstName)
{
    this->id = id;
    this->lastName = lastName;
    this->firstName = firstName;
}

void Customer::addTravel(Travel* travel){
    travelList.push_back(travel);
}

bool Customer::hasTravel(const Travel *travel) const{
    for(const Travel* t : travelList)
    {
        if(t == travel)
        {
            return true;
        }
    }
    return false;
}

long Customer::getId() const
{
    return id;
}

string Customer::getLastName() const
{
    return lastName;
}

string Customer::getFirstName() const
{
    return firstName;
}

vector<Travel *> Customer::getTravelList() const
{
    return travelList;
}
