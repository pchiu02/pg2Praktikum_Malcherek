#include "consistencycheck.h"
#include "ui_consistencycheck.h"

ConsistencyCheck::ConsistencyCheck(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConsistencyCheck)
{
    ui->setupUi(this);

    ui->reisenuberschneidungCheckBox->setChecked(true);
    ui->UeberflussigeMietwagenBuchungCheckBox->setChecked(true);
    ui->ueberflussigeHotelCheckBox->setChecked(true);
    ui->fehlenderHotelCheckBox->setChecked(true);
}

ConsistencyCheck::~ConsistencyCheck()
{
    delete ui;
}

bool ConsistencyCheck::isReisenuberschneidungChecked() const
{
    return ui->reisenuberschneidungCheckBox->isChecked();
}

bool ConsistencyCheck::isUeberflussigeMietwagenBuchungChecked() const
{
    return ui->UeberflussigeMietwagenBuchungCheckBox->isChecked();
}

bool ConsistencyCheck::isUeberflussigeHotelChecked() const
{
    return ui->ueberflussigeHotelCheckBox->isChecked();
}

bool ConsistencyCheck::isFehlenderHotelChecked() const
{
    return ui->fehlenderHotelCheckBox->isChecked();
}



