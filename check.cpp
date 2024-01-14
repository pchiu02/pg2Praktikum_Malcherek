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
                    return false;
                }
            }
        }
    }
    std::cout << "Check called" << std::endl;
    return true;
}

void Check::operator ()()
{
    QString errorMessage;
    if (!checkTravelDisjunct(errorMessage)) {  // Using Check as a functor
        QMessageBox::warning(nullptr, "Booking Error", errorMessage);
    }
}
