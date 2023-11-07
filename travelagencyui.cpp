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
            msgBox.information(this, "Meldung", "File opened sucessfully");
        }catch(const std::runtime_error)

}

