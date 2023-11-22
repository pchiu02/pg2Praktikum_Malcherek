#ifndef TRAVEL_H
#define TRAVEL_H

#include <vector>

#include "booking.h"

using namespace std;

class Travel
{
public:
    Travel();
    void addBooking(Booking* booking);

private:
    long id;
    long customerId;
    vector<Booking*> travelBookings;
};

#endif // TRAVEL_H
