#ifndef BUCHUNGSDETAILS_H
#define BUCHUNGSDETAILS_H

#include <QDialog>

#include "travelagency.h"

namespace Ui {
class BuchungsDetails;
}

class BuchungsDetails : public QDialog
{
    Q_OBJECT

public:
    explicit BuchungsDetails(TravelAgency* travelAgency, QWidget *parent = nullptr);
    ~BuchungsDetails();
    void setBookingDetails(QString row, QString reiseId);

private slots:
    void on_speichern_clicked();

    void on_abbrechen_clicked();

private:
    Ui::BuchungsDetails* ui;
    TravelAgency* travelAgency;
};

#endif // BUCHUNGSDETAILS_H
