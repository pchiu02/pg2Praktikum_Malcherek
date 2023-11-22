#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>



class Booking
{
public:
    Booking(std::string id, double price, std::string fromDate, std::string toDate);
    virtual std::string showDetails() = 0;
    virtual ~Booking() = default;

    const std::string &getId() const;
    double getPrice() const;
    const std::string &getFromDate() const;
    const std::string &getToDate() const;

protected:
    std::string id;
    double price;
    std::string fromDate;
    std::string toDate;

};

#endif // BOOKING_H
