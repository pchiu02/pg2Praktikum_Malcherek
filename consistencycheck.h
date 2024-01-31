#ifndef CONSISTENCYCHECK_H
#define CONSISTENCYCHECK_H

#include <QDialog>

namespace Ui {
class ConsistencyCheck;
}

class ConsistencyCheck : public QDialog
{
    Q_OBJECT

public:
    explicit ConsistencyCheck(QWidget *parent = nullptr);
    ~ConsistencyCheck();

    bool isReisenuberschneidungChecked() const;
    bool isUeberflussigeMietwagenBuchungChecked() const;
    bool isUeberflussigeHotelChecked() const;
    bool isFehlenderHotelChecked() const;

private:
    Ui::ConsistencyCheck *ui;
};
#endif // CONSISTENCYCHECK_H
