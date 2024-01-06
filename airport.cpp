#include "airport.h"

Airport::Airport(std::string name, std::string isoCountry, std::string municipality, std::string iataCode) {
    this->name = name;
    this->isoCountry = isoCountry;
    this->municipality = municipality;
    this->iataCode = iataCode;
}

std::string Airport::getIataCode() const
{
    return iataCode;
}

std::string Airport::getMunicipality() const
{
    return municipality;
}

std::string Airport::getIsoCountry() const
{
    return isoCountry;
}

std::string Airport::getName() const
{
    return name;
}
