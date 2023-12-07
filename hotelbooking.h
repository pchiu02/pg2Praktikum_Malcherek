#ifndef HOTELBOOKING_H
#define HOTELBOOKING_H

#include <iostream>
#include <iomanip>
#include <sstream>

#include "booking.h"


class HotelBooking : public Booking
{
public:
    HotelBooking(std::string id, double price, std::string fromDate, std::string toDate, long travelId,
                 std::string buchungsTyp, std::string hotel, std::string town, std::string roomType);
    virtual std::string showDetails() override;

    const std::string &getHotel() const;
    const std::string &getTown() const;

private:
    std::string hotel;
    std::string town;
    std::string roomType;
};

#endif // HOTELBOOKING_H
