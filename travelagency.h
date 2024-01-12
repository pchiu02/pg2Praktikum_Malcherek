#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include <iostream>
#include <vector>
#include <fstream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QMessageBox>
#include <memory>

#include "booking.h"
#include "customer.h"
#include "travel.h"
#include "airport.h"


class TravelAgency
{
public:
    TravelAgency();
    ~TravelAgency();
    void readFile(QString fileName);
    void readIataCode(QString fileName);
    QString getBookingsInfo();
    std::shared_ptr<Booking> findBooking(std::string id);
    std::shared_ptr<Travel> findTravel(long id);
    std::shared_ptr<Customer> findCustomer(long id, string &firstName, string &lastName);

    int getTotalFlightBooking() const;
    int getTotalHotelBooking() const;
    int getTotalRentalCarReservation() const;
    int getTotalTrainBooking() const;
    double getTotalFlightPrice() const;
    double getTotalHotelPrice() const;
    double getTotalRentalCarReservationPrice() const;
    double getTotalTrainPrice() const;
    const std::vector<std::shared_ptr<Booking>> &getAllBooking() const;
    const std::vector<std::shared_ptr<Customer>> &getAllCustomer() const;
    const std::vector<std::shared_ptr<Travel>> &getAllTravel() const;
    std::map<std::string, shared_ptr<Airport> > getAllAirport() const;
    std::shared_ptr<Airport> getAirport(const std::string& iataCode);
    bool hasAirport(const std::string& iataCode) const;

private:
    std::vector<std::shared_ptr<Booking>> allBooking;
    std::vector<std::shared_ptr<Customer>> allCustomer;
    std::vector<std::shared_ptr<Travel>> allTravel;
    std::map<std::string , shared_ptr<Airport>> allAirport;
    int totalFlightBooking = 0;
    int totalHotelBooking = 0;
    int totalRentalCarReservation = 0;
    int totalTrainBooking = 0;
    int travelCount = 0;
    int totalCustomer = 0;

    double totalFlightPrice = 0;
    double totalHotelPrice = 0;
    double totalRentalCarReservationPrice = 0;
    double totalTrainPrice = 0;
};

#endif // TRAVELAGENCY_H
