#include "travelagencyui.h"
#include "ui_travelagencyui.h"

TravelAgencyUi::TravelAgencyUi(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::TravelAgencyUi)
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
            travelagency.readFile(filePath);
            int totalFlightBooking = travelagency.getTotalFlightBooking();
            int totalHotelBooking = travelagency.getTotalFlightBooking();
            int totalRentalCarReservation = travelagency.getTotalRentalCarReservation();
            int totalTrainBooking = travelagency.getTotalTrainBooking();
            double totalFlightPrice = travelagency.getTotalFlightPrice();
            double totalHotelPrice = travelagency.getTotalHotelPrice();
            double totalRentalCarReservationPrice = travelagency.getTotalRentalCarReservationPrice();
            double totalTrainPrice = travelagency.getTotalTrainPrice();

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
        }catch(const std::runtime_error &e){
            msgBox.critical(this, "Fehler beim Einlesen der Buchungen", QString(e.what()));
        }
    }
}

