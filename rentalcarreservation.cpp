#include "rentalcarreservation.h"


RentalCarReservation::RentalCarReservation(std::string id, double price, std::string fromDate, std::string toDate,
                                           std::string pickupLocation, std::string returnLocation, std::string company)
                                            : Booking(id, price, fromDate, toDate)
{
    this->pickupLocation = pickupLocation;
    this->returnLocation = returnLocation;
    this->company = company;
}

std::string RentalCarReservation::showDetails()
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << price;

    return "Mietwagenreservierung mit " + company + ". Abholung am " + fromDate + " in " + pickupLocation +
            ". Rueckgabe am " + toDate + " in " + returnLocation + ". Preis: " + std::to_string(price);
}
