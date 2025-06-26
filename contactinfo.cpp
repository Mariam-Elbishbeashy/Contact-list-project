#include "contactinfo.h"
#include "ui_contactinfo.h"

contactinfo::contactinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::contactinfo)
{
    ui->setupUi(this);
}

contactinfo::~contactinfo()
{
    delete ui;
}
