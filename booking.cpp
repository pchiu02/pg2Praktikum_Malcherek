#include "booking.h"


Booking::Booking(std::string id, double price, std::string fromDate, std::string toDate)
{
    this->id = id;
    this->price = price;
    this->fromDate = fromDate;
    this->toDate = toDate;
}
