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
    for(Booking* booking : bookings)
    {
        delete booking;
    }
    bookings.clear();
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

    int totalFLightBooking = 0;
    int totalHotelBooking = 0;
    int totalRentalCarReservation= 0;
    int totalTrainBooking = 0;

    double totalFlightPrice = 0;
    double totalHotelPrice = 0;
    double totalRentalCarReservationPrice = 0;
    double totalTrainPrice = 0;

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

            if(airline.empty() || fromDestination.empty() || toDestination.empty())
            {
                throw std::runtime_error("Empty flightbooking attribute in line " + std::to_string(lineNumber));
            }

            if(fromDestination.length() > 3 || toDestination.length() > 3)
            {
                throw std::runtime_error("Error in destination. Line: " + std::to_string(lineNumber));
            }

            FlightBooking* flightBooking = new FlightBooking(id, price, fromDate, toDate,
                                                             fromDestination, toDestination,
                                                             airline);
            bookings.push_back(flightBooking);
            //std::cout << flightBooking->showDetails() << std::endl;

            totalFLightBooking++;
            totalFlightPrice += price;
        }else if(type == "RentalCar")
        {
            //Parse Rental car specific Data
            std::string company = obj["company"].toString().toStdString();
            std::string pickupLocation = obj["pickupLocation"].toString().toStdString();
            std::string returnLocation = obj["returnLocation"].toString().toStdString();

            if(company.empty() || pickupLocation.empty() || returnLocation.empty())
            {
                throw std::runtime_error("Empty carbooking attribute in line " +std::to_string(lineNumber));
            }

            RentalCarReservation* car = new RentalCarReservation(id, price, fromDate, toDate,
                                                                 company, pickupLocation,
                                                                 returnLocation);
            bookings.push_back(car);
            //std::cout << car->showDetails() << std::endl;

            totalRentalCarReservation++;
            totalRentalCarReservationPrice += price;
        }else if(type == "Hotel")
        {
            //Parse Hotel specific Data
            std::string hotel = obj["hotel"].toString().toStdString();
            std::string town = obj["town"].toString().toStdString();

            if(hotel.empty() || town.empty())
            {
                throw std::runtime_error(&"Empty hotelbooking attribute in line "[lineNumber]);
            }

            HotelBooking* hotelBooking = new HotelBooking(id, price, fromDate, toDate,
                                     hotel, town);
            bookings.push_back(hotelBooking);
            //std::cout << hotelBooking->showDetails() << std::endl;

            totalHotelBooking++;
            totalHotelPrice += price;
        }else if(type == "Train")
        {
            std::vector<std::string> connectingStations;
            std::string arrivalTime = obj["arrivalTime"].toString().toStdString();
            std::string departureTime = obj["departureTime"].toString().toStdString();
            std::string fromStation = obj["fromStation"].toString().toStdString();
            std::string toStation = obj["toStation"].toString().toStdString();

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
            TrainTicket* train = new TrainTicket(id, price, fromDate, toDate,
                                                 fromStation, toStation, departureTime,
                                                 arrivalTime, connectingStations);
            bookings.push_back(train);
            //std::cout << train->showDetails() << std::endl;

            totalTrainBooking++;
            totalTrainPrice += price;
        }
    }

    std::cout << "Es wurden " <<  totalFLightBooking << " Flugbuchungen im Wert " << totalFlightPrice << " Euro, "
              << totalRentalCarReservation << " Mietwagenbuchungen in Wert von " << totalRentalCarReservationPrice
              << " Euro, " << totalHotelBooking << " Hotelreservierungen im Wert von " << totalHotelPrice << " Euro, "
              << " und " << totalTrainBooking  << " Zugbuchungen im Wert von " << totalTrainPrice << " Euro" << std::endl;


}
