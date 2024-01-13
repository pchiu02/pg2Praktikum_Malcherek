#include "hotelbooking.h"

HotelBooking::HotelBooking(std::string id, double price, std::string fromDate,
                           std::string toDate, long travelId, long customerId, std::string buchungsTyp, std::string hotel, std::string town,
                           std::string roomType, double hotelLatitude, double hotelLongitude)
    :Booking(id, price, fromDate, toDate, travelId, customerId, buchungsTyp)
{
    this->hotel = hotel;
    this->town = town;
    this->roomType = roomType;
    this->hotelLatitude = hotelLatitude;
    this->hotelLongitude = hotelLongitude;
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

std::string HotelBooking::getRoomType() const
{
    return roomType;
}

void HotelBooking::setHotel(const std::string &newHotel)
{
    hotel = newHotel;
}

void HotelBooking::setTown(const std::string &newTown)
{
    town = newTown;
}

void HotelBooking::setRoomType(const std::string &newRoomType)
{
    roomType = newRoomType;
}

double HotelBooking::getHotelLatitude() const
{
    return hotelLatitude;
}

double HotelBooking::getHotelLongitude() const
{
    return hotelLongitude;
}
