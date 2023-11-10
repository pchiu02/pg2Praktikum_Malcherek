#include "hotelbooking.h"

HotelBooking::HotelBooking(std::string id, double price, std::string fromDate,
                           std::string toDate, std::string hotel, std::string town)
    :Booking(id, price, fromDate, toDate)
{
    this->hotel = hotel;
    this->town = town;
}

std::string HotelBooking::showDetails()
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << price;

    return "Hotelreservierung im " + hotel + " in " + town + " vom "
            + fromDate + " bis zum " + toDate + ". Preis: " + std::to_string(price);
}

const std::string &HotelBooking::getHotel() const
{
    return hotel;
}

const std::string &HotelBooking::getTown() const
{
    return town;
}
