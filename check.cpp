#include "check.h"

Check::Check(std::shared_ptr<TravelAgency> agency) : travelAgency(std::move(agency))
{

}

bool Check::checkTravelDisjunct(QString &message){

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

                    message = QString("Overlapping trips found for customer %1.").arg(QString::fromStdString(fullName));
                    return false;
                }
            }
        }
    }
    return true;
}
