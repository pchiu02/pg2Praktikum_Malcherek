#include "check.h"

#include <QMessageBox>

bool Check::checkTravelDisjunct(QString &message)
{
    auto bookings = travelAgency->getAllBooking();
    auto customers = travelAgency->getAllCustomer();

    for (const auto& customer : customers){
        std::vector<std::shared_ptr<Booking>> customerBookings;

        for(const auto& booking : bookings){
            if(booking->getCustomerId() == customer->getId()){
                customerBookings.push_back(booking);
            }
        }

        for(size_t i = 0; i < customerBookings.size(); ++i){
            for(size_t j = i + 1; j < customerBookings.size(); ++j){
                if(customerBookings[i]->overlapsWith(customerBookings[j])){
                    std::string fullName = customer->getFirstName() + " " + customer->getLastName();
                    long travelId1 = customerBookings[i]->getTravelId();
                    long travelId2 = customerBookings[j]->getTravelId();
                    message = QString("Overlapping trips found for customer ID %1. Conflicting travels: %2 and %3.")
                                      .arg(customer->getId()).arg(travelId1).arg(travelId2);
                    return true;
                }
            }
        }
    }
    std::cout << "Check called" << std::endl;
    return false;
}

void Check::checkNoMissingHotels()
{
    std::vector<std::shared_ptr<Travel>> travels = travelAgency->getAllTravel();
    QString message;
    QString errorType = "Missing Hotel";

    for (auto& travel: travels){
        auto sortedBookings = travel->sortTopologically();

        for(size_t i = 0; i < sortedBookings.size() - 1; ++i ){
            auto currentBooking = sortedBookings[i];
            auto nextBooking = sortedBookings[i+1];
            qDebug() << "Current booking to date:" << QString::fromStdString(currentBooking->getToDate());
            qDebug() << "Next booking from date:" << QString::fromStdString(nextBooking->getFromDate());

            //Ignore car Rentals
            if(currentBooking->getBuchungsTyp() == "RentalCar" || nextBooking->getBuchungsTyp() == "RentalCar"){
                continue;
            }

            //check for gaps in accomodation
            if(currentBooking->getToDate() != nextBooking->getFromDate()){
                message += "Gap found in travelID " + QString::number(travel->getId())
                           + " between bookings ending on " + QString::fromStdString(currentBooking->getToDate())
                           + " and starting on " + QString::fromStdString(nextBooking->getFromDate()) + "\n";


            }
        }
    }
    emit sendCheckResult(errorType, message);
    if(!message.isEmpty()){
        qDebug() << message;
    } else {
        qDebug() << "no missing hotels or gap in any travels";
    }
}

void Check::checkNoOverlappingHotels()
{
    std::vector<std::shared_ptr<Travel>> travels = travelAgency->getAllTravel();
    QString message;
    QString errorType = "Overlapping Hotel";

    for(auto& travel : travels){
        auto sortedBookings = travel->sortTopologically();

        for(size_t i = 0; i < sortedBookings.size() - 1; ++i){
            auto currentBooking = sortedBookings[i];
            auto nextBooking = sortedBookings[i+1];

            //Ignore car Rentals
            if(currentBooking->getBuchungsTyp() == "RentalCar" || nextBooking->getBuchungsTyp() == "RentalCar"){
                continue;
            }

            // Check for overlapping bookings
            if(currentBooking->getToDate() > nextBooking->getFromDate()){
                message += "Overlap found in travelID " + QString::number(travel->getId())
                           + " between bookings ending on " + QString::fromStdString(currentBooking->getToDate())
                           + " and starting on " + QString::fromStdString(nextBooking->getFromDate()) + "\n";
            }
        }
    }
    emit sendCheckResult(errorType, message);
    if(!message.isEmpty()){
        qDebug() << message;
    }else{
        qDebug() << "No overlapping hotels in any travels";
    }
}

void Check::checkNoOverlappingRentalCars()
{
    std::vector<std::shared_ptr<Travel>> travels = travelAgency->getAllTravel();
    QString message;
    QString errorType = "Overlapping Cars";

    for(auto& travel : travels){
        auto sortedBookings = travel->sortTopologically();

        for(size_t i = 0; i < sortedBookings.size() - 1; ++i){
            auto currentBooking = sortedBookings[i];
            auto nextBooking = sortedBookings[i+1];

            //Ignore car Rentals
            if(currentBooking->getBuchungsTyp() == "Hotel" || nextBooking->getBuchungsTyp() == "Hotel"){
                continue;
            }

            // Check for overlapping bookings
            if(currentBooking->getToDate() > nextBooking->getFromDate()){
                message += "Overlap found in travelID " + QString::number(travel->getId())
                           + " between bookings ending on " + QString::fromStdString(currentBooking->getToDate())
                           + " and starting on " + QString::fromStdString(nextBooking->getFromDate()) + "\n";
            }
        }
    }
    emit sendCheckResult(errorType, message);
    if(!message.isEmpty()){
        qDebug() << message;
    }else{
        qDebug() << "No overlapping Car in any travels";
    }
}

void Check::checkBookings()
{
    QString errorMessage;
    if(!checkTravelDisjunct(errorMessage))
    {
        QMessageBox::warning(nullptr, "Booking Error", errorMessage);
    }
}


