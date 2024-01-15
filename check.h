#ifndef CHECK_H
#define CHECK_H

#include <memory>
#include <QObject>
#include <QString>

#include "travelagency.h"

class Check : public QObject
{
    Q_OBJECT

public:
    explicit Check(std::shared_ptr<TravelAgency> travelAgency, QObject *parent = nullptr)
        : QObject(parent), travelAgency(travelAgency) {}
    bool checkTravelDisjunct(QString& message);

public slots:
    void checkBookings();


private:
    std::shared_ptr<TravelAgency> travelAgency;
};

#endif // CHECK_H
