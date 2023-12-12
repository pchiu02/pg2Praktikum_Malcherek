#include "travelagencyui.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"
#include "ui_travelagencyui.h"
#include "suchendialog.h"
#include "buchungsdetails.h"

TravelAgencyUi::TravelAgencyUi(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::TravelAgencyUi), travelagency(new TravelAgency)
{
    ui->setupUi(this);

    //ui->readButton->setIcon(QIcon("importFile.png"));
    ui->readButton->setIconSize(QSize(24,24));
    ui->readButton->setFlat(true);

    //ui->searchButton->setIcon(QIcon("search.svg.png"));
    ui->searchButton->setIconSize(QSize(24,24));
    ui->searchButton->setFlat(true);

    ui->saveButton->setIconSize(QSize(24,24));
    ui->saveButton->setFlat(true);

    ui->kundBox->setVisible(false);
    ui->reiseBox->setVisible(false);

    ui->reiseId->setReadOnly(true);
}

TravelAgencyUi::~TravelAgencyUi()
{
    delete ui;
}


void TravelAgencyUi::on_actionEinlesen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open JSON File", "", "JSON Files (*.json)");
    if (!filePath.isEmpty()){
        try {
            travelagency->readFile(filePath);

            msgBox.information(this, "Success", "Success");

            msgBox.information(this, "Datei erfolgreich eingelesen", travelagency->getBookingsInfo());

        }catch(const std::runtime_error &e){
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Fehler beim Einlesen der Buchungen");
            msgBox.setText(QString::fromUtf8(e.what()));
            msgBox.setInformativeText("Das Einlesen der Buchungen wurde in der betroffenen Zeile gestoppt."
                           " Die vorangehenden Buchungen wurden erfolgreich angelegt.");
            msgBox.setDetailedText("Wenn Sie die Datei bereits korrigiert haben, waehlen Sie 'Retry'."
                                   "Waehlen Sie 'Discard', um alle Buchungen zu loeschen und 'Cancel',"
                                   "um die vorhandenen Buchungen stehenzulassen und diesen Dialog zu verlassen");
            msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);

            int ret = msgBox.exec();

            switch(ret){
                case QMessageBox::Retry:
                    on_actionEinlesen_triggered();
                    break;
                case QMessageBox::Discard:
                    break;
                case QMessageBox::Cancel:
                    break;
                default:
                    msgBox.critical(this, "Error", "Error");
            }
        }
    }
}

void TravelAgencyUi::on_readButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open JSON File", "", "JSON Files (*.json)");
    if (!filePath.isEmpty()){
        try {
            travelagency->readFile(filePath);

            msgBox.information(this, "Success", "Success");

            msgBox.information(this, "Datei erfolgreich eingelesen", travelagency->getBookingsInfo());

//            ui->buchungListen->clear();
//            std::vector<Booking*> bookings = travelagency->getAllBooking();
//            for (Booking* booking : bookings){
//                QString details = QString::fromStdString(booking->showDetails());
//                QListWidgetItem* item = new QListWidgetItem(details);
//                ui->buchungListen->addItem(item);
//            }

        }catch(const std::runtime_error &e){
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle("Fehler beim Einlesen der Buchungen");
            msgBox.setText(QString::fromUtf8(e.what()));
            msgBox.setInformativeText("Das Einlesen der Buchungen wurde in der betroffenen Zeile gestoppt."
                           " Die vorangehenden Buchungen wurden erfolgreich angelegt.");
            msgBox.setDetailedText("Wenn Sie die Datei bereits korrigiert haben, waehlen Sie 'Retry'."
                                   "Waehlen Sie 'Discard', um alle Buchungen zu loeschen und 'Cancel',"
                                   "um die vorhandenen Buchungen stehenzulassen und diesen Dialog zu verlassen");
            msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);

            int ret = msgBox.exec();

            switch(ret){
                case QMessageBox::Retry:
                    on_actionEinlesen_triggered();
                    break;
                case QMessageBox::Discard:
                    break;
                case QMessageBox::Cancel:
                    break;
                default:
                    msgBox.critical(this, "Error", "Error");
            }
        }
    }
}

void TravelAgencyUi::on_searchButton_clicked()
{
    SuchenDialog suchenDialog(this);
    ui->reisen_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    if(suchenDialog.exec() == QDialog::Accepted)
    {
        ui->kundBox->setVisible(true);
        int enteredId = suchenDialog.getId();
        string firstName = " ";
        string lastName = " ";
        Customer* foundCustomer = travelagency->findCustomer(enteredId, firstName, lastName);
        if(foundCustomer)
        {
            ui->id_Kund->setText(QString::number(foundCustomer->getId()));
            ui->name_Kund->setText(QString::fromStdString(foundCustomer->getFirstName())
                                   + " " +
                                   QString::fromStdString(foundCustomer->getLastName()));
            std::vector<int> addedTravelIds;
            std::vector<int> displayedTravelIds;
            for(Travel* travel : travelagency->getAllTravel())
            {
                if(travel->getCustomerId() == enteredId)
                {
                    int travelID = travel->getId();

                    if(std::find(displayedTravelIds.begin(), displayedTravelIds.end(), travelID) != displayedTravelIds.end())
                    {
                        continue;
                    }

                    addedTravelIds.push_back(travelID);

                    vector<Booking*> bookings = travel->getTravelBookings();
                    if(!bookings.empty())
                    {
                        std::string earliestFromDate = bookings[0]->getFromDate();
                        std::string latestToDate = bookings[0]->getToDate();

                        for(const Booking* booking: bookings)
                        {
                            if(booking->getFromDate() < earliestFromDate)
                            {
                                earliestFromDate = booking->getFromDate();

                            }
                            else if(booking->getToDate() > latestToDate)
                            {
                                latestToDate = booking->getToDate();
                            }
                        }

                        QString fromDate = QString::fromStdString(earliestFromDate);
                        QString toDate = QString::fromStdString(latestToDate);

                        QDate fromDateObj = QDate::fromString(fromDate, "yyyyMMdd");
                        QDate toDateObj = QDate::fromString(toDate, "yyyyMMdd");

                        QString formattedFromDate = fromDateObj.toString("dd.MM.yyyy");
                        QString formattedToDate = toDateObj.toString("dd.MM.yyyy");

                        QTableWidgetItem* fromDateItem = new QTableWidgetItem(formattedFromDate);
                        QTableWidgetItem* toDateItem = new QTableWidgetItem(formattedToDate);

                        int rowCount = ui->reisen_Table->rowCount();

                        ui->reisen_Table->setRowCount(rowCount+1);
                        ui->reisen_Table->setItem(rowCount, 0, new QTableWidgetItem(QString::number(travelID)));
                        ui->reisen_Table->setItem(rowCount, 1, fromDateItem);
                        ui->reisen_Table->setItem(rowCount, 2, toDateItem);
                    }

                    displayedTravelIds.push_back(travelID);
                }
            }
        }else{
            QMessageBox::critical(this, "Error", "Customer not found");
        }
    }
}





void TravelAgencyUi::on_reisen_Table_itemDoubleClicked(QTableWidgetItem *item)
{
    ui->reiseBox->setVisible(true);
    ui->buchung_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->buchung_table->clearContents();
    ui->buchung_table->setRowCount(0);

    int selectedReiseID = item->text().toInt();

    if(item != nullptr)
    {
        ui->reiseId->setText(item->text());
    }

    for(Travel* travel : travelagency->getAllTravel())
    {
        if(travel->getId() == selectedReiseID)
        {
          const std::vector<Booking*> bookings = travel->getTravelBookings();
          int rowCount = bookings.size();
          std::vector<Booking*> currentBooking = travel->getTravelBookings();

          ui->buchung_table->setRowCount(rowCount);

          for(int i = 0; i < rowCount; i++)
          {
              QString fromDate = QString::fromStdString(bookings[i]->getFromDate());
              QString toDate = QString::fromStdString(bookings[i]->getToDate());
              QString preis = QString::number(bookings[i]->getPrice(), 'f', 2);
              QTableWidgetItem* buchungsTypItem = new QTableWidgetItem();
              QTableWidgetItem* preisItem = new QTableWidgetItem(preis);

              QDate fromDateObj = QDate::fromString(fromDate, "yyyyMMdd");
              QDate toDateObj = QDate::fromString(toDate, "yyyyMMdd");

              QString formattedFromDate = fromDateObj.toString("dd.MM.yyyy");
              QString formattedToDate = toDateObj.toString("dd.MM.yyyy");

              QTableWidgetItem* startItem = new QTableWidgetItem(formattedFromDate);
              QTableWidgetItem* endItem = new QTableWidgetItem(formattedToDate);

              if(dynamic_cast<FlightBooking*>(bookings[i]))
              {
                  buchungsTypItem->setIcon(QIcon("flightIcon.png"));
              }else if(dynamic_cast<HotelBooking*>(bookings[i]))
              {
                  buchungsTypItem->setIcon(QIcon("hotelIcon.png"));
              }else if(dynamic_cast<RentalCarReservation*>(bookings[i]))
              {
                  buchungsTypItem->setIcon(QIcon("carIcon.png"));
              }else if(dynamic_cast<TrainTicket*>(bookings[i]))
              {
                  buchungsTypItem->setIcon(QIcon("trainIcon.png"));
              }

              ui->buchung_table->setItem(i, 0, buchungsTypItem);
              ui->buchung_table->setItem(i, 1, startItem);
              ui->buchung_table->setItem(i, 2, endItem);
              ui->buchung_table->setItem(i, 3, preisItem);
          }
        }
    }

}

//void TravelAgencyUi::on_buchungListen_itemDoubleClicked(QListWidgetItem *item)
//{
//    QString text = item->text();
//    for(Booking* booking : travelagency->getAllBooking())
//    {
//        if(QString::fromStdString(booking->showDetails()) == text)
//        {
//            if(FlightBooking* flightBooking = dynamic_cast<FlightBooking*>(booking))
//            {
//                ui->bookingWidget->setCurrentWidget(ui->flightBookingTab);
//                ui->flightId->setText(QString::fromStdString(flightBooking->getId()));
//                ui->flightAirline->setText(QString::fromStdString(flightBooking->getAirline()));
//                ui->flightFromDate->setDate(QDate::fromString(QString::fromStdString(flightBooking->getFromDate()), "yyyyMMdd"));
//                ui->flightToDate->setDate(QDate::fromString(QString::fromStdString(flightBooking->getFromDate()), "yyyyMMdd"));
//                ui->flightFromDest->setText(QString::fromStdString(flightBooking->getFromDestination()));
//                ui->flightToDest->setText(QString::fromStdString(flightBooking->getToDestination()));
//                ui->flightPrice->setDecimals(2);
//                ui->flightPrice->setSingleStep(0.01);
//                ui->flightPrice->setRange(0.0, std::numeric_limits<double>::max());
//                ui->flightPrice->setPrefix("€");
//                ui->flightPrice->setValue(flightBooking->getPrice());
//            }

//            else if(HotelBooking* hotelBooking = dynamic_cast<HotelBooking*>(booking))
//            {
//                ui->bookingWidget->setCurrentWidget(ui->hotelBookingTab);
//                ui->hotelId->setText(QString::fromStdString(hotelBooking->getId()));
//                ui->hotelName->setText(QString::fromStdString(hotelBooking->getHotel()));
//                ui->hotelTownName->setText(QString::fromStdString(hotelBooking->getTown()));
//                ui->hotelFromDate->setDate(QDate::fromString(QString::fromStdString(hotelBooking->getFromDate()),"yyyyMMdd"));
//                ui->hotelToDate->setDate(QDate::fromString(QString::fromStdString(hotelBooking->getToDate()), "yyyyMMdd"));
//                ui->hotelPrice->setDecimals(2);
//                ui->hotelPrice->setSingleStep(0.01);
//                ui->hotelPrice->setRange(0.0, std::numeric_limits<double>::max());
//                ui->hotelPrice->setPrefix("€");
//                ui->hotelPrice->setValue(hotelBooking->getPrice());
//            }

//            else if(RentalCarReservation* carBooking = dynamic_cast<RentalCarReservation*>(booking))
//            {
//                ui->bookingWidget->setCurrentWidget(ui->carBookingTab);
//                ui->carId->setText(QString::fromStdString(carBooking->getId()));
//                ui->carCompany->setText(QString::fromStdString(carBooking->getCompany()));
//                ui->carFromDate->setDate(QDate::fromString(QString::fromStdString(carBooking->getFromDate()), "yyyyMMdd"));
//                ui->carToDate->setDate(QDate::fromString(QString::fromStdString(carBooking->getToDate()), "yyyyMMdd"));
//                ui->carPickupLocation->setText(QString::fromStdString(carBooking->getPickupLocation()));
//                ui->carReturnLocation->setText(QString::fromStdString(carBooking->getReturnLocation()));
//                ui->carPrice->setDecimals(2);
//                ui->carPrice->setSingleStep(0.01);
//                ui->carPrice->setRange(0.0, std::numeric_limits<double>::max());
//                ui->carPrice->setPrefix("€");
//                ui->carPrice->setValue(carBooking->getPrice());
//            }
//            else if(TrainTicket* trainBooking = dynamic_cast<TrainTicket*>(booking))
//            {
//                ui->bookingWidget->setCurrentWidget(ui->trainBookingTab);
//                ui->trainId->setText(QString::fromStdString(trainBooking->getId()));
//                ui->trainFromStation->setText(QString::fromStdString(trainBooking->getFromDestination()));
//                ui->trainToStation->setText(QString::fromStdString(trainBooking->getToDestination()));
//                ui->trainDepartureTime->setText(QString::fromStdString(trainBooking->getDepartureTime()));
//                ui->trainArrivalTime->setText(QString::fromStdString(trainBooking->getArrivalTime()));
//                ui->trainFromDate->setDate(QDate::fromString(QString::fromStdString(trainBooking->getFromDate()), "yyyyMMdd"));
//                ui->trainToDate->setDate(QDate::fromString(QString::fromStdString(trainBooking->getToDate()), "yyyyMMdd"));
//                ui->trainPrice->setDecimals(2);
//                ui->trainPrice->setSingleStep(0.01);
//                ui->trainPrice->setRange(0.0, std::numeric_limits<double>::max());
//                ui->trainPrice->setPrefix("€");
//                ui->trainPrice->setValue(trainBooking->getPrice());

//                std::vector<std::string>connectingStationList = trainBooking->getConnectingStations();
//                QStringListModel *model = new QStringListModel();

//                //Convert the vector of strings to QStringList
//                QStringList qStringList;
//                for(const std::string &connectingStationLists : connectingStationList)
//                {
//                    qStringList << QString::fromStdString(connectingStationLists);
//                }

//                //Set the QStringList as the model data
//                model->setStringList(qStringList);

//                //set the model for the QListView
//                ui->connectionList->setModel(model);
//            }
//        }
//    }
//}

void TravelAgencyUi::on_buchung_table_itemDoubleClicked(QTableWidgetItem *item)
{
    BuchungsDetails *buchungsDetails = new BuchungsDetails(travelagency, this);
    int row = item->row();
    QString QSrow = QString::number(row);
    QString reiseID = ui->reiseId->text();
    buchungsDetails->setBookingDetails(QSrow, reiseID);
    buchungsDetails->show();
}


void TravelAgencyUi::on_saveButton_clicked()
{
    QJsonArray jsonArray;

    for(const auto& booking : travelagency->getAllBooking()){
        QJsonObject bookingObject;
        std::string firstName = "";
        std::string lastName = "";
        Travel* travel = travelagency->findTravel(booking->getTravelId());
        Customer* customer = travelagency->findCustomer(travel->getCustomerId(), firstName, lastName);
        bookingObject["id"] = QString::fromStdString(booking->getId());
        bookingObject["customerId"] = QString::number(customer->getId());
        bookingObject["customerFirstName"] = QString::fromStdString(customer->getFirstName());
        bookingObject["customerLastName"] = QString::fromStdString(customer->getLastName());
        bookingObject["fromDate"] = QString::fromStdString(booking->getFromDate());
        bookingObject["toDate"] = QString::fromStdString(booking->getToDate());
        bookingObject["price"] = QString::number(booking->getPrice());
        bookingObject["travelId"] = QString::number(booking->getTravelId());

        if(FlightBooking* flightBooking = dynamic_cast<FlightBooking*>(booking)){
          bookingObject["type"] = "Flight";
          bookingObject["airline"] = QString::fromStdString(flightBooking->getAirline());
          bookingObject["bookingClass"] = QString::fromStdString(flightBooking->getBookingClass());
          bookingObject["fromDest"] = QString::fromStdString(flightBooking->getFromDestination());
          bookingObject["toDest"] = QString::fromStdString(flightBooking->getToDestination());
        }else if(RentalCarReservation* carBooking = dynamic_cast<RentalCarReservation*>(booking)){
          bookingObject["type"] = "Car";
          bookingObject["company"] = QString::fromStdString(carBooking->getCompany());
          bookingObject["pickupLocation"] = QString::fromStdString(carBooking->getPickupLocation());
          bookingObject["returnLocation"] = QString::fromStdString(carBooking->getReturnLocation());
          bookingObject["vehicleClass"] = QString::fromStdString(carBooking->getVehicleClass());
        }else if(HotelBooking* hotelBooking = dynamic_cast<HotelBooking*>(booking)){
          bookingObject["type"] = "Hotel";
          bookingObject["hotel"] = QString::fromStdString(hotelBooking->getHotel());
          bookingObject["town"] = QString::fromStdString(hotelBooking->getTown());
          bookingObject["roomType"] = QString::fromStdString(hotelBooking->getRoomType());
        }else if(TrainTicket* trainBooking = dynamic_cast<TrainTicket*>(booking)){
          bookingObject["type"] = "Train";
          bookingObject["fromDestination"] = QString::fromStdString(trainBooking->getFromDestination());
          bookingObject["toDestination"] = QString::fromStdString(trainBooking->getToDestination());
          bookingObject["departureTime"] = QString::fromStdString(trainBooking->getDepartureTime());
          bookingObject["arrivalTime"] = QString::fromStdString(trainBooking->getArrivalTime());
          bookingObject["ticketType"] = QString::fromStdString(trainBooking->getTicketType());

          QJsonArray connectingStationsArray;
          const std::vector<std::string>& connectingStations = trainBooking->getConnectingStations();
          for(const std::string& station : connectingStations){
              connectingStationsArray.append(QString::fromStdString(station));
          }
          bookingObject["connectingStations"] = connectingStationsArray;
        }

        jsonArray.append(bookingObject);
    }
    QJsonDocument jsonDocument(jsonArray);
    QFile outputFile(QString::fromStdString("bookingsPraktikum3_new"));
    if(outputFile.open(QIODevice::WriteOnly)){
        outputFile.write(jsonDocument.toJson());
        outputFile.close();
        qDebug() << "Booking saved to bookingsPraktikum3_new";
    }
}

