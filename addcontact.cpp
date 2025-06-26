#include "addcontact.h" // Assuming the header file for your addContact class is named "addcontact.h"
#include "ui_addcontact.h"
#include <QMessageBox>

addContact::addContact(QWidget *parent)
    : QDialog(parent), ui(new Ui::addContact)
{
    ui->setupUi(this);


    connect(ui->numberOne_button, SIGNAL(clicked()), this, SLOT(onNumberButtonClicked()));
    connect(ui->numberTwo_button, SIGNAL(clicked()), this, SLOT(onNumberButtonClicked()));
    connect(ui->numberThree_button, SIGNAL(clicked()), this, SLOT(onNumberButtonClicked()));
    connect(ui->numberFour_button, SIGNAL(clicked()), this, SLOT(onNumberButtonClicked()));
    connect(ui->numberFive_button, SIGNAL(clicked()), this, SLOT(onNumberButtonClicked()));
    connect(ui->numberSix_button, SIGNAL(clicked()), this, SLOT(onNumberButtonClicked()));
    connect(ui->numberSeven_button, SIGNAL(clicked()), this, SLOT(onNumberButtonClicked()));
    connect(ui->numberEight_button, SIGNAL(clicked()), this, SLOT(onNumberButtonClicked()));
    connect(ui->numberNine_button, SIGNAL(clicked()), this, SLOT(onNumberButtonClicked()));
    connect(ui->numberZero_button, SIGNAL(clicked()), this, SLOT(onNumberButtonClicked()));


    connect(ui->star_button, SIGNAL(clicked()), this, SLOT(onSpecialButtonClicked()));
    connect(ui->hashtag_button, SIGNAL(clicked()), this, SLOT(onSpecialButtonClicked()));


    connect(ui->backToContactList_button, SIGNAL(clicked()), this, SLOT(onBackButtonClicked()));

    connect(ui->clear_button, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));

    connect(ui->addContact_button, SIGNAL(clicked()), this, SLOT(onAddContactClicked()));

    countryCodes();
}

addContact::~addContact()
{
    delete ui;
}

// Slot for handling number button clicks
void addContact::onNumberButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString buttonText = button->text();
        ui->lineEdit_3->insert(buttonText);  // Insert the clicked button's text into the phone number line edit
    }
}


void addContact::onSpecialButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString buttonText = button->text();

        ui->lineEdit_3->insert(buttonText);
    }
}


void addContact::onBackButtonClicked() {

    this->close();
}

void addContact::onClearButtonClicked() {

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->comboBox->setCurrentIndex(0);
}

void addContact::onAddContactClicked() {


    QString firstName = ui->lineEdit->text();
    QString lastName = ui->lineEdit_2->text();
    QString phoneNumber = ui->lineEdit_3->text();

    // Check if either first name or last name is empty
    if (firstName.isEmpty() || lastName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter both first name and last name.");
        return;  // Stop further processing
    }

    // Check if phone number is empty
    if (phoneNumber.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a phone number.");
        return;  // Stop further processing
    }

    // If all checks passed, show success message and close the window
    QMessageBox::information(this, "Success", "Contact added successfully!");
    this->close();
}


void addContact::countryCodes() {

    setupCountryCodes();
}

void addContact::setupCountryCodes() {

    QStringList countryCodes;
    countryCodes <<"+1" << "+7" << "+20" << "+27" << "+30" << "+31" << "+32" << "+33" << "+34" << "+36"
                 << "+39" << "+40" << "+41" << "+43" << "+44" << "+45" << "+46" << "+47" << "+48" << "+49"
                 << "+51" << "+52" << "+53" << "+54" << "+55" << "+56" << "+57" << "+58" << "+60" << "+61"
                 << "+62" << "+63" << "+64" << "+65" << "+66" << "+81" << "+82" << "+84" << "+86" << "+90"
                 << "+91" << "+92" << "+93" << "+94" << "+95" << "+98" << "+212" << "+213" << "+216" << "+218"
                 << "+220" << "+221" << "+222" << "+223" << "+224" << "+225" << "+226" << "+227" << "+228" << "+229"
                 << "+230" << "+231" << "+232" << "+233" << "+234" << "+235" << "+236" << "+237" << "+238" << "+239"
                 << "+240" << "+241" << "+242" << "+243" << "+244" << "+245" << "+246" << "+248" << "+249" << "+250"
                 << "+251" << "+252" << "+253" << "+254" << "+255" << "+256" << "+257" << "+258" << "+260" << "+261"
                 << "+262" << "+263" << "+264" << "+265" << "+266" << "+267" << "+268" << "+269" << "+290" << "+291"
                 << "+297" << "+298" << "+299" << "+350" << "+351" << "+352" << "+353" << "+354" << "+355" << "+356"
                 << "+357" << "+358" << "+359" << "+370" << "+371" << "+372" << "+373" << "+374" << "+375" << "+376"
                 << "+377" << "+378" << "+380" << "+381" << "+382" << "+383" << "+385" << "+386" << "+387" << "+389"
                 << "+420" << "+421" << "+423" << "+500" << "+501" << "+502" << "+503" << "+504" << "+505" << "+506"
                 << "+507" << "+508" << "+509" << "+590" << "+591" << "+592" << "+593" << "+594" << "+595" << "+596"
                 << "+597" << "+598" << "+599" << "+670" << "+672" << "+673" << "+674" << "+675" << "+676" << "+677"
                 << "+678" << "+679" << "+680" << "+681" << "+682" << "+683" << "+685" << "+686" << "+687" << "+688"
                 << "+689" << "+690" << "+691" << "+692" << "+850" << "+852" << "+853" << "+855" << "+856" << "+880"
                 << "+886" << "+960" << "+961" << "+962" << "+963" << "+964" << "+965" << "+966" << "+967" << "+968"
                 << "+970" << "+971" << "+972" << "+973" << "+974" << "+975" << "+976" << "+977" << "+992" << "+993"
                 << "+994" << "+995" << "+996" << "+998";


    ui->comboBox->addItems(countryCodes);
}

void addContact::on_addContact_button_clicked()
{

}

