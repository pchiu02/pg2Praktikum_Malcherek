#include "travelagencyui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TravelAgencyUi w;
    w.show();
    return a.exec();
}
