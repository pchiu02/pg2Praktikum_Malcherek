#include "buchungsdetails.h"
#include "qstringlistmodel.h"
#include "ui_buchungsdetails.h"
#include "booking.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"
#include "connectingstation.h"

#include <QIcon>

BuchungsDetails::BuchungsDetails(TravelAgency* travelAgency, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuchungsDetails), travelAgency(travelAgency)
{
    ui->setupUi(this);

    ui->speichern->setEnabled(false);
    ui->abbrechen->setEnabled(false);

    ui->Id->setReadOnly(true);
}

BuchungsDetails::~BuchungsDetails()
{
    delete ui;
}

void BuchungsDetails::setBookingDetails(QString QSrow, QString reiseId)
{
    int row = QSrow.toInt();
    long travelId = reiseId.toInt();
    Travel* travel = travelAgency->findTravel(travelId);

    ui->Id->setEnabled(true);
    ui->fromDate->setEnabled(true);
    ui->toDate->setEnabled(true);
    ui->preis->setEnabled(true);

    ui->speichern->setEnabled(true);
    ui->abbrechen->setEnabled(true);

     // Check if 'travel' is valid before accessing its data
     if (travel) {
        const std::vector<Booking*>& bookings = travel->getTravelBookings();

        // Check if 'row' is within a valid range
        if (row >= 0 && row < static_cast<int>(bookings.size())) {
            Booking* booking = bookings[row];

            // Check if 'booking' is valid before accessing its data
            if (booking) {
                std::string buchungsID = booking->getId();
                std::string fromDateStr = booking->getFromDate();
                std::string toDateStr = booking->getToDate();
                double preis = booking->getPrice();

                ui->preis->setDecimals(2);
                ui->preis->setSingleStep(0.01);
                ui->preis->setRange(0.0, std::numeric_limits<double>::max());
                ui->preis->setPrefix("€");
                ui->preis->setValue(preis);
                ui->Id->setText(QString::fromStdString(buchungsID));
                ui->fromDate->setDate(QDate::fromString(QString::fromStdString(fromDateStr), "yyyyMMdd"));
                ui->toDate->setDate(QDate::fromString(QString::fromStdString(toDateStr), "yyyyMMdd"));

                if(FlightBooking* flightBooking = dynamic_cast<FlightBooking*>(booking))
                {
                    ui->buchungWidget->setCurrentWidget(ui->flugTab);
                    ui->flugAirline->setText(QString::fromStdString(flightBooking->getAirline()));
                    string bookingClass;
                    if(flightBooking->getBookingClass() == "Y"){
                        bookingClass = "Economy";
                    }else if(flightBooking->getBookingClass() == "W"){
                        bookingClass = "Premium Economy";
                    }else if(flightBooking->getBookingClass() == "J"){
                        bookingClass = "Business";
                    }else if(flightBooking->getBookingClass() == "F"){
                        bookingClass = "First";
                    }else{
                        bookingClass = "Undefined";
                    }
                    ui->flugBookingClass->setText(QString::fromStdString(bookingClass));

                    std::string fromIataCode = flightBooking->getFromDestination();
                    std::string toIataCode = flightBooking->getToDestination();

                    std::shared_ptr<Airport> fromAirport = travelAgency->getAirport(fromIataCode);
                    std::shared_ptr<Airport> toAirport = travelAgency->getAirport(toIataCode);

                    ui->flugFromDest->setText(QString::fromStdString(fromAirport->getName()));
                    ui->flugFromDest->setReadOnly(true);
                    ui->flugToDest->setText(QString::fromStdString(toAirport->getName()));
                    ui->flugToDest->setReadOnly(true);
                    ui->toDestCode->setText(QString::fromStdString(flightBooking->getToDestination()));
                    ui->fromDestCode->setText(QString::fromStdString(flightBooking->getFromDestination()));

                } else if(HotelBooking* hotelBooking = dynamic_cast<HotelBooking*>(booking)){

                    ui->buchungWidget->setCurrentWidget(ui->hotelTab);
                    ui->hotelName->setText(QString::fromStdString(hotelBooking->getHotel()));
                    ui->townName->setText(QString::fromStdString(hotelBooking->getTown()));
                    std::string roomType;
                    if(hotelBooking->getRoomType() == "EZ"){
                        roomType = "Einzelzimmer";
                    }else if(hotelBooking->getRoomType() == "DZ"){
                        roomType = "Doppelzimmer";
                    }else if(hotelBooking->getRoomType() == "SU"){
                        roomType = "Suite";
                    }else if(hotelBooking->getRoomType() == "AP"){
                        roomType = "Appartment";
                    }else{
                        roomType = "Undefined";
                    }

                    ui->hotelRoomType->setText(QString::fromStdString(roomType));

                } else if(RentalCarReservation* carBooking = dynamic_cast<RentalCarReservation*>(booking)){

                    ui->buchungWidget->setCurrentWidget(ui->mietwagenTab);

                    ui->mietwagenPickupLocation->setText(QString::fromStdString(carBooking->getPickupLocation()));
                    ui->mietwagenReturnLocation->setText(QString::fromStdString(carBooking->getReturnLocation()));
                    ui->mietwagenCompany->setText(QString::fromStdString(carBooking->getCompany()));
                    ui->mietwagenVehicleClass->setText(QString::fromStdString(carBooking->getVehicleClass()));

                } else if(TrainTicket* trainTicket = dynamic_cast<TrainTicket*>(booking)){

                    ui->buchungWidget->setCurrentWidget(ui->zugTab);

                    ui->trainFromDest->setText(QString::fromStdString(trainTicket->getFromDestination()));
                    ui->trainToDest->setText(QString::fromStdString(trainTicket->getToDestination()));
                    ui->trainTimeAbfahrt->setTime(QTime::fromString(QString::fromStdString(trainTicket->getDepartureTime()), "hh:mm"));
                    ui->trainTimeAnkunft->setTime(QTime::fromString(QString::fromStdString(trainTicket->getDepartureTime()), "hh:mm"));
                    string trainTicketType;
                    if(trainTicket->getTicketType() == "SSP1"){
                        trainTicketType = "Supersparpreis 1. Klasse";
                    }else if(trainTicket->getTicketType() == "SSP2"){
                        trainTicketType = "Supersparpreis 2. Klasse";
                    }else if(trainTicket->getTicketType() == "SP1"){
                        trainTicketType = "Sparpreis 1. Klasse";
                    }else if(trainTicket->getTicketType() == "SP2"){
                        trainTicketType = "Sparpreis 2. Klasse";
                    }else if(trainTicket->getTicketType() == "FP1"){
                        trainTicketType = "Flexpreis 1. Klasse";
                    }else if(trainTicket->getTicketType() == "FP2"){
                        trainTicketType = "Flexpreis 2. Klasse";
                    }else{
                        trainTicketType = "Undefined";
                    }
                    ui->trainTicketTyp->setText(QString::fromStdString(trainTicketType));

                    std::vector<ConnectingStation>connectingStationList = trainTicket->getConnectingStations();
                    QStringListModel *model = new QStringListModel();
                    //Convert the vector of string to QStringList
                    QStringList qStringList;
                    for (const ConnectingStation &connectingStation : connectingStationList) {
                        QString stationInfo = QString::fromStdString(connectingStation.getStationName()) +
                                              " (Latitude: " + QString::number(connectingStation.getLatitude()) +
                                              ", Longitude: " + QString::number(connectingStation.getLongitude()) + ")";
                        qStringList << stationInfo;
                    }
                    //Set the QStringList as the model data
                    model->setStringList(qStringList);
                    //set the model for the QListView
                    ui->trainConnecting->setModel(model);
                } else{

                }
            }
        }
    }
}

void BuchungsDetails::on_speichern_clicked()
{
    std::string id = QString(ui->Id->text()).toStdString();

    QDate newFromDate = ui->fromDate->date();
    QDate newToDate = ui->toDate->date();
    double newPreis = ui->preis->value();

    Booking* bookingToUpdate = travelAgency->findBooking(id);

    if(bookingToUpdate){
        bookingToUpdate->setFromDate(newFromDate.toString("yyyyMMdd").toStdString());
        bookingToUpdate->setToDate(newToDate.toString("yyyyMMdd").toStdString());
        bookingToUpdate->setPrice(newPreis);

        if(FlightBooking* flightBooking = dynamic_cast<FlightBooking*>(bookingToUpdate)){
            flightBooking->setAirline(ui->flugAirline->text().toStdString());
            flightBooking->setFromDestination(ui->flugFromDest->text().toStdString());
            flightBooking->setToDestination(ui->flugToDest->text().toStdString());
            QString bookingClassStr = ui->flugBookingClass->text();
            std::string bookingClass;

            if(bookingClassStr == "Economy"){
                bookingClass = "Y";
            }else if(bookingClassStr == "Premium Economy"){
                bookingClass = "W";
            }else if(bookingClassStr == "Business"){
                bookingClass = "J";
            }else if(bookingClassStr == "First"){
                bookingClass = "F";
            }else{
                bookingClass = "Undefined";
            }
            flightBooking->setBookingClass(bookingClass);

            if(travelAgency->getAirport(ui->fromDestCode->text().toStdString()) &&
                travelAgency->getAirport(ui->toDestCode->text().toStdString())){
                flightBooking->setFromDestination(ui->fromDestCode->text().toStdString());
                flightBooking->setToDestination(ui->toDestCode->text().toStdString());
            }else{
                if(travelAgency->getAirport(ui->fromDestCode->text().toStdString()) == nullptr)
                {
                    ui->fromDestCode->setText("Ungultiger Iata Codes");
                    ui->fromDestCode->setStyleSheet("color: red;");
                }

                if(travelAgency->getAirport(ui->toDestCode->text().toStdString()) == nullptr)
                {
                    ui->toDestCode->setText("Ungultiger Iata Codes");
                    ui->toDestCode->setStyleSheet("color: red;");
                }

            }
        }else if(HotelBooking* hotelBooking = dynamic_cast<HotelBooking*>(bookingToUpdate)){
            hotelBooking->setHotel(ui->hotelName->text().toStdString());
            hotelBooking->setTown(ui->townName->text().toStdString());
            QString roomTypeStr = ui->hotelRoomType->text();
            std::string roomType;

            if(roomTypeStr == "Einzelzimmer"){
                roomType = "EZ";
            }else if(roomTypeStr == "Doppelzimmer"){
                roomType = "DZ";
            }else if(roomTypeStr == "Suite"){
                roomType = "SU";
            }else if(roomTypeStr == "Appartment"){
                roomType = "AP";
            }else{
                roomType = "Undefined";
            }
            hotelBooking->setRoomType(roomType);
        }else if(RentalCarReservation *carBooking = dynamic_cast<RentalCarReservation*>(bookingToUpdate)){
            carBooking->setCompany(ui->mietwagenCompany->text().toStdString());
            carBooking->setPickupLocation(ui->mietwagenPickupLocation->text().toStdString());
            carBooking->setReturnLocation(ui->mietwagenReturnLocation->text().toStdString());
            carBooking->setVehicleClass(ui->mietwagenVehicleClass->text().toStdString());
        }else if(TrainTicket* trainBooking = dynamic_cast<TrainTicket*>(bookingToUpdate)){
            trainBooking->setFromDestination(ui->trainFromDest->text().toStdString());
            trainBooking->setToDestination(ui->trainToDest->text().toStdString());
            trainBooking->setDepartureTime(ui->trainTimeAbfahrt->time().toString("hh:mm").toStdString());
            trainBooking->setDepartureTime(ui->trainTimeAnkunft->time().toString("hh:mm").toStdString());
            QString trainTicketTypeStr = ui->trainTicketTyp->text();
            std::string trainTicketType;
            if(trainTicketTypeStr == "Supersparpreis 1. Klasse"){
                trainTicketType = "SSP1";
            }else if(trainTicketTypeStr == "Supersparpreis 2. Klasse"){
                trainTicketType = "SSP2";
            }else if(trainTicketTypeStr == "Sparpreis 1. Klasse"){
                trainTicketType = "SP1";
            }else if(trainTicketTypeStr == "Sparpreis 2. Klasse"){
                trainTicketType = "SP2";
            }else if(trainTicketTypeStr == "Flexpreis 1. Klasse"){
                trainTicketType = "FP1";
            }else if(trainTicketTypeStr == "Flexpreis 2. Klasse"){
                trainTicketType = "FP2";
            }else{
                trainTicketType = "Undefined";
            }

            QStringList selectedStations;
            QModelIndexList selectedIndexes = ui->trainConnecting->selectionModel()->selectedIndexes();

            for (const QModelIndex &index : selectedIndexes) {
                selectedStations << index.data().toString();
            }

            std::vector<ConnectingStation> newConnectingStations;
            for (const QString &station : selectedStations) {
                // Parse the QString to extract the station name, latitude, and longitude
                QStringList parts = station.split(" (Lat: ");
                if (parts.size() == 2) {
                    QString stationName = parts[0];
                    QString latLon = parts[1];
                    latLon = latLon.left(latLon.length() - 1); // Remove trailing ")"
                    QStringList latLonParts = latLon.split(", Lon: ");
                    if (latLonParts.size() == 2) {
                        double latitude = latLonParts[0].toDouble();
                        double longitude = latLonParts[1].toDouble();

                        // Create a ConnectingStation object and add it to the vector
                        ConnectingStation connectingStation{stationName.toStdString(), latitude, longitude};
                        newConnectingStations.push_back(connectingStation);
                    }
                }
            }

            // 2. Update the TrainTicket object's connecting station list
            trainBooking->setConnectingStations(newConnectingStations);
        }
    }

    ui->speichern->setEnabled(false);
    ui->abbrechen->setEnabled(false);
}


void BuchungsDetails::on_abbrechen_clicked()
{
    std::string id = ui->Id->text().toStdString();
    Booking* bookingToUpdate = travelAgency->findBooking(id);

    if(bookingToUpdate){
        ui->fromDate->setDate(QDate::fromString(QString::fromStdString(bookingToUpdate->getFromDate()), "yyyyMMdd"));
        ui->toDate->setDate(QDate::fromString(QString::fromStdString(bookingToUpdate->getToDate()), "yyyyMMdd"));
        ui->preis->setValue(bookingToUpdate->getPrice());

        if(FlightBooking* flightBooking = dynamic_cast<FlightBooking*>(bookingToUpdate)){
            ui->buchungWidget->setCurrentWidget(ui->flugTab);
            ui->flugAirline->setText(QString::fromStdString(flightBooking->getAirline()));
            ui->flugFromDest->setText(QString::fromStdString(flightBooking->getFromDestination()));
            ui->flugToDest->setText(QString::fromStdString(flightBooking->getToDestination()));
            string bookingClass;
            if(flightBooking->getBookingClass() == "Y"){
                bookingClass = "Economy";
            }else if(flightBooking->getBookingClass() == "W"){
                bookingClass = "Premium Economy";
            }else if(flightBooking->getBookingClass() == "J"){
                bookingClass = "Business";
            }else if(flightBooking->getBookingClass() == "F"){
                bookingClass = "First";
            }else{
                bookingClass = "Undefined";
            }
            ui->flugBookingClass->setText(QString::fromStdString(bookingClass));
        } else if(HotelBooking* hotelBooking = dynamic_cast<HotelBooking*>(bookingToUpdate)){

            ui->buchungWidget->setCurrentWidget(ui->hotelTab);
            ui->hotelName->setText(QString::fromStdString(hotelBooking->getHotel()));
            ui->townName->setText(QString::fromStdString(hotelBooking->getTown()));
            std::string roomType;
            if(hotelBooking->getRoomType() == "EZ"){
                roomType = "Einzelzimmer";
            }else if(hotelBooking->getRoomType() == "DZ"){
                roomType = "Doppelzimmer";
            }else if(hotelBooking->getRoomType() == "SU"){
                roomType = "Suite";
            }else if(hotelBooking->getRoomType() == "AP"){
                roomType = "Appartment";
            }else{
                roomType = "Undefined";
            }

            ui->hotelRoomType->setText(QString::fromStdString(roomType));

        } else if(RentalCarReservation* carBooking = dynamic_cast<RentalCarReservation*>(bookingToUpdate)){

            ui->buchungWidget->setCurrentWidget(ui->mietwagenTab);

            ui->mietwagenPickupLocation->setText(QString::fromStdString(carBooking->getPickupLocation()));
            ui->mietwagenReturnLocation->setText(QString::fromStdString(carBooking->getReturnLocation()));
            ui->mietwagenCompany->setText(QString::fromStdString(carBooking->getCompany()));
            ui->mietwagenVehicleClass->setText(QString::fromStdString(carBooking->getVehicleClass()));

        } else if(TrainTicket* trainTicket = dynamic_cast<TrainTicket*>(bookingToUpdate)){

            ui->buchungWidget->setCurrentWidget(ui->zugTab);

            ui->trainFromDest->setText(QString::fromStdString(trainTicket->getFromDestination()));
            ui->trainToDest->setText(QString::fromStdString(trainTicket->getToDestination()));
            ui->trainTimeAbfahrt->setTime(QTime::fromString(QString::fromStdString(trainTicket->getDepartureTime()), "hh:mm"));
            ui->trainTimeAnkunft->setTime(QTime::fromString(QString::fromStdString(trainTicket->getDepartureTime()), "hh:mm"));
            string trainTicketType;
            if(trainTicket->getTicketType() == "SSP1"){
                trainTicketType = "Supersparpreis 1. Klasse";
            }else if(trainTicket->getTicketType() == "SSP2"){
                trainTicketType = "Supersparpreis 2. Klasse";
            }else if(trainTicket->getTicketType() == "SP1"){
                trainTicketType = "Sparpreis 1. Klasse";
            }else if(trainTicket->getTicketType() == "SP2"){
                trainTicketType = "Sparpreis 2. Klasse";
            }else if(trainTicket->getTicketType() == "FP1"){
                trainTicketType = "Flexpreis 1. Klasse";
            }else if(trainTicket->getTicketType() == "FP2"){
                trainTicketType = "Flexpreis 2. Klasse";
            }else{
                trainTicketType = "Undefined";
            }
            ui->trainTicketTyp->setText(QString::fromStdString(trainTicketType));

            std::vector<ConnectingStation>connectingStationList = trainTicket->getConnectingStations();
            QStringListModel *model = new QStringListModel();
            //Convert the vector of string to QStringList
            QStringList qStringList;
            for(const ConnectingStation &connectingStation : connectingStationList){
                QString stationInfo = QString::fromStdString(connectingStation.getStationName()) +
                                      "(Latitude: " + QString::number(connectingStation.getLatitude()) +
                                      "(Longitude: " + QString::number(connectingStation.getLongitude());
                qStringList << stationInfo;
            }
            //Set the QStringList as the model data
            model->setStringList(qStringList);
            //set the model for the QListView
            ui->trainConnecting->setModel(model);
        }
    }

    ui->speichern->setEnabled(false);
    ui->abbrechen->setEnabled(false);
}

