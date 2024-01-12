#include "travel.h"

Travel::Travel(long id, long customerId)
{
    this->id = id;
    this->customerId = customerId;
}

void Travel::addBooking(std::shared_ptr<Booking> booking){
    travelBookings.push_back(booking);
}

int Travel::getBookingCount()
{
    return travelBookings.size();
}

long Travel::getId() const
{
    return id;
}

long Travel::getCustomerId() const
{
    return customerId;
}

const vector<std::shared_ptr<Booking>> &Travel::getTravelBookings() const
{
    return travelBookings;
}
