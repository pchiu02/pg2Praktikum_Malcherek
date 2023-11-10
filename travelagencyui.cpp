#include "travelagencyui.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"
#include "ui_travelagencyui.h"

TravelAgencyUi::TravelAgencyUi(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::TravelAgencyUi), travelagency(new TravelAgency)
{
    ui->setupUi(this);
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
            int totalFlightBooking = travelagency->getTotalFlightBooking();
            int totalHotelBooking = travelagency->getTotalFlightBooking();
            int totalRentalCarReservation = travelagency->getTotalRentalCarReservation();
            int totalTrainBooking = travelagency->getTotalTrainBooking();
            double totalFlightPrice = travelagency->getTotalFlightPrice();
            double totalHotelPrice = travelagency->getTotalHotelPrice();
            double totalRentalCarReservationPrice = travelagency->getTotalRentalCarReservationPrice();
            double totalTrainPrice = travelagency->getTotalTrainPrice();

            msgBox.information(this, "Success", "Success");

            msgBox.information(this, "Datei erfolgreich eingelesen", QString("Es wurden %1 Fluege im Wert von %2 Euro, "
                                                                             "%3 Hotelbuchungen im Wert von %4 Euro, "
                                                                             "%5 Mietwagenbuchungen im Wert von %6 Euro, "
                                                                             "und %7 Zugbuchungen im Wert von %8 Euro eingelesen")
                                                                             .arg(totalFlightBooking)
                                                                             .arg(static_cast<double>(totalFlightPrice), 0, 'f', 2)
                                                                             .arg(totalHotelBooking)
                                                                             .arg(static_cast<double>(totalHotelPrice), 0, 'f', 2)
                                                                             .arg(totalRentalCarReservation)
                                                                             .arg(static_cast<double>(totalRentalCarReservationPrice), 0, 'f', 2)
                                                                             .arg(totalTrainBooking)
                                                                             .arg(static_cast<double>(totalTrainPrice), 0, 'f', 2));

            ui->buchungListen->clear();
            std::vector<Booking*> bookings = travelagency->getBookings();
            for (Booking* booking : bookings){
                QString details = QString::fromStdString(booking->showDetails());
                QListWidgetItem* item = new QListWidgetItem(details);
                ui->buchungListen->addItem(item);
            }

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

void TravelAgencyUi::on_buchungListen_itemDoubleClicked(QListWidgetItem *item)
{
    QString text = item->text();
    for(Booking* booking : travelagency->getBookings())
    {
        if(QString::fromStdString(booking->showDetails()) == text)
        {
            if(FlightBooking* flightBooking = dynamic_cast<FlightBooking*>(booking))
            {
                ui->bookingWidget->setCurrentWidget(ui->flightBookingTab);
                ui->flightId->setText(QString::fromStdString(flightBooking->getId()));
                ui->flightAirline->setText(QString::fromStdString(flightBooking->getAirline()));
                ui->flightFromDate->setDate(QDate::fromString(QString::fromStdString(flightBooking->getFromDate()), "yyyyMMdd"));
                ui->flightToDate->setDate(QDate::fromString(QString::fromStdString(flightBooking->getFromDate()), "yyyyMMdd"));
                ui->flightFromDest->setText(QString::fromStdString(flightBooking->getFromDestination()));
                ui->flightToDest->setText(QString::fromStdString(flightBooking->getToDestination()));
                ui->flightPrice->setDecimals(2);
                ui->flightPrice->setSingleStep(0.01);
                ui->flightPrice->setRange(0.0, std::numeric_limits<double>::max());
                ui->flightPrice->setPrefix("€");
                ui->flightPrice->setValue(flightBooking->getPrice());
            }

            if(HotelBooking* hotelBooking = dynamic_cast<HotelBooking*>(booking))
            {
                ui->bookingWidget->setCurrentWidget(ui->hotelBookingTab);
            }
        }
    }
}

