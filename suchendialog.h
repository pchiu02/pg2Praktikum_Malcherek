#ifndef SUCHENDIALOG_H
#define SUCHENDIALOG_H

#include <QDialog>

namespace Ui {
class SuchenDialog;
}

class SuchenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SuchenDialog(QWidget *parent = nullptr);
    ~SuchenDialog();
    int getId() const;

signals:
    void suchenClicked();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SuchenDialog *ui;
};

#endif // SUCHENDIALOG_H
