#ifndef CONNECTINGSTATION_H
#define CONNECTINGSTATION_H

#include <iostream>
#include <string>

class ConnectingStation
{
public:
    ConnectingStation(const std::string stationName, double latitude, double longitude);

    std::string getStationName() const;
    double getLatitude() const;
    double getLongitude() const;

private:
    std::string stationName;
    double latitude;
    double longitude;
};

#endif // CONNECTINGSTATION_H
