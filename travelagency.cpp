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

void TravelAgency::readFile()
{
    QFile file("bookings.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning("Failed to open File");
        return;
    }

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

void TravelAgency::readBinaryFile()
{
    int totalFlightBooking = 0, totalHotelBooking = 0, totalCarBooking = 0, totalTrainBooking = 0;
    double totalFlightPrice = 0, totalHotelPrice = 0, totalCarPrice = 0, totalTrainPrice = 0;
    std::ifstream inputFile("bookingsBinary.bin", std::ios::binary);
    if(inputFile.is_open())
    {
        char bookingType;
        while(inputFile.read(&bookingType, sizeof(bookingType)))
        {
            char id[39];
            double price;
            char fromDate[9];
            char toDate[9];

            inputFile.read(id, sizeof(id) -1);
            inputFile.read(reinterpret_cast<char*>(&price), sizeof(price));
            inputFile.read(fromDate, sizeof(fromDate)-1);
            inputFile.read(toDate, sizeof(toDate)-1);

            id[38] = '\0';
            fromDate[8] = '\0';
            toDate[8] = '\0';

            std::string idStr(id);
            std::string fromDateStr(fromDate);
            std::string toDateStr(toDate);

            if(bookingType == 'F')
            {
                char fromDestination[4];
                char toDestination[4];
                char airline[16];

                inputFile.read(fromDestination, sizeof(fromDestination)-1);
                inputFile.read(toDestination, sizeof(toDestination)-1);
                inputFile.read(airline, sizeof(airline)-1);

                fromDestination[3] = '\0';
                toDestination[3] = '\0';
                airline[15] = '\0';

                std::string fromDestinationStr(fromDestination);
                std::string toDestinationStr(toDestination);
                std::string airlineStr(airline);

                FlightBooking* flightBooking = new FlightBooking(idStr, price, fromDateStr,
                                                                  toDateStr, fromDestinationStr, toDestinationStr,
                                                                 airlineStr);
                bookings.push_back(flightBooking);
                std::cout << flightBooking->showDetails() << std::endl;
                totalFlightBooking++;
                totalFlightPrice += price;
            }
            else if(bookingType == 'R')
            {
                char pickupLocation[16];
                char returnLocation[16];
                char company[16];

                inputFile.read(pickupLocation, sizeof(pickupLocation) - 1);
                inputFile.read(returnLocation, sizeof(returnLocation) -1);
                inputFile.read(company, sizeof(company) -1);

                pickupLocation[15] = '\0';
                returnLocation[15] = '\0';
                company[15] = '\0';

                std::string pickupLocationStr(pickupLocation);
                std::string returnLocationStr(returnLocation);
                std::string companyStr(company);

                RentalCarReservation* car = new RentalCarReservation(idStr, price, fromDateStr,
                                                                     toDateStr, pickupLocationStr, returnLocationStr,
                                                                     companyStr);
                bookings.push_back(car);
                std::cout << car->showDetails() << std::endl;
                totalCarBooking++;
                totalCarPrice += price;
            }
            else if(bookingType == 'H')
            {
                char hotel[16];
                char town[16];

                inputFile.read(hotel, sizeof(hotel)-1);
                inputFile.read(town, sizeof(town)-1);

                hotel[15] = '\0';
                town[15] = '\0';

                std::string hotelStr(hotel);
                std::string townStr(town);

                HotelBooking* hotelBooking = new HotelBooking(idStr, price, fromDateStr, toDateStr,
                                         hotelStr, townStr);
                bookings.push_back(hotelBooking);
                std::cout << hotelBooking->showDetails() << std::endl;
                totalHotelBooking++;
                totalHotelPrice += price;
            }
            else if(bookingType == 'T')
            {
                char fromDestination[16];
                char toDestination[16];
                char departureTime[6];
                char arrivalTime[6];
                char connectingStationsName[16];
                int numConnectingStations = 0;

                inputFile.read(fromDestination, sizeof(fromDestination)-1);
                inputFile.read(toDestination, sizeof(toDestination)-1);
                inputFile.read(departureTime, sizeof(departureTime)-1);
                inputFile.read(arrivalTime, sizeof(arrivalTime)-1);
                inputFile.read(reinterpret_cast<char*>(&numConnectingStations), sizeof(int));

                fromDestination[15] = '\0';
                toDestination[15] = '\0';
                departureTime[5] = '\0';
                arrivalTime[5] = '\0';
                connectingStationsName[15] = '\0';

                std::vector<std::string> connectingStations;
                for(int i = 0; i < numConnectingStations; i++) {
//                    inputFile.read(reinterpret_cast<char*>(&connectingStationsName), sizeof(connectingStationsName)-1);
//                    connectingStations.push_back(connectingStationsName);
                    inputFile.read(connectingStationsName, 15);
                    connectingStations.push_back(std::string(connectingStationsName));
                }

                std::string fromDestinationStr(fromDestination);
                std::string toDestinationStr(toDestination);
                std::string departureTimeStr(departureTime);
                std::string arrivalTimeStr(arrivalTime);

                TrainTicket* train = new TrainTicket(idStr, price, fromDateStr, toDateStr,
                                                     fromDestinationStr, toDestinationStr,
                                                     departureTimeStr, arrivalTime, connectingStations);
                bookings.push_back(train);
                std::cout << train->showDetails() << std::endl;
                totalTrainBooking++;
                totalTrainPrice += price;
            }
            else {
                std::cout << "Unindenified Booking Type" << std::endl;
            }
        }
        std::cout << "Es wurden " <<  totalFlightBooking << " Flugbuchungen im Wert " << totalFlightPrice << " Euro, "
                  << totalCarBooking << " Mietwagenbuchungen in Wert von " << totalCarPrice
                  << " Euro, " << totalHotelBooking << " Hotelreservierungen im Wert von " << totalHotelPrice << " Euro, "
                  << " und " << totalTrainBooking  << " Zugbuchungen im Wert von " << totalTrainPrice << " Euro" << std::endl;
    }
}
