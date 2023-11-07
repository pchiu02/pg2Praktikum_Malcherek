#ifndef TRAINTICKET_H
#define TRAINTICKET_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

#include "booking.h"


class TrainTicket : public Booking
{
public:
    TrainTicket(std::string id, double price, std::string fromDate, std::string toDate,
                std::string fromDestination, std::string toDestination, std::string departureTime,
                std::string arrivalTime, std::vector<std::string> connectingStations);
    virtual std::string showDetails() override;

private:
    std::string fromDestination;
    std::string toDestination;
    std::string departureTime;
    std::string arrivalTime;
    std::vector<std::string> connectingStations;
};

#endif // TRAINTICKET_H
