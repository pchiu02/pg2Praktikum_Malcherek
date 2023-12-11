#include "buchungsdetails.h"
#include "ui_buchungsdetails.h"
#include "booking.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"

BuchungsDetails::BuchungsDetails(TravelAgency* travelAgency, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuchungsDetails), travelAgency(travelAgency)
{
    ui->setupUi(this);
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
                    ui->flugFromDest->setText(QString::fromStdString(flightBooking->getFromDestination()));
                    ui->flugToDest->setText(QString::fromStdString(flightBooking->getToDestination()));
                    ui->flugAirline->setText(QString::fromStdString(flightBooking->getAirline()));
                    string bookingClass;
                    if(flightBooking->getBookingClass() == 'Y')


                } else if(HotelBooking* hotelBooking = dynamic_cast<HotelBooking*>(booking)){

                    ui->buchungWidget->setCurrentWidget(ui->hotelTab);

                } else if(RentalCarReservation* carBooking = dynamic_cast<RentalCarReservation*>(booking)){

                    ui->buchungWidget->setCurrentWidget(ui->mietwagenTab);

                } else if(TrainTicket* trainTicket = dynamic_cast<TrainTicket*>(booking)){

                    ui->buchungWidget->setCurrentWidget(ui->zugTab);

                } else{

                }
           }
       }
   }
}
