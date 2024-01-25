#ifndef RESULTS_H
#define RESULTS_H

#include <QDialog>

namespace Ui {
class Results;
}

class Results : public QDialog
{
    Q_OBJECT

public:
    explicit Results(QWidget *parent = nullptr);
    ~Results();

public slots:
    void updateTableWidget(const QString& errorType, const QString &result);

private:
    Ui::Results *ui;
};

#endif // RESULTS_H
