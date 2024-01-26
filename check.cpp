#include "check.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"

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

void Check::checkNoMissingHotels() {
    QString errorType = "Missing Hotel";
    QString message;

    for (const auto& travel : travelAgency->getAllTravel()) {
        std::vector<VertexData> data;
        travel->sortGraph(data); // Sorts bookings by their topological order

        // Initialize lastToDate as an empty string
        QString lastToDate;

        for (const VertexData& vertex : data) {
            auto currentBooking = vertex.booking;

            // Only consider hotel bookings for gaps
            if (std::dynamic_pointer_cast<HotelBooking>(currentBooking)) {
                QString currentFromDate = QString::fromStdString(currentBooking->getFromDate());

                // If lastToDate is not empty and currentFromDate is not the same day, we have a gap
                if (!lastToDate.isEmpty() && lastToDate != currentFromDate) {
                    message = "Gap found in travelID " + QString::number(travel->getId())
                               + " between bookings ending on " + lastToDate
                               + " and starting on " + currentFromDate + ".\n";
                    // Emit the message for this specific gap
                    emit sendCheckResult(errorType, message);
                }

                // Update lastToDate to the current booking's toDate
                lastToDate = QString::fromStdString(currentBooking->getToDate());
            }
        }
    }

    if (!message.isEmpty()) {
        qDebug() << message;
    } else {
        qDebug() << "No missing hotel bookings in any travels.";
    }
}


void Check::checkNoOverlappingHotels() {
    QString errorType = "Overlapping Hotel";
    QString message;

    for (const auto& travel : travelAgency->getAllTravel()) {
        std::vector<VertexData> data;
        travel->sortGraph(data); // Sorts bookings by their topological order

        for (size_t i = 0; i < data.size() - 1; ++i) {
            auto currentBooking = data[i].booking;
            auto nextBooking = data[i + 1].booking;

            // Only consider hotel bookings for overlaps
            if (std::dynamic_pointer_cast<HotelBooking>(currentBooking) && std::dynamic_pointer_cast<HotelBooking>(nextBooking)) {
                QDate toDateCurrent = QDate::fromString(QString::fromStdString(currentBooking->getToDate()), "yyyyMMdd");
                QDate fromDateNext = QDate::fromString(QString::fromStdString(nextBooking->getFromDate()), "yyyyMMdd");

                // If the toDate of the current booking is after the fromDate of the next, we have an overlap
                if (toDateCurrent > fromDateNext) {
                    message = "Overlap found in travelID " + QString::number(travel->getId())
                               + " between hotel bookings ending on " + toDateCurrent.toString("yyyyMMdd")
                               + " and starting on " + fromDateNext.toString("yyyyMMdd") + ".\n";
                    // Emit the message for this specific overlap
                    emit sendCheckResult(errorType, message);
                }
            }
        }
    }

    if (!message.isEmpty()) {
        qDebug() << message;
    } else {
        qDebug() << "No overlapping hotel bookings in any travels.";
    }
}

void Check::checkNoOverlappingRentalCars() {
    QString errorType = "Overlapping Cars";
    QString message;

    for (const auto& travel : travelAgency->getAllTravel()) {
        std::vector<VertexData> data;
        travel->sortGraph(data); // Assuming this method sorts the bookings and fills 'data'

        std::shared_ptr<Booking> lastCarBooking = nullptr;

        for (const VertexData& vertex : data) {
            auto currentBooking = vertex.booking;

            // Only consider rental car bookings for overlap
            if (std::dynamic_pointer_cast<RentalCarReservation>(currentBooking)) {
                if (lastCarBooking) {
                    QDate toDateLast = QDate::fromString(QString::fromStdString(lastCarBooking->getToDate()), "yyyyMMdd");
                    QDate fromDateCurrent = QDate::fromString(QString::fromStdString(currentBooking->getFromDate()), "yyyyMMdd");

                    // If the end date of the last car booking is later than the start date of the current, it's an overlap
                    if (toDateLast > fromDateCurrent) {
                        message = "Overlap found in travelID " + QString::number(travel->getId())
                                   + " between car rental bookings ending on " + toDateLast.toString("yyyyMMdd")
                                   + " and starting on " + fromDateCurrent.toString("yyyyMMdd") + ".\n";
                        // Emit the message for this specific overlap
                        emit sendCheckResult(errorType, message);
                        break; // Since we found an overlap, we break out of the loop
                    }
                }
                lastCarBooking = currentBooking; // Update the last car booking
            }
        }
    }

    if (!message.isEmpty()) {
        qDebug() << message;
    } else {
        qDebug() << "No overlapping car rentals in any travels.";
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


