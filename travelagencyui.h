#ifndef TRAVELAGENCYUI_H
#define TRAVELAGENCYUI_H

#include <QMainWindow>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>
#include <QDate>
#include <QDateEdit>
#include <QListView>
#include <QListWidgetItem>
#include <QStringListModel>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "QtWidgets/qlistwidget.h"
#include "buchungsdetails.h"
#include "travelagency.h"
#include "check.h"
#include "results.h"


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

    void on_readButton_clicked();

    void on_searchButton_clicked();

    void on_reisen_Table_itemDoubleClicked(QTableWidgetItem *item);

    void on_buchung_table_itemDoubleClicked(QTableWidgetItem *item);

    void on_saveButton_clicked();

    void on_ergebnisse_clicked();

private:
    Ui::TravelAgencyUi *ui;
    std::shared_ptr<TravelAgency> travelagency;
    std::shared_ptr<BuchungsDetails> buchungsDetails;
    QMessageBox msgBox;
    std::unique_ptr<Check> check;
    std::unique_ptr<Results> results;
};
#endif // TRAVELAGENCYUI_H
