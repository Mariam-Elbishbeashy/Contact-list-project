#include "Contact_list.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <regex>
using namespace std;

const string default_filename = "contact.dat";

ContactList::Contact::Contact()
    :prev(nullptr), next(nullptr) {
    // Initialize members as needed
    // For example:
    firstName[0] = '\0';
    lastName[0] = '\0';
    countryCode[0] = '\0';
    phone_number[0] = '\0';
}


ContactList::Contact::Contact(const char* fName, const char* lName, const char* cCode, const char* pNumber)
    :prev(nullptr), next(nullptr) {
    // Initialize members as needed
    // For example:
    strncpy_s(firstName, fName, sizeof(firstName) - 1);
    firstName[sizeof(firstName) - 1] = '\0';  // Ensure null-terminated
    strncpy_s(lastName, lName, sizeof(lastName) - 1);
    lastName[sizeof(lastName) - 1] = '\0';    // Ensure null-terminated
    strncpy_s(countryCode, cCode, sizeof(countryCode) - 1);
    countryCode[sizeof(countryCode) - 1] = '\0';  // Ensure null-terminated
    strncpy_s(phone_number, pNumber, sizeof(phone_number) - 1);
    phone_number[sizeof(phone_number) - 1] = '\0';  // Ensure null-terminated
}


ContactList::ContactList()
    : head(nullptr), tail(nullptr)
{}

ContactList::~ContactList() {
    while (head != NULL)
    {
        NodePointer ptr = head;
        head = head->next;
        delete ptr;
    }
    tail = nullptr;
}


void ContactList::addContact(const char* firstName, const char* lastName, const char* countryCode, const char* localNumber) {
    Contact* newContact = new Contact(firstName, lastName, countryCode, localNumber);

    if (!head) {
        head = newContact;
        tail = newContact;
    }
    else {
        Contact* current = head;

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

void ContactList::addContactInput() {
    int choice = 0;

    do {
        char firstName[10], lastName[10], countryCode[5], phoneNo[15];

        cout << "Enter the first name (up to 10 characters): ";
        cin.getline(firstName, sizeof(firstName));

        cout << "Enter the last name (up to 10 characters): ";
        cin.getline(lastName, sizeof(lastName));

        while (true) {
            cout << "Enter the country code and phone number (e.g., +123 4567890123)\nPlease enter a space after entering the country code: ";
            cin.getline(countryCode, sizeof(countryCode), ' ');
            cin.getline(phoneNo, sizeof(phoneNo));

            if (strlen(phoneNo) == 10 && strlen(countryCode) <= 4 && countryCode[0] == '+') {
                break;
            }
            else {
                cout << "Invalid phone number or country code. Please try again." << endl;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        Contact* current = head;
        bool contactExists = false;

        while (current != nullptr) {
            if (strcmp(current->firstName, firstName) == 0 &&
                strcmp(current->lastName, lastName) == 0 &&
                strcmp(current->countryCode, countryCode) == 0 &&
                strcmp(current->phone_number, phoneNo) == 0) {
                contactExists = true;
                break;
            }

            current = current->next;
        }

        if (contactExists) {
            cout << "Contact already exists. Are you sure you want to add it again?\n1. Yes\n2. No\nEnter your choice: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice != 1) {


                continue;
            }
        }

        addContact(firstName, lastName, countryCode, phoneNo);

        cout << "Contact added successfully!" << endl;

        cout << "Do you want to add another contact?\n1. Yes\n2. No\nEnter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (choice == 1);
}

void ContactList::removeContact(const char* FName, const char* LName) {
    NodePointer temp = head;

    if (head == nullptr) {
        cerr << "List is empty" << endl;
        return;
    }

    // Check if the first node is the one to be removed
    if (strcmp(head->firstName, FName) == 0 && strcmp(head->lastName, LName) == 0) {
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
        return;
    }
    // Traverse the list to find the node to be removed
    while (temp != nullptr) {
        if (strcmp(temp->firstName, FName) == 0 && strcmp(temp->lastName, LName) == 0) {
            if (temp->prev != nullptr) {
                temp->prev->next = temp->next;
            }
            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }
            if (temp == tail) {
                tail = tail->prev;
                if (tail != nullptr) {
                    tail->next = nullptr;
                }
            }

            delete temp;
            cout << "Contact removed successfully!" << endl;
            return;
        }
        temp = temp->next;
    }

    cerr << "Name not found" << endl;
}

void ContactList::editContact(const char* targetFName, const char* targetLName) {
    NodePointer current = head;
    NodePointer ptr = nullptr;

    while (current != nullptr) {
        if (strcmp(current->firstName, targetFName) == 0 && strcmp(current->lastName, targetLName) == 0) {
            ptr = current;
            break;
        }

        current = current->next;
    }

    if (ptr != nullptr) {
        cout << "What do you want to edit?" << endl;
        int choice;
        cout << "1. Edit contact name" << endl;
        cout << "2. Edit phone number" << endl;
        cout << "3. Edit both" << endl;
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Do you want to edit first name or last name?" << endl;
            int choice2;
            cout << "1. Edit first name" << endl;
            cout << "2. Edit last name" << endl;
            cout << "3. Edit both" << endl;
            cout << "Your choice: ";
            cin >> choice2;

            switch (choice2) {
            case 1: {
                char newFirstName[20];
                cout << "Enter the new first name: ";
                cin.ignore(); // Ignore the newline character in the buffer
                cin.getline(newFirstName, sizeof(newFirstName));
                strncpy_s(ptr->firstName, newFirstName, sizeof(ptr->firstName) - 1);
                ptr->firstName[sizeof(ptr->firstName) - 1] = '\0';
                break;
            }
            case 2: {
                char newLastName[20];
                cout << "Enter the new last name: ";
                cin.ignore();
                cin.getline(newLastName, sizeof(newLastName));
                strncpy_s(ptr->lastName, newLastName, sizeof(ptr->lastName) - 1);
                ptr->lastName[sizeof(ptr->lastName) - 1] = '\0';
                break;
            }
            case 3: {
                char newFirstName[20], newLastName[20];
                cout << "Enter the new first name: ";
                cin.ignore();
                cin.getline(newFirstName, sizeof(newFirstName));
                strncpy_s(ptr->firstName, newFirstName, sizeof(ptr->firstName) - 1);
                ptr->firstName[sizeof(ptr->firstName) - 1] = '\0';

                cout << "Enter the new last name: ";
                cin.getline(newLastName, sizeof(newLastName));
                strncpy_s(ptr->lastName, newLastName, sizeof(ptr->lastName) - 1);
                ptr->lastName[sizeof(ptr->lastName) - 1] = '\0';
                break;
            }
            default:
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
                break;
            }
            break;
        }
        case 2: {
            char newPhoneNumber[12], newcountryCode[5];
            while (true) {
                cout << "Enter the country code and the new phone number (e.g., +123 4567890123)\nPlease enter a space after entering the country code: ";
                cin.getline(newcountryCode, sizeof(newcountryCode), ' ');
                cin.getline(newPhoneNumber, sizeof(newPhoneNumber));

                if (strlen(newPhoneNumber) == 10 && strlen(newcountryCode) <= 4 && newcountryCode[0] == '+') {
                    break;
                }
                else {
                    cout << "Invalid phone number or country code. Please try again." << endl;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            strncpy_s(ptr->phone_number, newPhoneNumber, sizeof(ptr->phone_number) - 1);
            ptr->phone_number[sizeof(ptr->phone_number) - 1] = '\0';
            strncpy_s(ptr->countryCode, newcountryCode, sizeof(ptr->countryCode) - 1);
            ptr->countryCode[sizeof(ptr->countryCode) - 1] = '\0';

            break;
        }
        case 3: {
            cout << "Do you want to edit first name or last name?" << endl;
            int choice2;
            cout << "1. Edit first name" << endl;
            cout << "2. Edit last name" << endl;
            cout << "3. Edit both" << endl;
            cout << "Your choice: ";
            cin >> choice2;

            switch (choice2) {
            case 1: {
                char newFirstName[20];
                cout << "Enter the new first name: ";
                cin.ignore();
                cin.getline(newFirstName, sizeof(newFirstName));
                strncpy_s(ptr->firstName, newFirstName, sizeof(ptr->firstName) - 1);
                ptr->firstName[sizeof(ptr->firstName) - 1] = '\0';
                break;
            }
            case 2: {
                char newLastName[20];
                cout << "Enter the new last name: ";
                cin.ignore();
                cin.getline(newLastName, sizeof(newLastName));
                strncpy_s(ptr->lastName, newLastName, sizeof(ptr->lastName) - 1);
                ptr->lastName[sizeof(ptr->lastName) - 1] = '\0';
                break;
            }
            case 3: {
                char newFirstName[20], newLastName[20];
                cout << "Enter the new first name: ";
                cin.ignore();
                cin.getline(newFirstName, sizeof(newFirstName));
                strncpy_s(ptr->firstName, newFirstName, sizeof(ptr->firstName) - 1);
                ptr->firstName[sizeof(ptr->firstName) - 1] = '\0';

                cout << "Enter the new last name: ";
                cin.getline(newLastName, sizeof(newLastName));
                strncpy_s(ptr->lastName, newLastName, sizeof(ptr->lastName) - 1);
                ptr->lastName[sizeof(ptr->lastName) - 1] = '\0';
                break;
            }
            default:
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
                break;
            }
            char newPhoneNumber[12], newcountryCode[5];
            while (true) {
                cout << "Enter the country code and the new phone number (e.g., +123 4567890123)\nPlease enter a space after entering the country code: ";
                cin.getline(newcountryCode, sizeof(newcountryCode), ' ');
                cin.getline(newPhoneNumber, sizeof(newPhoneNumber));

                if (strlen(newPhoneNumber) == 10 && strlen(newcountryCode) <= 4 && newcountryCode[0] == '+') {
                    break;
                }
                else {
                    cout << "Invalid phone number or country code. Please try again." << endl;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            strncpy_s(ptr->phone_number, newPhoneNumber, sizeof(ptr->phone_number) - 1);
            ptr->phone_number[sizeof(ptr->phone_number) - 1] = '\0';
            strncpy_s(ptr->countryCode, newcountryCode, sizeof(ptr->countryCode) - 1);
            ptr->countryCode[sizeof(ptr->countryCode) - 1] = '\0';
            break;
        }
        default:
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
            break;
        }
    }
    else {
        cerr << "Contact not found." << endl;
    }
}
void ContactList::displayContacts() {
    if (head == NULL)
        cerr << "Empty contact list." << endl;
    NodePointer ptr = head;
    while (ptr != NULL) {
        cout << ptr->firstName << " " << ptr->lastName << ": " << ptr->countryCode << ptr->phone_number << endl;
        ptr = ptr->next;
    }
}
void ContactList::saveToFile() {
    ofstream outFile(default_filename, ios::binary | ios::app);

    if (outFile.is_open()) {
        NodePointer current = head;
        while (current) {
            outFile.write(reinterpret_cast<const char*>(current), sizeof(Contact));

            current = current->next;
        }
        outFile.close();
    }
    else {
        cerr << "Unable to open file: " << default_filename << endl;
    }
}

//void ContactList::saveToFileapp() {
//    ofstream outFile(default_filename, ios::binary | ios::app);
//
//    if (outFile.is_open()) {
//        NodePointer current = head;
//        while (current) {
//            outFile.write(reinterpret_cast<const char*>(current), sizeof(Contact));
//
//            current = current->next;
//        }
//        outFile.close();
//    }
//    else {
//        cerr << "Unable to open file: " << default_filename << endl;
//    }
//}

void ContactList::saveToFileNOapp() {
    ofstream outFile(default_filename, ios::binary);

    if (outFile.is_open()) {
        NodePointer current = head;
        while (current) {
            outFile.write(reinterpret_cast<const char*>(current), sizeof(Contact));

            current = current->next;
        }
        outFile.close();
    }
    else {
        cerr << "Unable to open file: " << default_filename << endl;
    }
}
void ContactList::loadFromFile() {
    ifstream inFile(default_filename, ios::binary);
    if (inFile.is_open()) {
        while (inFile.peek() != EOF) {
            // Read the contact data from the file in binary format
            NodePointer newContact = new Contact();
            inFile.read(reinterpret_cast<char*>(newContact), sizeof(Contact));

            // Add the contact to the list
            if (!head) {
                head = newContact;
                tail = newContact;
            }
            else {
                tail->next = newContact;
                newContact->prev = tail;
                tail = newContact;
            }
        }
        inFile.close();
    }
    else {
        cerr << "Unable to open file: " << default_filename << endl;
    }
}


//void ContactList::searchByFirstName(const char* firstName) {
//    Contact* current = head;
//    bool found = false;
//
//    while (current != nullptr) {
//        if (strcmp(current->firstName, firstName) == 0 || strcmp(current->lastName, firstName) == 0) {
//            cout << "Name: " << current->firstName << " " << current->lastName << "\nPhone: " << current -> countryCode <<" "<<current->phone_number << endl;
//            found = true;
//        }
//
//        current = current->next;
//    }
//
//    if (!found) {
//        cout << "No contacts found that name '"<<firstName<<"'" << endl;
//    }
//}
//
//
//void ContactList::searchByFullName(const char* firstName, const char* lastName) {
//    Contact* current = head;
//    bool found = false;
//
//    while (current != nullptr) {
//        if (strcmp(current->firstName, firstName) == 0 && strcmp(current->lastName, lastName) == 0) {
//            cout << "Name: " << current->firstName << " " << current->lastName << "\nPhone: " <<current -> countryCode<<" "<< current->phone_number << endl;
//            found = true;
//        }
//
//        current = current->next;
//    }
//
//    if (!found) {
//        cout << "No contact found with the name '"<<firstName<<" "<<lastName<<"'" << endl;
//    }
//}
//
//
//void ContactList::searchByLastName(const char* lastName) {
//    Contact* current = head;
//    bool found = false;
//
//    while (current != nullptr) {
//        if (strcmp(current->lastName, lastName) == 0) {
//            cout << "Name: " << current->firstName << " " << current->lastName << "\nPhone: " <<current -> countryCode <<" "<< current->phone_number << endl;
//            found = true;
//        }
//
//        current = current->next;
//    }
//
//    if (!found) {
//        cout << "No contacts found with the last name '"<<lastName<<"'" << endl;
//    }
//}

void ContactList::searchByFirstName(const char* firstName) {
    Contact* current = head;
    bool found = false;
    regex firstNameRegex(firstName, regex_constants::icase);

    while (current != nullptr) {
        if (regex_search(current->firstName, firstNameRegex) ||
            regex_search(current->lastName, firstNameRegex)) {
            cout << "Name: " << current->firstName << " " << current->lastName
                << "\nPhone: " << current->countryCode << " " << current->phone_number << endl;
            found = true;
        }

        current = current->next;
    }

    if (!found) {
        cout << "No contacts found that match the name '" << firstName << "'" << endl;
    }
}

void ContactList::searchByFullName(const char* firstName, const char* lastName) {
    Contact* current = head;
    bool found = false;
    regex firstNameRegex(firstName, regex_constants::icase);
    regex lastNameRegex(lastName, regex_constants::icase);

    while (current != nullptr) {
        if (regex_search(current->firstName, firstNameRegex) &&
            regex_search(current->lastName, lastNameRegex)) {
            cout << "Name: " << current->firstName << " " << current->lastName
                << "\nPhone: " << current->countryCode << " " << current->phone_number << endl;
            found = true;
        }

        current = current->next;
    }

    if (!found) {
        cout << "No contact found with the name '" << firstName << " " << lastName << "'" << endl;
    }
}

void ContactList::searchByLastName(const char* lastName) {
    Contact* current = head;
    bool found = false;
    regex lastNameRegex(lastName, regex_constants::icase);

    while (current != nullptr) {
        if (regex_search(current->lastName, lastNameRegex)) {
            cout << "Name: " << current->firstName << " " << current->lastName
                << "\nPhone: " << current->countryCode << " " << current->phone_number << endl;
            found = true;
        }

        current = current->next;
    }

    if (!found) {
        cout << "No contacts found with the last name '" << lastName << "'" << endl;
    }
}


void ContactList::search() {
    int option, searchChoice;
    char firstName[10];
    char lastName[10];

    do {
        cout << "Search by:\n1. First Name and Last Name\n2. First Name Only\n3. Last Name Only\n4. Exit\nEnter your choice: ";
        cin >> option;

        switch (option) {
        case 1:
            cout << "Enter the first name: ";
            cin >> firstName;
            cout << "Enter the last name: ";
            cin >> lastName;
            searchByFullName(firstName, lastName);
            break;
        case 2:
            cout << "Enter the first name: ";
            cin >> firstName;
            searchByFirstName(firstName);
            break;
        case 3:
            cout << "Enter the last name: ";
            cin >> lastName;
            searchByLastName(lastName);
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice." << endl;
        }

        cout << "Do you want to search again?\n1. Yes\n2. No\nEnter your choice: ";
        cin >> searchChoice;

    } while (searchChoice == 1);
}

bool ContactList::isDuplicate(const char* firstName, const char* lastName, const char* countryCode, const char* phoneNumber) const {
    NodePointer current = head;
    while (current != nullptr) {
        //strcmp function is used for comparing
        if (strcmp(current->firstName, firstName) == 0 && strcmp(current->lastName, lastName) == 0 &&
            strcmp(current->countryCode, countryCode) == 0 && strcmp(current->phone_number, phoneNumber) == 0) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void ContactList::clearContacts() {
    ofstream outFile(default_filename, ios::binary | ios::trunc);

    if (outFile.is_open()) {
        outFile.close();
        cout << "File cleared successfully." << endl;
    }
    else {
        cerr << "Unable to open file: " << default_filename << endl;
    }
}