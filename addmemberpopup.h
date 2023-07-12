#ifndef ADDMEMBERPOPUP_H
#define ADDMEMBERPOPUP_H

#include <QDialog>
#include "date.h"

namespace Ui {
class AddMemberPopUp;
}

class AddMemberPopUp : public QDialog
{
    Q_OBJECT

public:
    explicit AddMemberPopUp(QWidget *parent = nullptr);
    ~AddMemberPopUp();

    // Accessor for getting the name of the member
    QString get_name() const;

    // Accessor for getting the type of the member
    bool get_type() const;

    // Accessor for getting the date of the member
    Date get_date() const;

private slots:
    void on_addMemberPushButton_clicked();
    void on_cancelAddMemberPushButton_clicked();
    void on_enterMemberNameLineEdit_returnPressed();

private:
    Ui::AddMemberPopUp *ui;    // User interface pointer
    QString basic_name;        // Name of the member
    bool member_type;          // Type of the member
    Date member_exp;           // Expiration date of the member
};

#endif // ADDBASICPOPUP_H
