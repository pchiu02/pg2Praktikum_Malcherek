#include "suchendialog.h"
#include "ui_suchendialog.h"

SuchenDialog::SuchenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SuchenDialog)
{
    ui->setupUi(this);
}

SuchenDialog::~SuchenDialog()
{
    delete ui;
}

int SuchenDialog::getId() const{
    return ui->id_Box->value();
}

void SuchenDialog::on_buttonBox_accepted()
{
    int id = getId();
    emit suchenClicked();
}

