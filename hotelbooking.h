#ifndef HOTELBOOKING_H
#define HOTELBOOKING_H

#include <iostream>
#include <iomanip>
#include <sstream>

#include "booking.h"


class HotelBooking : public Booking
{
public:
    HotelBooking(std::string id, double price, std::string fromDate, std::string toDate, long travelId, long customerId,
                 std::string buchungsTyp, std::string hotel, std::string town, std::string roomType,
                double hotelLatitude, double hotelLongitude);
    virtual std::string showDetails() override;

    const std::string &getHotel() const;
    const std::string &getTown() const;
    std::string getRoomType() const;

    void setHotel(const std::string &newHotel);
    void setTown(const std::string &newTown);
    void setRoomType(const std::string &newRoomType);

    double getHotelLatitude() const;
    double getHotelLongitude() const;

private:
    std::string hotel;
    std::string town;
    std::string roomType;
    double hotelLatitude;
    double hotelLongitude;
};

#endif // HOTELBOOKING_H
