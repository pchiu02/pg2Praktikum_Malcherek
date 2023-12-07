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
    TrainTicket(std::string id, double price, std::string fromDate, std::string toDate, long travelId,
                std::string buchungsTyp, std::string fromDestination, std::string toDestination, std::string departureTime,
                std::string arrivalTime, std::vector<std::string> connectingStations,
                std::string ticketType);
    virtual std::string showDetails() override;

    const std::string &getFromDestination() const;
    const std::string &getToDestination() const;
    const std::string &getDepartureTime() const;
    const std::string &getArrivalTime() const;
    const std::vector<std::string> &getConnectingStations() const;

private:
    std::string fromDestination;
    std::string toDestination;
    std::string departureTime;
    std::string arrivalTime;
    std::string ticketType;
    std::vector<std::string> connectingStations;
};

#endif // TRAINTICKET_H
