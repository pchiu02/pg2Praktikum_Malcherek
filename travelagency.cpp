#include "travelagency.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"

TravelAgency::TravelAgency()
{

}

TravelAgency::~TravelAgency()
{
    for(Booking* booking : allBooking)
    {
        delete booking;
    }
    for(Customer* customer : allCustomer)
    {
        delete customer;
    }
    for(Travel* travel : allTravel)
    {
        delete travel;
    }
    allBooking.clear();
    allTravel.clear();
    allCustomer.clear();
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

        std::string customerFirstName = obj["customerFirstname"].toString().toStdString();
        std::string customerLastName = obj["customerLastname"].toString().toStdString();
        int customerId = obj["customerId"].toInt();
        int travelId = obj["travelId"].toInt();

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

             FlightBooking* flightBooking = new FlightBooking(id, price, fromDate, toDate, travelId, type,
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

            RentalCarReservation* car = new RentalCarReservation(id, price, fromDate, toDate, travelId, type,
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

            HotelBooking* hotelBooking = new HotelBooking(id, price, fromDate, toDate, travelId, type,
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
            TrainTicket* train = new TrainTicket(id, price, fromDate, toDate, travelId, type,
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
            totalCustomer++;
        }

        Travel* travel = findTravel(travelId);
        if(travel && !customer->hasTravel(travel))
        {
            customer->addTravel(travel);
        }
    }

    std::cout << "Es wurden " <<  totalFlightBooking << " Flugbuchungen im Wert " << totalFlightPrice << " Euro, "
              << totalRentalCarReservation << " Mietwagenbuchungen in Wert von " << totalRentalCarReservationPrice
              << " Euro, " << totalHotelBooking << " Hotelreservierungen im Wert von " << totalHotelPrice << " Euro, "
              << " und " << totalTrainBooking  << " Zugbuchungen im Wert von " << totalTrainPrice << " Euro" << std::endl;

    std::cout << "Es wurden " << allCustomer.size() << " Kunden und " << allTravel.size() << " Reisen angelegt." << std::endl;
    file.close();


}

QString TravelAgency::getBookingsInfo()
{
    int totalTravels = allTravel.size();
    int totalCustomers = allCustomer.size();
    string firstName = " ";
    string lastName = " ";
    Customer* customerId1 = findCustomer(1, firstName, lastName);
    Travel* travelId17 = findTravel(17);

    std::ostringstream oss;

    oss << "Es wurden " << totalFlightBooking << " Flugreservierungen, " << totalHotelBooking << " Hotelbuchungen und " << totalRentalCarReservation
        << " Mietwagenreservierungen im Gesamtwert von " << (totalFlightPrice + totalRentalCarReservationPrice + totalHotelPrice) << " eingelesen. "
        << "Es wurden " << totalTravels << " Reisen und " << totalCustomers << " Kunden angelegt. "
        << "Der Kunde mit der ID 1 hat " << customerId1->getTravelCount() << " Reisen gebucht. "
        << "Zur Reise mit der ID 17 gehören " << travelId17->getBookingCount() << " Buchungen.";

            return QString::fromStdString(oss.str());
}

Booking *TravelAgency::findBooking(std::string id)
{
    for(Booking* booking : allBooking)
    {
        if(booking->getId() == id)
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

Customer* TravelAgency::findCustomer(long id, string &firstName, string &lastName)
{
    for (Customer* customer : allCustomer)
    {
        if (customer->getId() == id)
        {
            // Customer with the given ID already exists, so return it.
            return customer;
        }
    }

           // If no matching customer is found, create a new one
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

const std::vector<Customer *> &TravelAgency::getAllCustomer() const
{
    return allCustomer;
}

const std::vector<Travel *> &TravelAgency::getAllTravel() const
{
    return allTravel;
}
