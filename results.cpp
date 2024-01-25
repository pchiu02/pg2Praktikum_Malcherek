#include "results.h"
#include "QtWidgets/qtablewidget.h"
#include "ui_results.h"

Results::Results(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Results)
{
    ui->setupUi(this);
    ui->table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
}

Results::~Results()
{
    delete ui;
}

void Results::updateTableWidget(const QString &errorType, const QString &result)
{
    int row = ui->table->rowCount();
    ui->table->insertRow(row);

    QTableWidgetItem *beschreibung = new QTableWidgetItem(result);
    QTableWidgetItem* fehlerTypItem = new QTableWidgetItem();
    fehlerTypItem->setText(errorType);
    if(errorType == "Missing Hotel"){
        fehlerTypItem->setIcon(QIcon("MissingHotel.png"));
    }else if(errorType == "Overlapping Hotel"){
        fehlerTypItem->setIcon(QIcon("overlappingHotel.png"));
    }else if(errorType == "Overlapping Cars"){
        fehlerTypItem->setIcon(QIcon("overlappingCar.png"));
    }
    ui->table->setItem(row, 0, fehlerTypItem);
    ui->table->setItem(row, 1, beschreibung);
}
