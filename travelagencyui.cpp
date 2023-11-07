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

