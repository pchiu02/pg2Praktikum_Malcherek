#include "trainticket.h"


TrainTicket::TrainTicket(std::string id, double price, std::string fromDate, std::string toDate, long travelId, std::string buchungsTyp,
                         std::string fromDestination, std::string toDestination, std::string departureTime, std::string arrivalTime,
                         std::vector<std::string> connectingStations, std::string ticketType)
    :Booking(id, price, fromDate, toDate, travelId, buchungsTyp)
{
    this->fromDestination = fromDestination;
    this->toDestination = toDestination;
    this->departureTime = departureTime;
    this->arrivalTime = arrivalTime;
    this->connectingStations = connectingStations;
    this->ticketType = ticketType;
}

std::string TrainTicket::showDetails()
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << price;

    std::string details = "Zugticket von " + fromDestination + " nach " + toDestination + " am " + fromDate +
            " um " + departureTime;
    if(!connectingStations.empty())
    {
        details += " ueber ";
        for(size_t i = 0; i < connectingStations.size(); i++)
        {
            details += connectingStations[i];
            if(i < connectingStations.size() - 1) //Check if its not the last station
            {
                details += ", ";
            }
        }
    }

    details += ". Preis: " + std::to_string(price) + " Euro";
    return details;
}

const std::string &TrainTicket::getFromDestination() const
{
    return fromDestination;
}

const std::string &TrainTicket::getToDestination() const
{
    return toDestination;
}

const std::string &TrainTicket::getDepartureTime() const
{
    return departureTime;
}

const std::string &TrainTicket::getArrivalTime() const
{
    return arrivalTime;
}

const std::vector<std::string> &TrainTicket::getConnectingStations() const
{
    return connectingStations;
}
