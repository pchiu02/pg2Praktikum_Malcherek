    #ifndef FLIGHTBOOKING_H
#define FLIGHTBOOKING_H

#include <iostream>
#include <iomanip>
#include <sstream>

#include "booking.h"


class FlightBooking : public Booking
{
public:
    FlightBooking(std::string id , double price, std::string fromDate, std::string toDate, long travelId, long customerId,
                  std::string buchungsTyp, std::string predecessor1, std::string predecessor2, std::string fromDestination, std::string toDestination, std::string airline,
                  std::string bookingClass, double fromDestLatitude, double fromDestLongitude, double toDestLatitude, double toDestLongitude);
    virtual std::string showDetails() override;

    const std::string &getFromDestination() const;
    const std::string &getToDestination() const;
    const std::string &getAirline() const;
    const std::string &getBookingClass() const;

    void setAirline(const std::string &newAirline);
    void setToDestination(const std::string &newToDestination);
    void setFromDestination(const std::string &newFromDestination);
    void setBookingClass(const std::string &newBookingClass);

    double getFromDestLatitude() const;
    double getFromDestLongitude() const;
    double getToDestLatitude() const;
    double getToDestLongitude() const;

private:
    std::string fromDestination;
    std::string toDestination;
    std::string airline;
    std::string bookingClass;
    double fromDestLatitude;
    double fromDestLongitude;
    double toDestLatitude;
    double toDestLongitude;
};

#endif // FLIGHTBOOKING_H
