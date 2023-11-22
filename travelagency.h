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

#include "booking.h"
#include "customer.h"
#include "travel.h"


class TravelAgency
{
public:
    TravelAgency();
    ~TravelAgency();
    void readFile(QString fileName);
    Booking* findBooking(long id);
    Travel* findTravel(long id);
    Customer* findCustomer(long id);

    int getTotalFlightBooking() const;
    int getTotalHotelBooking() const;
    int getTotalRentalCarReservation() const;
    int getTotalTrainBooking() const;
    double getTotalFlightPrice() const;
    double getTotalHotelPrice() const;
    double getTotalRentalCarReservationPrice() const;
    double getTotalTrainPrice() const;
    const std::vector<Booking *> &getBookings() const;

private:
    std::vector<Booking*> bookings;
    std::vector<Customer*> allCustomer;
    std::vector<Travel*> allTravel;
    int totalFlightBooking = 0;
    int totalHotelBooking = 0;
    int totalRentalCarReservation = 0;
    int totalTrainBooking = 0;

    double totalFlightPrice = 0;
    double totalHotelPrice = 0;
    double totalRentalCarReservationPrice = 0;
    double totalTrainPrice = 0;
};

#endif // TRAVELAGENCY_H
