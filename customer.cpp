#include "customer.h"

Customer::Customer(long id, string lastName, string firstName)
{
    this->id = id;
    this->lastName = lastName;
    this->firstName = firstName;
}

void Customer::addTravel(std::shared_ptr<Travel> travel){
    travelList.push_back(travel);
}

bool Customer::hasTravel(const std::shared_ptr<Travel> travel) const{
    for(const std::shared_ptr<Travel>  &t : travelList)
    {
        if(t == travel)
        {
            return true;
        }
    }
    return false;
}

int Customer::getTravelCount()
{
    return travelList.size();
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

vector<std::shared_ptr<Travel>> Customer::getTravelList() const
{
    return travelList;
}
