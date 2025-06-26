#ifndef CONTACTLIST__H
#define CONTACTLIST__H
class contactList_
{
private:
    class contact
    {
    public:
        char firstName[20];
        char lastName[20];
        char phoneNumber[12];
        char country[5];      // Assuming country code like "+20"
        contact* prev;
        contact* next;

        contact(const char* fName, const char* lName, const char* phone, const char* c);
        ~contact();
    };
public:
    typedef contact* NodePointer;
    contactList_();
    ~contactList_();

    void addContact(const char* firstName, const char* lastName, const char* countryCode, const char* localNumber);
    void displayContacts();
    NodePointer head;
    NodePointer tail;

private:
    void saveToFile();
    void loadFromFile();
    void saveToFileNOapp();

};

#endif // CONTACTLIST__H
