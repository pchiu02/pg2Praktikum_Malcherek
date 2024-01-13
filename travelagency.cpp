#include "travelagency.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"
#include "connectingstation.h"

#include <QDesktopServices>
#include <QUrl>
#include <sstream>

TravelAgency::TravelAgency()
{

}

TravelAgency::~TravelAgency()
{
    // for(Booking* booking : allBooking)
    // {
    //     delete booking;
    // }
    // for(Customer* customer : allCustomer)
    // {
    //     delete customer;
    // }
    // for(Travel* travel : allTravel)
    // {
    //     delete travel;
    // }
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

        std::string customerFirstName = obj["customerFirstName"].toString().toStdString();
        std::string customerLastName = obj["customerLastName"].toString().toStdString();
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
            double fromDestLatitude = obj["fromDestLatitude"].toDouble();
            double fromDestLongitude = obj["fromDestLongitude"].toDouble();
            double toDestLatitude = obj["toDestLatitude"].toDouble();
            double toDestLongitude = obj["toDestLongitude"].toDouble();

            if(airline.empty() || fromDestination.empty() || toDestination.empty())
            {
                throw std::runtime_error("Empty flightbooking attribute in line " + std::to_string(lineNumber));
            }

            if(fromDestination.length() != 3 || toDestination.length() != 3)
            {
                throw std::runtime_error("Error in destination. Line: " + std::to_string(lineNumber));
            }

            std::shared_ptr<FlightBooking> flightBooking = std::make_shared<FlightBooking>(id, price, fromDate, toDate, travelId, customerId, type,
                                                             fromDestination, toDestination,
                                                             airline, bookingClass, fromDestLatitude, fromDestLongitude,
                                                             toDestLatitude, toDestLongitude);
            allBooking.push_back(flightBooking);
            //std::cout << flightBooking->showDetails() << std::endl;

            totalFlightBooking++;
            totalFlightPrice += price;

            std::shared_ptr<Travel> travel = findTravel(travelId);
            if(!travel){
                travel = std::make_shared<Travel>(travelId, customerId);
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
            double pickupLatitude = obj["pickupLatitude"].toDouble();
            double pickupLongitude = obj["pickupLongitude"].toDouble();
            double returnLatitude = obj["returnLatitude"].toDouble();
            double returnLongitude = obj["returnLongitude"].toDouble();

            if(company.empty() || pickupLocation.empty() || returnLocation.empty())
            {
                throw std::runtime_error("Empty carbooking attribute in line " +std::to_string(lineNumber));
            }

            std::shared_ptr<RentalCarReservation> car = std::make_shared<RentalCarReservation>(id, price, fromDate, toDate, travelId, customerId, type,
                                                                pickupLocation,
                                                                returnLocation, company, vehicleClass, pickupLatitude, pickupLongitude,
                                                                returnLatitude, returnLongitude);
            allBooking.push_back(car);
            //std::cout << car->showDetails() << std::endl;

            totalRentalCarReservation++;
            totalRentalCarReservationPrice += price;

            std::shared_ptr<Travel> travel = findTravel(travelId);
            if(!travel){
                travel = std::make_shared<Travel>(travelId, customerId);
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
            double hotelLatitude = obj["hotelLatitude"].toDouble();
            double hotelLongitude = obj["hotelLongitude"].toDouble();

            if(hotel.empty() || town.empty())
            {
                throw std::runtime_error(&"Empty hotelbooking attribute in line "[lineNumber]);
            }

            std::shared_ptr<HotelBooking>hotelBooking = std::make_shared<HotelBooking>(id, price, fromDate, toDate, travelId, customerId, type,
                                     hotel, town, roomType, hotelLatitude, hotelLongitude);
            allBooking.push_back(hotelBooking);
            //std::cout << hotelBooking->showDetails() << std::endl;

            totalHotelBooking++;
            totalHotelPrice += price;

            std::shared_ptr<Travel> travel = findTravel(travelId);
            if(!travel){
                travel = std::make_shared<Travel>(travelId, customerId);
                allTravel.push_back(travel);
            }
            travelCount++;
            travel->addBooking(hotelBooking);
        }else if(type == "Train")
        {
            std::vector<ConnectingStation> connectingStations;
            std::string arrivalTime = obj["arrivalTime"].toString().toStdString();
            std::string departureTime = obj["departureTime"].toString().toStdString();
            std::string fromStation = obj["fromStation"].toString().toStdString();
            std::string toStation = obj["toStation"].toString().toStdString();
            std::string ticketType = obj["ticketType"].toString().toStdString();
            double fromStationLatitude = obj["fromStationLatitude"].toDouble();
            double fromStationLongitude = obj["fromStationLongitude"].toDouble();
            double toStationLatitude = obj["toStationLatitude"].toDouble();
            double toStationLongitude = obj["toStationLongitude"].toDouble();

            if(departureTime.empty() || fromStation.empty() || toStation.empty())
            {
                throw std::runtime_error(&"Empty train ticket attribute " [lineNumber]);
            }

            if(obj.contains("connectingStations") && obj["connectingStations"].isArray())
            {
                QJsonArray stationsArray = obj["connectingStations"].toArray();

                for(const QJsonValue &stationValue : stationsArray)
                {
                    if(stationValue.isObject()){
                        QJsonObject stationObject = stationValue.toObject();
                        if(stationObject.contains("latitude") && stationObject.contains("longitude")){
                            double latitude = stationObject["latitude"].toDouble();
                            double longitude = stationObject["longitude"].toDouble();
                            std::string stationName = stationObject["stationName"].toString().toStdString();

                            ConnectingStation connectingStation = ConnectingStation(stationName, latitude, longitude);
                            connectingStations.push_back(connectingStation);
                        }
                    }
                }
            }
            std::shared_ptr<TrainTicket>train = std::make_shared<TrainTicket>(id, price, fromDate, toDate, travelId, customerId, type,
                                                 fromStation, toStation, departureTime,
                                                 arrivalTime, connectingStations, ticketType,
                                                 fromStationLatitude, fromStationLongitude, toStationLatitude,
                                                 toStationLongitude);
            allBooking.push_back(train);
            //std::cout << train->showDetails() << std::endl;

            totalTrainBooking++;
            totalTrainPrice += price;

            std::shared_ptr<Travel>travel = findTravel(travelId);
            if(!travel){
                travel = std::make_shared<Travel>(travelId, customerId);
                allTravel.push_back(travel);
            }
            travelCount++;
            travel->addBooking(train);
        }
        std::shared_ptr<Customer> customer = findCustomer(customerId, customerFirstName, customerLastName);
        if(!customer){
            customer = std::make_shared<Customer>(customerId, customerFirstName, customerLastName);
            allCustomer.push_back(customer);
            totalCustomer++;
        }

        std::shared_ptr<Travel>travel = findTravel(travelId);
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

void TravelAgency::readIataCode(QString fileName)
{
    allAirport.clear();

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        throw std::invalid_argument("Failed to open IataCodes File");
    }

    //Read the contents of the file into a QString
    QString jsonData = file.readAll();
    //Parse the JSON Data
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData.toUtf8());

    //Checking if the JSON Document is an array
    if(!jsonDoc.isArray()){
        throw std::invalid_argument("Invalid JSON File");
    }

    QJsonArray airportsArray = jsonDoc.array();
    for(int i = 0; i < airportsArray.size(); i++)
    {
        if(!airportsArray[i].isObject()){
            throw std::invalid_argument("Invalid Airport in JSON File at object" + std::to_string (i + 1));
        }
        QJsonObject airportObject = airportsArray[i].toObject();

        std::string name = airportObject["name"].toString().toStdString();
        std::string isoCountry = airportObject["iso_country"].toString().toStdString();
        std::string municipality = airportObject["municipality"].toString().toStdString();
        std::string iataCode = airportObject["iata_code"].toString().toStdString();

        // make an airport object
        if(!iataCode.empty())
        {
            std::shared_ptr<Airport> airport = std::make_shared<Airport>(name, isoCountry, municipality,
                                                                         iataCode);
            allAirport[iataCode] = airport;
        }
    }
    std::cout << "Airport size: " << allAirport.size() << endl;
}

QString TravelAgency::getBookingsInfo()
{
    int totalTravels = allTravel.size();
    int totalCustomers = allCustomer.size();
    string firstName = " ";
    string lastName = " ";
    std::shared_ptr<Customer> customerId1 = findCustomer(1, firstName, lastName);
    std::shared_ptr<Travel> travelId17 = findTravel(17);

    std::ostringstream oss;

    oss << "Es wurden " << totalFlightBooking << " Flugreservierungen, " << totalHotelBooking << " Hotelbuchungen und " << totalRentalCarReservation
        << " Mietwagenreservierungen im Gesamtwert von " << (totalFlightPrice + totalRentalCarReservationPrice + totalHotelPrice) << " eingelesen. "
        << "Es wurden " << totalTravels << " Reisen und " << totalCustomers << " Kunden angelegt. "
        << "Der Kunde mit der ID 1 hat " << customerId1->getTravelCount() << " Reisen gebucht. "
        << "Zur Reise mit der ID 17 gehören " << travelId17->getBookingCount() << " Buchungen.";

            return QString::fromStdString(oss.str());
}

std::shared_ptr<Booking> TravelAgency::findBooking(std::string id)
{
    for(std::shared_ptr<Booking> booking : allBooking)
    {
        if(booking->getId() == id)
        {
            return booking;
        }
    }

    return nullptr;
}

std::shared_ptr<Travel> TravelAgency::findTravel(long id)
{
    //check if the travel with the given Id already exist
    for(std::shared_ptr<Travel>travel : allTravel)
    {
        if(travel->getId() == id)
        {
            return travel;
        }
    }
    return nullptr;
}

std::shared_ptr<Customer> TravelAgency::findCustomer(long id, string &firstName, string &lastName)
{
    for (std::shared_ptr<Customer> customer : allCustomer)
    {
        if (customer->getId() == id)
        {
            // Customer with the given ID already exists, so return it.
            return customer;
        }
    }

           // If no matching customer is found, create a new one
    std::shared_ptr<Customer> newCustomer = std::make_shared<Customer>(id, firstName, lastName);
    allCustomer.push_back(newCustomer);
    return newCustomer;
}

string TravelAgency::generatePointGeoJson(double latitude, double longitude, std::string labels)
{
    std::ostringstream ss;
    ss << "{\"type\":\"Point\",\"coordinates\":[" << longitude << "," << latitude << "]}"
       << "\"properties\":{\"name\":\"" << labels << "\"}}";
    return ss.str();
}

string TravelAgency::generateLineStringGeoJson(const std::vector<std::pair<double, double> > &coordinates, std::vector<std::string>& labels)
{
    std::ostringstream ss;

    ss << "{\"type\":\"FeatureCollection\",\"features\":[";

    ss << "{\"type\":\"Feature\",\"geometry\":{\"type\":\"LineString\",\"coordinates\":[";
    for (size_t i = 0; i < coordinates.size(); ++i) {
        ss << "[" << coordinates[i].second << "," << coordinates[i].first << "]";
        if (i < coordinates.size() - 1) ss << ",";
    }
    ss << "]}},";

    // Add Point features with labels
    for (size_t i = 0; i < coordinates.size() && i < labels.size(); ++i) {
        ss << "{\"type\":\"Feature\",\"geometry\":{\"type\":\"Point\",\"coordinates\":["
           << coordinates[i].second << "," << coordinates[i].first << "]},"
           << "\"properties\":{\"name\":\"" << labels[i] << "\"}}";
        if (i < coordinates.size() - 1 && i < labels.size() - 1) ss << ",";
    }

    ss << "]}";
    return ss.str();
}

void TravelAgency::displayOnBookingMap(const std::shared_ptr<Travel> &travel)
{
    for(const auto& booking : travel->getTravelBookings())
    {
        std::string geoJson;
        if(std::shared_ptr<FlightBooking> flightBooking = std::dynamic_pointer_cast<FlightBooking>(booking))
        {
            std::vector<std::pair<double, double>> coords = {
                {flightBooking->getFromDestLatitude(), flightBooking->getFromDestLongitude()},
                {flightBooking->getToDestLatitude(), flightBooking->getToDestLongitude()}
            };

            std::vector<std::string> labels = {flightBooking->getFromDestination(), flightBooking->getToDestination()};
            geoJson = generateLineStringGeoJson(coords, labels);
        }else if(std::shared_ptr<HotelBooking> hotelBooking = std::dynamic_pointer_cast<HotelBooking>(booking))
        {
            geoJson = generatePointGeoJson(hotelBooking->getHotelLatitude(), hotelBooking->getHotelLongitude(), hotelBooking->getHotel());
        }else if(std::shared_ptr<RentalCarReservation> car = std::dynamic_pointer_cast<RentalCarReservation>(booking))
        {
            if(car->getPickupLatitude() != car->getReturnLatitude() ||
                car->getPickupLongitude() != car->getReturnLongitude()){
                std::vector<std::pair<double, double>> coords ={
                    {car->getPickupLatitude(), car->getPickupLongitude()},
                    {car->getReturnLatitude(), car->getReturnLongitude()}
                };

                std::vector<std::string> labels = {car->getPickupLocation(), car->getReturnLocation()};
                geoJson = generateLineStringGeoJson(coords, labels);
            }else{
                geoJson = generatePointGeoJson(car->getPickupLatitude(), car->getPickupLongitude(), car->getPickupLocation());
            }
        }else if (std::shared_ptr<TrainTicket> train = std::dynamic_pointer_cast<TrainTicket>(booking))
        {
            std::vector<std::pair<double, double>> coords = train->getAllStationCoordinates();
            std::vector<std::string> labels = {train->getFromDestination(), train->getToDestination()};
            geoJson = generateLineStringGeoJson(coords, labels);
        }

        if(!geoJson.empty()){
            QString QGeoJson = QString::fromStdString(geoJson);
            QString url = "http://townsendjennings.com/geo/?geojson=" + QUrl::toPercentEncoding(QGeoJson);

            QDesktopServices::openUrl(QUrl(url));
        }
    }
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

const std::vector<std::shared_ptr<Booking>> &TravelAgency::getAllBooking() const
{
    return allBooking;
}

const std::vector<std::shared_ptr<Customer> > &TravelAgency::getAllCustomer() const
{
    return allCustomer;
}

const std::vector<std::shared_ptr<Travel> > &TravelAgency::getAllTravel() const
{
    return allTravel;
}

std::map<std::string, shared_ptr<Airport> > TravelAgency::getAllAirport() const
{
    return allAirport;
}

std::shared_ptr<Airport> TravelAgency::getAirport(const string &iataCode)
{
    auto it = allAirport.find(iataCode);
    if(it != allAirport.end())
    {
        return it->second;
    }else
    {
        return nullptr;
    }
}

bool TravelAgency::hasAirport(const string &iataCode) const
{
    auto it = allAirport.find(iataCode);
    return it != allAirport.end();
}
