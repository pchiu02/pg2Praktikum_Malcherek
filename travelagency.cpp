#include "travelagency.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"

TravelAgency::TravelAgency()
    : totalFlightBooking(0), totalHotelBooking(0), totalRentalCarReservation(0), totalTrainBooking(0),
      totalFlightPrice(0), totalHotelPrice(0), totalRentalCarReservationPrice(0), totalTrainPrice(0)
{

}

TravelAgency::~TravelAgency()
{
    for(Booking* booking : allBooking)
    {
        delete booking;
    }
    allBooking.clear();
}

void TravelAgency::readFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning("Failed to open File");
        return;
    }

    qDebug() <<"File open succesfully";

    //Read the contents of the file into a QByteArray
    QByteArray jsonData = file.readAll();


    //Parse the JSON data
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if(jsonDoc.isNull())
    {
        qWarning("Failed to parse Json");
        return;
    }

    if(!jsonDoc.isArray())
    {
        qWarning("JSON is not an array");
        return;
    }

    QJsonArray jsonArray = jsonDoc.array();

    file.close();

    int lineNumber = 0;

    for(const QJsonValue &value : jsonArray)
    {
        lineNumber++;
        QJsonObject obj = value.toObject();
        std::string type = obj["type"].toString().toStdString();

        std::string id = obj["id"].toString().toStdString();
        std::string fromDate = obj["fromDate"].toString().toStdString();
        std::string toDate = obj["toDate"].toString().toStdString();
        double price = obj["price"].toDouble();

        std::string customerFirstName = obj["customerFirstName"].toString().toStdString();
        std::string customerLastName = obj["customerLastName"].toString().toStdString();
        long customerId = obj["customerId"].toString().toLong();
        long travelId = obj["travelId"].toString().toLong();

        if(id.empty() || fromDate.empty() || toDate.empty() || obj["price"].isNull())
        {
            throw std::runtime_error("Empty Attribut in " + std::to_string(lineNumber));
        }

        if (!obj["price"].isDouble())
        {
            throw std::runtime_error("Price is not a number. Line: " + std::to_string(lineNumber));
        }

        if (type == "Flight")
        {
            //Parse Flight specific Data
            std::string airline = obj["airline"].toString().toStdString();
            std::string fromDestination = obj["fromDest"].toString().toStdString();
            std::string toDestination = obj["toDest"].toString().toStdString();
            std::string bookingClass = obj["bookingClass"].toString().toStdString();

            if(airline.empty() || fromDestination.empty() || toDestination.empty())
            {
                throw std::runtime_error("Empty flightbooking attribute in line " + std::to_string(lineNumber));
            }

            if(fromDestination.length() != 3 || toDestination.length() != 3)
            {
                throw std::runtime_error("Error in destination. Line: " + std::to_string(lineNumber));
            }

             FlightBooking* flightBooking = new FlightBooking(id, price, fromDate, toDate, travelId,
                                                             fromDestination, toDestination,
                                                             airline, bookingClass);
            allBooking.push_back(flightBooking);
            //std::cout << flightBooking->showDetails() << std::endl;

            totalFlightBooking++;
            totalFlightPrice += price;

            Travel* travel = findTravel(travelId);
            if(!travel){
                travel = new Travel(travelId, customerId);
                allTravel.push_back(travel);
            }
            travelCount++;
            travel->addBooking(flightBooking);

        }else if(type == "RentalCar")
        {
            //Parse Rental car specific Data
            std::string company = obj["company"].toString().toStdString();
            std::string pickupLocation = obj["pickupLocation"].toString().toStdString();
            std::string returnLocation = obj["returnLocation"].toString().toStdString();
            std::string vehicleClass = obj["vehicleClass"].toString().toStdString();

            if(company.empty() || pickupLocation.empty() || returnLocation.empty())
            {
                throw std::runtime_error("Empty carbooking attribute in line " +std::to_string(lineNumber));
            }

            RentalCarReservation* car = new RentalCarReservation(id, price, fromDate, toDate, travelId,
                                                                 company, pickupLocation,
                                                                 returnLocation, vehicleClass);
            allBooking.push_back(car);
            //std::cout << car->showDetails() << std::endl;

            totalRentalCarReservation++;
            totalRentalCarReservationPrice += price;

            Travel* travel = findTravel(travelId);
            if(!travel){
                travel = new Travel(travelId, customerId);
                allTravel.push_back(travel);
            }
            travelCount++;
            travel->addBooking(car);
        }else if(type == "Hotel")
        {
            //Parse Hotel specific Data
            std::string hotel = obj["hotel"].toString().toStdString();
            std::string town = obj["town"].toString().toStdString();
            std::string roomType = obj["roomType"].toString().toStdString();

            if(hotel.empty() || town.empty())
            {
                throw std::runtime_error(&"Empty hotelbooking attribute in line "[lineNumber]);
            }

            HotelBooking* hotelBooking = new HotelBooking(id, price, fromDate, toDate, travelId,
                                     hotel, town, roomType);
            allBooking.push_back(hotelBooking);
            //std::cout << hotelBooking->showDetails() << std::endl;

            totalHotelBooking++;
            totalHotelPrice += price;

            Travel* travel = findTravel(travelId);
            if(!travel){
                travel = new Travel(travelId, customerId);
                allTravel.push_back(travel);
            }
            travelCount++;
            travel->addBooking(hotelBooking);
        }else if(type == "Train")
        {
            std::vector<std::string> connectingStations;
            std::string arrivalTime = obj["arrivalTime"].toString().toStdString();
            std::string departureTime = obj["departureTime"].toString().toStdString();
            std::string fromStation = obj["fromStation"].toString().toStdString();
            std::string toStation = obj["toStation"].toString().toStdString();
            std::string ticketType = obj["ticketType"].toString().toStdString();

            if(departureTime.empty() || fromStation.empty() || toStation.empty())
            {
                throw std::runtime_error(&"Empty train ticket attribute " [lineNumber]);
            }

            if(obj.contains("connectingStations") && obj["connectingStations"].isArray())
            {
                QJsonArray stationsArray = obj["connectingStations"].toArray();

                for(const QJsonValue &stationValue : stationsArray)
                {
                    connectingStations.push_back(stationValue.toString().toStdString());
                }
            }
            TrainTicket* train = new TrainTicket(id, price, fromDate, toDate, travelId,
                                                 fromStation, toStation, departureTime,
                                                 arrivalTime, connectingStations, ticketType);
            allBooking.push_back(train);
            //std::cout << train->showDetails() << std::endl;

            totalTrainBooking++;
            totalTrainPrice += price;

            Travel* travel = findTravel(travelId);
            if(!travel){
                travel = new Travel(travelId, customerId);
                allTravel.push_back(travel);
            }
            travelCount++;
            travel->addBooking(train);
        }
        Customer* customer = findCustomer(customerId, customerFirstName, customerLastName);
        if(!customer){
            customer = new Customer(customerId, customerFirstName, customerLastName);
            allCustomer.push_back(customer);
        }

        Travel* travel = findTravel(travelId);
        if(travel && !customer->hasTravel(travel))
        {
            customer->addTravel(travel);
        }
        file.close();
    }

    std::cout << "Es wurden " <<  totalFlightBooking << " Flugbuchungen im Wert " << totalFlightPrice << " Euro, "
              << totalRentalCarReservation << " Mietwagenbuchungen in Wert von " << totalRentalCarReservationPrice
              << " Euro, " << totalHotelBooking << " Hotelreservierungen im Wert von " << totalHotelPrice << " Euro, "
              << " und " << totalTrainBooking  << " Zugbuchungen im Wert von " << totalTrainPrice << " Euro" << std::endl;


}

Booking *TravelAgency::findBooking(long id)
{
    for(Booking* booking : allBooking)
    {
        if(booking->getTravelId() == id)
        {
            return booking;
        }
    }

    return nullptr;
}

Travel *TravelAgency::findTravel(long id)
{
    //check if the travel with the given Id already exist
    for(Travel* travel : allTravel)
    {
        if(travel->getId() == id)
        {
            return travel;
        }
    }
    return nullptr;
}

Customer *TravelAgency::findCustomer(long id, string firstName, string lastName)
{
    for(Customer *customer : allCustomer)
    {
        if(customer->getId() == id)
        {
            return customer;
        }
    }
    Customer* newCustomer = new Customer(id, firstName, lastName);
    allCustomer.push_back(newCustomer);
    return newCustomer;
}

int TravelAgency::getTotalFlightBooking() const
{
    return totalFlightBooking;
}

int TravelAgency::getTotalHotelBooking() const
{
    return totalHotelBooking;
}

int TravelAgency::getTotalRentalCarReservation() const
{
    return totalRentalCarReservation;
}

int TravelAgency::getTotalTrainBooking() const
{
    return totalTrainBooking;
}

double TravelAgency::getTotalFlightPrice() const
{
    return totalFlightPrice;
}

double TravelAgency::getTotalHotelPrice() const
{
    return totalHotelPrice;
}

double TravelAgency::getTotalRentalCarReservationPrice() const
{
    return totalRentalCarReservationPrice;
}

double TravelAgency::getTotalTrainPrice() const
{
    return totalTrainPrice;
}

const std::vector<Booking *> &TravelAgency::getAllBooking() const
{
    return allBooking;
}
