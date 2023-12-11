#include "flightbooking.h"


FlightBooking::FlightBooking(std::string id, double price, std::string fromDate, std::string toDate, long travelId,
                             std::string buchungsTyp, std::string fromDestination, std::string toDestination, std::string airline,
                             std::string bookingClass)
    :Booking(id, price, fromDate, toDate, travelId, buchungsTyp)
{
    this->fromDestination = fromDestination;
    this->toDestination = toDestination;
    this->airline = airline;
    this->bookingClass = bookingClass;
}

std::string FlightBooking::showDetails()
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << price;

    return "Flughbuchung von " + fromDestination + " nach " + toDestination + " mit " + airline + " am " + fromDate +
            ". Preis: " + std::to_string(price) + " Euro";
}

const std::string &FlightBooking::getFromDestination() const
{
    return fromDestination;
}

const std::string &FlightBooking::getToDestination() const
{
    return toDestination;
}

const std::string &FlightBooking::getAirline() const
{
    return airline;
}

const std::string &FlightBooking::getBookingClass() const
{
    return bookingClass;
}
