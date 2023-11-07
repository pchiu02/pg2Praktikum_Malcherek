#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H

#include <iostream>
#include <vector>
#include <fstream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "booking.h"


class TravelAgency
{
public:
    TravelAgency();
    ~TravelAgency();
    void readFile();
    void readBinaryFile();

private:
    std::vector<Booking*> bookings;
};

#endif // TRAVELAGENCY_H
