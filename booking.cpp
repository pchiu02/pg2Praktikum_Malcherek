#include "booking.h"
#include <memory>


Booking::Booking(std::string id, double price, std::string fromDate, std::string toDate, long travelId, long customerId, std::string buchungsTyp, std::string predecessor1, std::string predecessor2)
{
    this->id = id;
    this->price = price;
    this->fromDate = fromDate;
    this->toDate = toDate;
    this->travelId = travelId;
    this->buchungsTyp = buchungsTyp;
    this->customerId = customerId;
    this->predecessor1 = predecessor1;
    this->predecessor2 = predecessor2;
}

bool Booking::overlapsWith(const std::shared_ptr<Booking>& other) const{
    auto thisFromDate = this->getFromDate();
    auto thisToDate = this->getToDate();
    auto otherFromDate = other->getFromDate();
    auto otherToDate = other->getToDate();

    return thisFromDate <= otherToDate && otherFromDate <= thisToDate;
}

const std::string &Booking::getId() const
{
    return id;
}

double Booking::getPrice() const
{
    return price;
}

const std::string &Booking::getFromDate() const
{
    return fromDate;
}

const std::string &Booking::getToDate() const
{
    return toDate;
}

long Booking::getTravelId() const
{
    return travelId;
}

const std::string &Booking::getBuchungsTyp() const
{
    return buchungsTyp;
}

void Booking::setId(const std::string &newId)
{
    id = newId;
}

void Booking::setPrice(double newPrice)
{
    price = newPrice;
}

void Booking::setFromDate(const std::string &newFromDate)
{
    fromDate = newFromDate;
}

void Booking::setToDate(const std::string &newToDate)
{
    toDate = newToDate;
}

long Booking::getCustomerId() const
{
    return customerId;
}

std::string Booking::getPredecessor1() const
{
    return predecessor1;
}

std::string Booking::getPredecessor2() const
{
    return predecessor2;
}
