#ifndef HOTELBOOKING_H
#define HOTELBOOKING_H

#include <iostream>
#include <iomanip>
#include <sstream>

#include "booking.h"


class HotelBooking : public Booking
{
public:
    HotelBooking(std::string id, double price, std::string fromDate, std::string toDate,
                 std::string hotel, std::string town);
    virtual std::string showDetails() override;

    const std::string &getHotel() const;
    const std::string &getTown() const;

private:
    std::string hotel;
    std::string town;
};

#endif // HOTELBOOKING_H
