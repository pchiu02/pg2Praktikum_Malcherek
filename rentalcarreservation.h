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
                         std::string buchungsTyp, std::string pickupLocation, std::string returnLocation, std::string company,
                         std::string vehicleClass, double pickupLatitude, double pickupLongitude, double returnLatitude, double returnLongitude);
    virtual std::string showDetails() override;

    const std::string &getPickupLocation() const;
    const std::string &getReturnLocation() const;
    const std::string &getCompany() const;
    std::string getVehicleClass() const;

    void setPickupLocation(const std::string &newPickupLocation);
    void setReturnLocation(const std::string &newReturnLocation);
    void setCompany(const std::string &newCompany);
    void setVehicleClass(const std::string &newVehicleClass);

    double getPickupLatitude() const;

    double getPickupLongitude() const;

    double getReturnLatitude() const;

    double getReturnLongitude() const;

private:
    std::string pickupLocation;
    std::string returnLocation;
    std::string company;
    std::string vehicleClass;
    double pickupLatitude;
    double pickupLongitude;
    double returnLatitude;
    double returnLongitude;
};

#endif // RENTALCARRESERVATION_H
