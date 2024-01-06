#ifndef AIRPORT_H
#define AIRPORT_H

#include <iostream>
#include <string>


class Airport
{
public:
    Airport(std::string name, std::string isoCountry, std::string municipality, std::string iataCode);

    std::string getIataCode() const;
    std::string getMunicipality() const;
    std::string getIsoCountry() const;
    std::string getName() const;

private:
    std::string name;
    std::string isoCountry;
    std::string municipality;
    std::string iataCode;
};

#endif // AIRPORT_H
