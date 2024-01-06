#include "connectingstation.h"

ConnectingStation::ConnectingStation(const std::string stationName, double latitude, double longitude) {
    this->stationName = stationName;
    this->latitude = latitude;
    this->longitude = longitude;
}

std::string ConnectingStation::getStationName() const
{
    return stationName;
}

double ConnectingStation::getLatitude() const
{
    return latitude;
}

double ConnectingStation::getLongitude() const
{
    return longitude;
}
