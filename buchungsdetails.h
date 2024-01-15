#ifndef BUCHUNGSDETAILS_H
#define BUCHUNGSDETAILS_H

#include <QDialog>

#include "travelagency.h"
#include "check.h"

namespace Ui {
class BuchungsDetails;
}

class BuchungsDetails : public QDialog
{
    Q_OBJECT

public:
    explicit BuchungsDetails(std::shared_ptr<TravelAgency> travelAgency, QWidget *parent = nullptr);
    ~BuchungsDetails();
    void setBookingDetails(QString row, QString reiseId);

private slots:
    void on_speichern_clicked();

    void on_abbrechen_clicked();

signals:
    void bookingChanged();

private:
    Ui::BuchungsDetails* ui;
    std::shared_ptr<TravelAgency> travelAgency;
    std::unique_ptr<Check> check;
};

#endif // BUCHUNGSDETAILS_H
