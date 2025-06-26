#ifndef CONTACTINFO_H
#define CONTACTINFO_H

#include <QDialog>

namespace Ui {
class contactinfo;
}

class contactinfo : public QDialog
{
    Q_OBJECT

public:
    explicit contactinfo(QWidget *parent = nullptr);
    ~contactinfo();
    Ui::contactinfo *ui;

private:

};

#endif // CONTACTINFO_H
