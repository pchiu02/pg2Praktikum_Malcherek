#ifndef TRAVEL_H
#define TRAVEL_H

#include <memory>
#include <vector>
#include <memory.h>

#include "booking.h"

using namespace std;

class Travel
{
public:
    Travel(long id, long customerId);
    void addBooking(std::shared_ptr<Booking> booking);
    int getBookingCount();

    long getId() const;
    long getCustomerId() const;
    const vector<std::shared_ptr<Booking>> &getTravelBookings() const;

private:
    long id;
    long customerId;
    vector<std::shared_ptr<Booking>> travelBookings;
};

#endif // TRAVEL_H
