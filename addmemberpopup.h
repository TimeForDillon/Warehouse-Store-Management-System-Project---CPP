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

    QString get_name() const;
    bool get_type() const;
    Date get_date() const;

private slots:
    void on_addMemberPushButton_clicked();
    void on_cancelAddMemberPushButton_clicked();
    void on_enterMemberNameLineEdit_returnPressed();

private:
    Ui::AddMemberPopUp *ui;
    QString basic_name;
    bool member_type;
    Date member_exp;
};

#endif // ADDBASICPOPUP_H
