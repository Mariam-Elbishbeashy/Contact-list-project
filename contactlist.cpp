#include "contactlist.h"
#include "addcontact.h"
#include "./ui_contactlist.h"
#include "ui_addcontact.h"
#include <QMessageBox>
#include"contactinfo.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_contactinfo.h"

contactList_ *contact=new contactList_;

const QString default_filename = "contacts.dat";

ContactList::ContactList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ContactList), addContactWindow(nullptr)
{
    ui->setupUi(this);
    connect(ui->addContactButton, SIGNAL(clicked()), this, SLOT(onAddContactClicked()));
    connect(ui->editContactButton, SIGNAL(clicked()), this, SLOT(onEditContactClicked()));
    connect(ui->removeContactButton, SIGNAL(clicked()), this, SLOT(onRemoveContactClicked()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(onSearchClicked()));
    connect(ui->saveToFileButton, SIGNAL(clicked()), this, SLOT(onSaveToFileClicked()));
    connect(ui->loadFromFileButton, SIGNAL(clicked()), this, SLOT(onLoadFromFileClicked()));
    connect(addContactWindow, &addContact::finished, this, &ContactList::onAddContactWindowClosed);
    connect(ui->saveToFileButton, &QPushButton::clicked, this, &ContactList::onSaveToFileClicked);
    connect(ui->loadFromFileButton, &QPushButton::clicked, this, &ContactList::onLoadFromFileClicked);

    // Add this line to the ContactList constructor in contactlist.cpp
    connect(ui->listWidget, &QListWidget::itemClicked, this, &ContactList::onListItemClicked);

    onLoadFromFileClicked();


}

ContactList::~ContactList()
{
    delete ui;
}
void ContactList::onAddContactClicked() {
    if (!addContactWindow)
    {
       addContactWindow = new addContact(this);
     connect(addContactWindow, &addContact::finished, this, &ContactList::onAddContactWindowClosed);
       connect(addContactWindow, &addContact::finished, this, [this](int result)
        {

            Q_UNUSED(result);
            delete addContactWindow;
            addContactWindow = nullptr;
        });
    }


    addContactWindow->show();
}

void ContactList::onAddContactWindowClosed() {

    QString firstName = addContactWindow->ui->lineEdit->text();
    QByteArray firstNameByteArray = firstName.toLocal8Bit();
    const char* firstNameCharArray = firstNameByteArray.data();

    QString lastName = addContactWindow->ui->lineEdit_2->text();
    QByteArray lastNameByteArray = lastName.toLocal8Bit();
    const char* lastNameCharArray = lastNameByteArray.data();

    QString countryCode = addContactWindow->ui->comboBox->currentText();
    QByteArray countryCodeBytes = countryCode.toLocal8Bit();
    const char* countryCodeCharArray = countryCodeBytes.constData();

    QString phoneNumber = addContactWindow->ui->lineEdit_3->text();
    QByteArray phoneNumberBytes = phoneNumber.toLocal8Bit();
    const char* phoneNumberCharArray = phoneNumberBytes.constData();

    QString nameInfo = QString("- %1 %2\n").arg(firstName, lastName);
    ui->listWidget->addItem(nameInfo);

    // Store both the name and phone number as a custom data in the item
    QString contactInfo = QString("%1\nPhone Number: %2%3").arg(nameInfo, countryCode, phoneNumber);
    QListWidgetItem *item = ui->listWidget->item(ui->listWidget->count() - 1);
    item->setData(Qt::UserRole, contactInfo);

    ui->listWidget->sortItems();

    contact->addContact(firstNameByteArray,lastNameCharArray,countryCodeCharArray,phoneNumberCharArray);
}

void ContactList::onListItemClicked(QListWidgetItem *item) {
    if (item) {
       // Retrieve the custom data containing both name and phone number
       QString contactInfo = item->data(Qt::UserRole).toString();

       QStringList contactDetails = contactInfo.split("\n", Qt::SkipEmptyParts);
       if (contactDetails.size() >= 2) {
           QStringList nameParts = contactDetails[0].split(" ");
           if (nameParts.size() >= 3) {
               QString firstName = nameParts[1];
               QString lastName = nameParts[2];

               contactinfo *contactInfoForm = new contactinfo(this);
               contactInfoForm->ui->lineEdit->setText(firstName);
               contactInfoForm->ui->lineEdit_2->setText(lastName);

               QStringList phoneParts = contactDetails[1].split("Phone Number: ");
               if (phoneParts.size() >= 2) {
                   QString countryCode = phoneParts[1].left(2); // Assuming country code length is 2
                   QString phoneNumber = phoneParts[1].mid(2); // Assuming country code length is 2

                   // Combine country code and phone number
                   QString combinedPhoneNumber = countryCode + phoneNumber;

                   // Set combined phone number in lineEdit_4
                   contactInfoForm->ui->lineEdit_4->setText(combinedPhoneNumber);
                   contactInfoForm->show();
                   return;
               }
           }
       }
       // Handling if data extraction fails or is incorrect
       QMessageBox::warning(this, "Error", "Invalid contact information");
    }
}


void ContactList::onEditContactClicked() {

}

void ContactList::onRemoveContactClicked() {

}

void ContactList::onSearchClicked() {

}

void ContactList::onSaveToFileClicked() {
    QString filename = QFileDialog::getSaveFileName(this, "Save File", default_filename, "Binary Files (.dat);;All Files ()");

    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)) {
            QDataStream out(&file);

            for (int i = 0; i < ui->listWidget->count(); ++i) {
                QListWidgetItem* item = ui->listWidget->item(i);
                QString contactInfo = item->data(Qt::UserRole).toString();
                out << contactInfo;
            }

            file.close();
            QMessageBox::information(this, "Save File", "Contacts saved successfully.");
        } else {
            QMessageBox::critical(this, "Error", "Unable to open file for writing.");
        }
    }
}

void ContactList::onLoadFromFileClicked() {
    QString filename = QFileDialog::getOpenFileName(this, "Open File", default_filename, "Binary Files (.dat);;All Files ()");

    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);

            ui->listWidget->clear();

            while (!in.atEnd()) {
                QString contactInfo;
                in >> contactInfo;
                ui->listWidget->addItem(contactInfo);
            }

            file.close();
            QMessageBox::information(this, "Load File", "Contacts loaded successfully.");
        } else {
            QMessageBox::critical(this, "Error", "Unable to open file for reading.");
        }
    }
}

