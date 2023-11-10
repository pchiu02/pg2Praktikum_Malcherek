#include "booking.h"


Booking::Booking(std::string id, double price, std::string fromDate, std::string toDate)
{
    this->id = id;
    this->price = price;
    this->fromDate = fromDate;
    this->toDate = toDate;
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
