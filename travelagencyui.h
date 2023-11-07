#ifndef TRAVELAGENCYUI_H
#define TRAVELAGENCYUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TravelAgencyUi; }
QT_END_NAMESPACE

class TravelAgencyUi : public QMainWindow
{
    Q_OBJECT

public:
    TravelAgencyUi(QWidget *parent = nullptr);
    ~TravelAgencyUi();

private:
    Ui::TravelAgencyUi *ui;
};
#endif // TRAVELAGENCYUI_H
