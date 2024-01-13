#ifndef CHECK_H
#define CHECK_H

#include <memory>

#include "travelagency.h"

class Check
{
public:
    explicit Check(std::shared_ptr<TravelAgency> agency);
    bool checkTravelDisjunct(QString& message);

private:
    std::shared_ptr<TravelAgency> travelAgency;
};

#endif // CHECK_H
