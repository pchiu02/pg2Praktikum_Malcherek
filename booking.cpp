#include "booking.h"


Booking::Booking(std::string id, double price, std::string fromDate, std::string toDate, long travelId, std::string buchungsTyp)
{
    this->id = id;
    this->price = price;
    this->fromDate = fromDate;
    this->toDate = toDate;
    this->travelId = travelId;
    this->buchungsTyp = buchungsTyp;
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
