#include "contact_list.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib> // for system clear
#include <fstream>

using namespace std;

const string default_filename = "contacts.txt";

int main() {
    ContactList contactList;
    bool contactsLoaded = false;

    if (!contactsLoaded) {
        contactList.loadFromFile();
        contactsLoaded = true;
        cout << "Contacts loaded successfully.\n";
    }

    while (true) {
        system("cls"); // For Windows, use "clear" for Mac

        cout << "CONTACT LIST PROJECT" << endl;
        cout << "Represented by: Mariam, Sondos, Sama, Laura, Mahmoud\n\n";

        cout << "------------------------------------------------------" << endl;
        cout << "MENU:\n";
        cout << "1. Add Contact\n";
        cout << "2. Remove Contact\n";
        cout << "3. Edit Contact\n";
        cout << "4. Display Contacts\n";
        cout << "5. Search Contact\n";
        cout << "6. Clear Contacts\n";
        cout << "0. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // for input strings

        switch (choice) {
        case 1: {
            contactList.addContactInput();
            contactList.saveToFile();
            break;
        }

        case 2: {
            char firstName[10];
            char lastName[10];
            cout << "To remove: ";
            cout << "Enter contact first name: ";
            cin.getline(firstName, sizeof(firstName));
            cout << "Enter contact last name: ";
            cin.getline(lastName, sizeof(lastName));
            contactList.removeContact(firstName, lastName);
            contactList.saveToFileNOapp();
            break;
        }

        case 3: {

            char targetFName[20], targetLName[20];
            cout << "To edit: " << endl;
            cout << "Enter the contact first name: ";
            cin >> targetFName;
            cout << "Enter the contact last name: ";
            cin >> targetLName;
            contactList.editContact(targetFName, targetLName);
            contactList.saveToFileNOapp();
            break;
        }

        case 4:
            contactList.displayContacts();
            break;

        case 5: {
            contactList.search();
            break;
        }

        case 6: {
            contactList.clearContacts();
            cout << "Contacts cleared successfully.\n";
            break;
        }

        case 0: {
            cout << "Exiting program.\n";
            return 0;
        }

        default:
            cout << "Invalid choice. Please enter a number between 0 and 6.\n";
        }

        cout << "Press Enter to continue...";
        cin.get();
    }

    return 0;
}