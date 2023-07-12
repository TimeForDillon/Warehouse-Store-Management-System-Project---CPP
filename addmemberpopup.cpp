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

// Accessor for getting the name of the member
QString AddMemberPopUp::get_name() const
{
    return basic_name;
}

// Accessor for getting the type of the member
bool AddMemberPopUp::get_type() const
{
    return member_type;
}

// Accessor for getting the date of the member
Date AddMemberPopUp::get_date() const
{
    return member_exp;
}

void AddMemberPopUp::on_addMemberPushButton_clicked()
{
    // Check for empty fields
    if (ui->enterMemberNameLineEdit->text() == "" || ui->enterMemberExpirationMonthLineEdit->text() == "" || ui->enterMemberExpirationDayLineEdit->text() == "" || ui->enterMemberExpirationYearLineEdit->text() == "")
    {
        ui->addMemberInvalidEntryLabel->setText("Fill in all blanks");
        ui->addMemberInvalidEntryLabel->show();
        return;
    }

    // Retrieve day, month, and year from input fields
    int day = ui->enterMemberExpirationDayLineEdit->text().toInt();
    int month = ui->enterMemberExpirationMonthLineEdit->text().toInt();
    int year = ui->enterMemberExpirationYearLineEdit->text().toInt();

    // Create a Date object to validate the date entry
    Date test(month, day, year);
    if (test.get_day() != day || test.get_month() != month || test.get_year() != year)
    {
        ui->addMemberInvalidEntryLabel->setText("Invalid date entry");
        ui->addMemberInvalidEntryLabel->show();
        return;
    }

    // Store the name, type, and expiration date
    basic_name = ui->enterMemberNameLineEdit->text();

    if (ui->selectTypeComboBox->currentText() == "Preferred")
        member_type = true;
    else if (ui->selectTypeComboBox->currentText() == "Basic")
        member_type = false;

    member_exp = test;

    // Signal successful addition of member with a return value of 1
    done(1);
}

void AddMemberPopUp::on_cancelAddMemberPushButton_clicked()
{
    // Signal cancellation with a return value of 0
    done(0);
}

void AddMemberPopUp::on_enterMemberNameLineEdit_returnPressed()
{
    // Trigger the addMemberPushButton click event when the Enter key is pressed in the name input field
    on_addMemberPushButton_clicked();
}
