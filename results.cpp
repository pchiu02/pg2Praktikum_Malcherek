#include "results.h"
#include "QtWidgets/qtablewidget.h"
#include "ui_results.h"

Results::Results(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Results)
{
    ui->setupUi(this);
}

Results::~Results()
{
    delete ui;
}

void Results::updateTableWidget(const QString &result)
{
    int row = ui->table->rowCount();
    ui->table->insertRow(row);

    QTableWidgetItem *beschreibung = new QTableWidgetItem(result);
    QTableWidgetItem* fehlerTyp = new QTableWidgetItem();
    fehlerTyp->setIcon(QIcon("MissingHotel.png"));
    ui->table->setItem(row, 0, fehlerTyp);
    ui->table->setItem(row, 1, beschreibung);
}
