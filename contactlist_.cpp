#include "contactlist_.h"
#include <cstring>
#include <iostream>
#include <QFile>
#include <QDataStream>
#include <QDebug>

const QString default_filename = "contacts.dat";
using namespace std;

contactList_::contactList_()
:     head(nullptr),
    tail(nullptr){}

contactList_::contact::~contact()
{}

contactList_::contact::contact(const char* fName, const char* lName, const char* c, const char* phone)
    : next(nullptr)
{
    strncpy(firstName, fName, sizeof(firstName) - 1);
    firstName[sizeof(firstName) - 1] = '\0';

    strncpy(lastName, lName, sizeof(lastName) - 1);
    lastName[sizeof(lastName) - 1] = '\0';

    strncpy(phoneNumber, phone, sizeof(phoneNumber) - 1);
    phoneNumber[sizeof(phoneNumber) - 1] = '\0';

    strncpy(country, c, sizeof(country) - 1);
    country[sizeof(country) - 1] = '\0';
}

contactList_::~contactList_()
{}


void contactList_::addContact(const char* firstName, const char* lastName, const char* countryCode, const char* localNumber) {
    contact* newContact = new contact(firstName, lastName, countryCode, localNumber);

    if (!head) {
        head = newContact;
        tail = newContact;
    }
    else {
        contact* current = head;

        while (current != nullptr) {
            int nameComparison = strcmp(newContact->firstName, current->firstName);

            if (nameComparison < 0 || (nameComparison == 0 && strcmp(newContact->lastName, current->lastName) < 0)) {
                newContact->next = current;
                newContact->prev = current->prev;

                if (current->prev) {
                    current->prev->next = newContact;
                }
                else {
                    head = newContact;
                }

                current->prev = newContact;
                break;
            }

            current = current->next;
        }

        if (current == nullptr) {
            tail->next = newContact;
            newContact->prev = tail;
            tail = newContact;
        }
    }
}
void contactList_::displayContacts() {
    if (head == NULL)
        cerr << "Empty contact list." << endl;
    NodePointer ptr = head;
    while (ptr != NULL) {
        cout << ptr->firstName << " " << ptr->lastName << ": " << ptr->country << ptr->phoneNumber << endl;
        ptr = ptr->next;
    }
}
void contactList_::saveToFile() {
    QFile outFile(default_filename);

    if (outFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QDataStream dataStream(&outFile);

        NodePointer current = head;
        while (current) {

            dataStream << current->firstName << current->lastName << current->country << current->phoneNumber;

            current = current->next;
        }

        outFile.close();
    }
    else {
        //cerr
        qCritical() << "Unable to open file:" << default_filename;
    }
}
void contactList_::saveToFileNOapp() {
    QFile outFile(default_filename);

    if (outFile.open(QIODevice::WriteOnly)) {
        QDataStream dataStream(&outFile);

        NodePointer current = head;
        while (current) {

            dataStream << current->firstName << current->lastName << current->country << current->phoneNumber;

            current = current->next;
        }

        outFile.close();
    }
    else {
        qCritical() << "Unable to open file:" << default_filename;
    }
}
void contactList_::loadFromFile() {
    QFile inFile(default_filename);

    if (inFile.open(QIODevice::ReadOnly)) {
        QDataStream dataStream(&inFile);

        while (!dataStream.atEnd()) {
            // Read the contact data from the file using QDataStream
            QString firstName, lastName, countryCode, phoneNumber;
            dataStream >> firstName >> lastName >> countryCode >> phoneNumber;

            // Add the contact to the list
            NodePointer newContact = new contact(firstName.toUtf8().constData(), lastName.toUtf8().constData(),
                                                 countryCode.toUtf8().constData(), phoneNumber.toUtf8().constData());

            if (!head) {
                head = newContact;
                tail = newContact;
            } else {
                tail->next = newContact;
                newContact->prev = tail;
                tail = newContact;
            }
        }

        inFile.close();
    } else {
        qCritical() << "Unable to open file:" << default_filename;
    }
}
