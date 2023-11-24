#include "travel.h"

Travel::Travel(long id, long customerId)
{
    this->id = id;
    this->customerId = customerId;
}

void Travel::addBooking(Booking* booking){
    travelBookings.push_back(booking);
}

long Travel::getId() const
{
    return id;
}

long Travel::getCustomerId() const
{
    return customerId;
}
