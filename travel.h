#ifndef TRAVEL_H
#define TRAVEL_H

#include <vector>

#include "booking.h"

using namespace std;

class Travel
{
public:
    Travel(long id, long customerId);
    void addBooking(Booking* booking);

    long getId() const;
    long getCustomerId() const;

private:
    long id;
    long customerId;
    vector<Booking*> travelBookings;
};

#endif // TRAVEL_H
