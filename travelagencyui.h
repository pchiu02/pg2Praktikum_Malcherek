#ifndef TRAVELAGENCYUI_H
#define TRAVELAGENCYUI_H

#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>
#include <QDate>
#include <QDateEdit>

#include "QtWidgets/qlistwidget.h"
#include "travelagency.h"


QT_BEGIN_NAMESPACE
namespace Ui { class TravelAgencyUi; }
QT_END_NAMESPACE

class TravelAgencyUi : public QMainWindow
{
    Q_OBJECT

public:
    TravelAgencyUi(QWidget *parent = nullptr);
    ~TravelAgencyUi();

private slots:
    void on_actionEinlesen_triggered();

    void on_buchungListen_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::TravelAgencyUi *ui;
    TravelAgency* travelagency;
    QMessageBox msgBox;
};
#endif // TRAVELAGENCYUI_H
