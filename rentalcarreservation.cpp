#include "rentalcarreservation.h"


RentalCarReservation::RentalCarReservation(std::string id, double price, std::string fromDate, std::string toDate, long travelId, long customerId, std::string buchungsTyp,
                                           std::string pickupLocation, std::string returnLocation, std::string company,
                                           std::string vehicleClass, double pickupLatitude, double pickupLongitude, double returnLatitude, double returnLongitude)
                                            : Booking(id, price, fromDate, toDate, travelId, customerId, buchungsTyp)
{
    this->pickupLocation = pickupLocation;
    this->returnLocation = returnLocation;
    this->company = company;
    this->vehicleClass = vehicleClass;
    this->pickupLatitude = pickupLatitude;
    this->pickupLongitude = pickupLongitude;
    this->returnLatitude = returnLatitude;
    this->returnLongitude = returnLongitude;
}

std::string RentalCarReservation::showDetails()
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << price;

    return "Mietwagenreservierung mit " + company + ". Abholung am " + fromDate + " in " + pickupLocation +
            ". Rueckgabe am " + toDate + " in " + returnLocation + ". Preis: " + std::to_string(price);
}

const std::string &RentalCarReservation::getPickupLocation() const
{
    return pickupLocation;
}

const std::string &RentalCarReservation::getReturnLocation() const
{
    return returnLocation;
}

const std::string &RentalCarReservation::getCompany() const
{
    return company;
}

std::string RentalCarReservation::getVehicleClass() const
{
    return vehicleClass;
}

void RentalCarReservation::setPickupLocation(const std::string &newPickupLocation)
{
    pickupLocation = newPickupLocation;
}

void RentalCarReservation::setReturnLocation(const std::string &newReturnLocation)
{
    returnLocation = newReturnLocation;
}

void RentalCarReservation::setCompany(const std::string &newCompany)
{
    company = newCompany;
}

void RentalCarReservation::setVehicleClass(const std::string &newVehicleClass)
{
    vehicleClass = newVehicleClass;
}

double RentalCarReservation::getPickupLatitude() const
{
    return pickupLatitude;
}

double RentalCarReservation::getPickupLongitude() const
{
    return pickupLongitude;
}

double RentalCarReservation::getReturnLatitude() const
{
    return returnLatitude;
}

double RentalCarReservation::getReturnLongitude() const
{
    return returnLongitude;
}
