#ifndef CONTACTLIST_H
#define CONTACTLIST_H

#include <QMainWindow>
#include "addcontact.h"
#include <QDialog>
#include "contactlist_.h"
#include "qlistwidget.h"
#include"contactinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ContactList;
}
QT_END_NAMESPACE

class ContactList : public QMainWindow
{
    Q_OBJECT


public:
    ContactList(QWidget *parent = nullptr);
    ~ContactList();

private slots:
    void onAddContactClicked();
    void onEditContactClicked();
    void onRemoveContactClicked();
    void onSearchClicked();
    void onSaveToFileClicked();
    void onLoadFromFileClicked();

    void onAddContactWindowClosed();

    void onListItemClicked(QListWidgetItem *item);
private:

    Ui::ContactList *ui;

    addContact* addContactWindow;


};
#endif // CONTACTLIST_H
