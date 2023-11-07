#ifndef FLIGHTBOOKING_H
#define FLIGHTBOOKING_H

#include <iostream>
#include <iomanip>
#include <sstream>

#include "booking.h"


class FlightBooking : public Booking
{
public:
    FlightBooking(std::string id , double price, std::string fromDate, std::string toDate,
                  std::string fromDestination, std::string toDestination, std::string airline);
    virtual std::string showDetails() override;

private:
    std::string fromDestination;
    std::string toDestination;
    std::string airline;
};

#endif // FLIGHTBOOKING_H
