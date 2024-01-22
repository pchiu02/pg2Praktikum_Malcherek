#ifndef TRAINTICKET_H
#define TRAINTICKET_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

#include "connectingstation.h"

#include "booking.h"


class TrainTicket : public Booking
{
public:
    TrainTicket(std::string id, double price, std::string fromDate, std::string toDate, long travelId, long customerId,
                std::string buchungsTyp, std::string predecessor1, std::string predecessor2, std::string fromDestination, std::string toDestination, std::string departureTime,
                std::string arrivalTime, std::vector<ConnectingStation> connectingStations,
                std::string ticketType, double fromStationLatitude, double fromStationLongitude, double toStationLatitude,
                double toStationLongitude);
    virtual std::string showDetails() override;

    const std::string &getFromDestination() const;
    const std::string &getToDestination() const;
    const std::string &getDepartureTime() const;
    const std::string &getArrivalTime() const;
    const std::vector<ConnectingStation> &getConnectingStations() const;
    std::string getTicketType() const;
    std::vector<std::pair<double, double>> getAllStationCoordinates() const;

    void setFromDestination(const std::string &newFromDestination);
    void setToDestination(const std::string &newToDestination);
    void setDepartureTime(const std::string &newDepartureTime);
    void setArrivalTime(const std::string &newArrivalTime);
    void setTicketType(const std::string &newTicketType);
    void setConnectingStations(const std::vector<ConnectingStation> &newConnectingStations);

private:
    std::string fromDestination;
    std::string toDestination;
    std::string departureTime;
    std::string arrivalTime;
    std::string ticketType;
    std::vector<ConnectingStation> connectingStations;
    double fromStationLatitude;
    double fromStationLongitude;
    double toStationLatitude;
    double toStationLongitude;
};

#endif // TRAINTICKET_H
