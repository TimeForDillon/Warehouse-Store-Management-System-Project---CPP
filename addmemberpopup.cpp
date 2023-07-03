#include "addmemberpopup.h"
#include "ui_addmemberpopup.h"

AddMemberPopUp::AddMemberPopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMemberPopUp),
    member_type(true)
{
    ui->setupUi(this);
    ui->addMemberInvalidEntryLabel->hide();
}

AddMemberPopUp::~AddMemberPopUp()
{
    delete ui;
}

QString AddMemberPopUp::get_name() const
{
    return basic_name;
}

bool AddMemberPopUp::get_type() const
{
    return member_type;
}

Date AddMemberPopUp::get_date() const
{
    return member_exp;
}

void AddMemberPopUp::on_addMemberPushButton_clicked()
{
    if (ui->enterMemberNameLineEdit->text() == "" || ui->enterMemberExpirationMonthLineEdit->text() == "" || ui->enterMemberExpirationDayLineEdit->text() == "" || ui->enterMemberExpirationYearLineEdit->text() == "")
    {
        ui->addMemberInvalidEntryLabel->setText("Fill in all blanks");
        ui->addMemberInvalidEntryLabel->show();
        return;
    }

    int day = ui->enterMemberExpirationDayLineEdit->text().toInt();
    int month = ui->enterMemberExpirationMonthLineEdit->text().toInt();
    int year = ui->enterMemberExpirationYearLineEdit->text().toInt();

    Date test(month, day, year);
    if (test.get_day() != day || test.get_month() != month || test.get_year() != year)
    {
        ui->addMemberInvalidEntryLabel->setText("Invalid date entry");
        ui->addMemberInvalidEntryLabel->show();
        return;
    }

    basic_name = ui->enterMemberNameLineEdit->text();

    if (ui->selectTypeComboBox->currentText() == "Preferred")
        member_type = true;
    else if (ui->selectTypeComboBox->currentText() == "Basic")
        member_type = false;

    member_exp = test;

    done(1);
}

void AddMemberPopUp::on_cancelAddMemberPushButton_clicked()
{
    done(0);
}

void AddMemberPopUp::on_enterMemberNameLineEdit_returnPressed()
{
    on_addMemberPushButton_clicked();
}
