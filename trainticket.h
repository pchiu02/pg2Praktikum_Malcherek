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
    std::string getTicketType() const;

    void setFromDestination(const std::string &newFromDestination);

    void setToDestination(const std::string &newToDestination);

    void setDepartureTime(const std::string &newDepartureTime);

    void setArrivalTime(const std::string &newArrivalTime);

    void setTicketType(const std::string &newTicketType);

    void setConnectingStations(const std::vector<std::string> &newConnectingStations);

private:
    std::string fromDestination;
    std::string toDestination;
    std::string departureTime;
    std::string arrivalTime;
    std::string ticketType;
    std::vector<std::string> connectingStations;
};

#endif // TRAINTICKET_H
