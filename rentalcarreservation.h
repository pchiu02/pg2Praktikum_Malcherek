#ifndef RENTALCARRESERVATION_H
#define RENTALCARRESERVATION_H

#include <iostream>
#include <iomanip>
#include <sstream>

#include "booking.h"


class RentalCarReservation : public Booking
{
public:
    RentalCarReservation(std::string id, double price, std::string fromDate, std::string toDate, long travelId,
                         std::string pickupLocation, std::string returnLocation, std::string company,
                         std::string vehicleClass);
    virtual std::string showDetails() override;

    const std::string &getPickupLocation() const;
    const std::string &getReturnLocation() const;
    const std::string &getCompany() const;

private:
    std::string pickupLocation;
    std::string returnLocation;
    std::string company;
    std::string vehicleClass;
};

#endif // RENTALCARRESERVATION_H
