#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include <memory>



class Booking
{
public:
    Booking(std::string id, double price, std::string fromDate, std::string toDate, long travelId, long customerId, std::string buchungsTyp
            ,std::string predecessor1, std::string predecessor2);
    virtual std::string showDetails() = 0;
    virtual ~Booking() = default;

    bool overlapsWith(const std::shared_ptr<Booking>& other) const;

    const std::string &getId() const;
    double getPrice() const;
    const std::string &getFromDate() const;
    const std::string &getToDate() const;
    long getTravelId() const;
    const std::string &getBuchungsTyp() const;
    std::string getPredecessor1() const;
    std::string getPredecessor2() const;

    void setId(const std::string &newId);
    void setPrice(double newPrice);
    void setFromDate(const std::string &newFromDate);
    void setToDate(const std::string &newToDate);
    long getCustomerId() const;



protected:
    std::string id;
    double price;
    std::string fromDate;
    std::string toDate;
    long travelId;
    long customerId;
    std::string buchungsTyp;
    std::string predecessor1;
    std::string predecessor2;
};

#endif // BOOKING_H
