#ifndef ADDCONTACT_H
#define ADDCONTACT_H

#include "contactlist_.h"
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>


namespace Ui {
class addContact;
}

class addContact : public QDialog
{
    Q_OBJECT

public:
    explicit addContact(QWidget *parent = nullptr);
    ~addContact();

    Ui::addContact *ui;

private slots:
    void onNumberButtonClicked();
    void onSpecialButtonClicked();
    void onBackButtonClicked();
    void onClearButtonClicked();
    void onAddContactClicked();
    void countryCodes();

    void on_addContact_button_clicked();

private:

    void setupCountryCodes();
};

#endif // ADDCONTACT_H
