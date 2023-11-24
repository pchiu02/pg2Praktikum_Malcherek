#include "rentalcarreservation.h"


RentalCarReservation::RentalCarReservation(std::string id, double price, std::string fromDate, std::string toDate, long travelId,
                                           std::string pickupLocation, std::string returnLocation, std::string company,
                                           std::string vehicleClass)
                                            : Booking(id, price, fromDate, toDate, travelId)
{
    this->pickupLocation = pickupLocation;
    this->returnLocation = returnLocation;
    this->company = company;
    this->vehicleClass = vehicleClass;
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
