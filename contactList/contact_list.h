#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring> // Added for C-string functions
using namespace std;

class ContactList {

private:
    class Contact {
    public:
        char firstName[20];
        char lastName[20];
        char countryCode[5];
        char phone_number[15];
        Contact* prev;
        Contact* next;

        Contact();
        Contact(const char* firstName, const char* lastName, const char* countryCode, const char* phone_number);
    };
    typedef Contact* NodePointer;

public:
    ContactList();
    ~ContactList();
    //void addContact();
    void addContact(const char* firstName, const char* lastName, const char* countryCode, const char* localNumber);
    void addContactInput();
    void removeContact(const char* firstName, const char* lastName);
    void editContact(const char* targetFName, const char* targetLName);
    void displayContacts();
    void saveToFile();
    void saveToFileNOapp();
    void loadFromFile();

    void searchByFullName(const char* firstName, const char* lastName);
    void searchByFirstName(const char* firstName);
    void searchByLastName(const char* lastName);
    void search();
    //void sortContacts();
    //int compareNames(const string& FName1, const string& LName1, const string& FName2, const string& LName2);
    //void swapContacts(Contact* contact1, Contact* contact2);
    bool isDuplicate(const char* firstName, const char* lastName, const char* countryCode, const char* phoneNumber) const;
    void clearContacts();

private:
    NodePointer head;
    NodePointer tail;
};

#endif