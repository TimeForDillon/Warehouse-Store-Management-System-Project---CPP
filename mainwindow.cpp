#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addmemberpopup.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , deleting(false)
    , active_row(0)
{
    QTableWidget * theTable;    // CALC - pointer to table widget used to
                                //        setup table widgets

    ui->setupUi(this);
    //system("pwd");

    findSavedFiles();
    ui->displayAllMembersRadioButton->click();

    // OUT: set up the member list table widget
    theTable = ui->membersTableWidget;
    theTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    theTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Member ID"));
    theTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Membership Expiration"));
    theTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Membership Type"));
    theTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Annual Dues"));
    theTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    theTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    theTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    theTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    theTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);

    // OUT: set up the sales report items sold table widget
    theTable = ui->reportsItemsSoldTableWidget;
    theTable->setColumnCount(4);
    theTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Item Name"));
    theTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Item Price"));
    theTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Quantity Sold"));
    theTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Revenue"));
    theTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    theTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    theTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    theTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    // OUT: set up the sales report members who shopped table widget
    theTable = ui->reportsMembersShoppedTableWidget;
    theTable->setColumnCount(4);
    theTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Member Name"));
    theTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Member ID"));
    theTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Membership Type"));
    theTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Membership Expiration"));
    theTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    theTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    theTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    theTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    // OUT: set up the items sold report table widget
    theTable = ui->itemsSoldOnlyTableWidget;
    theTable->setColumnCount(4);
    theTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Item Name"));
    theTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Item Price"));
    theTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Quantity Sold"));
    theTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Revenue"));
    theTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    theTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    theTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    theTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    // PROC: set up member list tab ui
    ui->notificationLabel      ->setText("");
    ui->confirmDeletePushButton->hide();
    ui->confirmDeletePushButton->setDisabled(true);
    ui->cancelDeletePushButton ->hide();
    ui->shouldConvertLabel_1   ->setWordWrap(true);
    ui->shouldConvertLabel_2   ->setWordWrap(true);
    ui->searchNameLineEdit     ->setText("");
    ui->searchIDLineEdit       ->setText("");
    ui->searchDayLineEdit      ->setText("");
    ui->searchMonthLineEdit    ->setText("");
    ui->searchYearLineEdit     ->setText("");
    ui->searchClearPushButton  ->click();
    ui->invalidSearchLabel     ->hide();
    ui->viewTotalPurchasesPushButton->hide();

    // PROC: set up reports tab ui
    ui->itemsSoldOnlyTableWidget     ->hide();
    ui->reportsSummaryGroupBox       ->setStyleSheet("QGroupBox{border: 0px;}");
    ui->showItemsSoldGroupBox        ->setChecked(false);
    ui->salesReportGroupBox          ->setChecked(false);
    ui->salesReportGroupBox          ->setChecked(true);
    ui->dailySalesReportRadioButton  ->click();
    ui->reportsAllMembersRadioButton ->click();
    ui->salesReportInvalidEntryLabel ->hide();
    ui->reportsNotificationLabel     ->hide();
    ui->generateSalesReportPushButton->setDisabled(true);

    // PROC: set up import files tab ui
    ui->importMemberFileGroupBox->setStyleSheet("QGroupBox{border: 1px solid gray; margin-top: 7px;} "
                                                "QGroupBox::title{subcontrol-origin: margin; left: 7px; padding: 0px 3px 0px 3px;}");
    ui->importSalesFileGroupBox ->setStyleSheet("QGroupBox{border: 1px solid gray; margin-top: 7px;} "
                                                "QGroupBox::title{subcontrol-origin: margin; left: 7px; padding: 0px 3px 0px 3px;}");
    ui->noFileFoundLabel_1->hide();
    ui->noFileFoundLabel_2->hide();
    ui->memberListUpdatedLabel->hide();
    ui->salesListUpdatedLabel->hide();
}

MainWindow::~MainWindow()
{
    QString shoppersPath;
    QString salesPath;

    shoppersPath = qApp->applicationDirPath() + "/all shoppers.txt";
    salesPath    = qApp->applicationDirPath() + "/all sales.txt";

    QFile allShoppers(shoppersPath);

    if (allShoppers.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&allShoppers);

        for (int i = 0; i < members.size(); i++)
        {
            out << QString::fromStdString(members[i].get_name()) << "\n";
            out << QString::number(members[i].get_member_id()) << "\n";
            if (members[i].get_type() == true)
                out << "Preferred\n";
            else
                out << "Basic\n";
            out << QString::fromStdString(members[i].get_expiration_date().returnNumeric()) << "\n";
        }
    }

    QFile allSales(salesPath);

    if (allSales.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&allSales);

        for (int i = 0; i < items_sold.size(); i++)
        {
            out << QString::fromStdString(items_sold[i].getDate()) << "\n";
            out << QString::number(items_sold[i].getID()) << "\n";
            out << QString::fromStdString(items_sold[i].getItemName()) << "\n";
            out << QString::number(items_sold[i].getItemPrice(), 'f' , 2) << "\t"
                << QString::number(items_sold[i].getQuantity()) << "\n";
        }
    }

    delete ui;
}

void MainWindow::findSavedFiles()
{
    members.load(qApp->applicationDirPath() + "/all shoppers.txt");
    items_sold.load(qApp->applicationDirPath() + "/all sales.txt");

    if (members.size() == 0 || items_sold.size() == 0)
        ui->tabs->setCurrentIndex(2);
}

void MainWindow::display()
{
    int total_size;            // CALC - will be assigned the size of members
    int row;                   // CALC - used to display preferred/basic members
    QTableWidget * theTable;   // CALC - table widget pointer for table setup

    row = 0;
    total_size = members.size();
    theTable   = ui->membersTableWidget;

    ui->memberInfoTextBrowser->clear();
    ui->selectToViewLabel->show();
    ui->viewTotalPurchasesPushButton->hide();

    if (!deleting)
        ui->notificationLabel->clear();

    // PROC & OUT: set text of notification label to let user know what is being
    //             displayed
    if (display_mode == 1)
        ui->displayNoticeLabel->setText("Displaying all members");
    else if (display_mode == 2)
        ui->displayNoticeLabel->setText("Displaying Preferred members");
    else if (display_mode == 3)
        ui->displayNoticeLabel->setText("Displaying Basic members");

    theTable->setColumnCount(5);

    // PROC & OUT: display members depending on what membership type the user
    //             has selected (1 == all, 2 == preferred, 3 == basic)
    if (display_mode == 1)
    {
        theTable->setRowCount(members.size());

        for (int i = 0; i < total_size; i++)
        {
            theTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(members[i].get_name())));
            theTable->setItem(i, 1, new QTableWidgetItem(QString::number(members[i].get_member_id())));
            theTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(members[i].get_expiration_date().returnNumeric())));

            if (members[i].get_type() == true)
                theTable->setItem(i, 3, new QTableWidgetItem("Preferred"));
            else
                theTable->setItem(i, 3, new QTableWidgetItem("Basic"));

            theTable->setItem(i, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
        }
    }
    else if (display_mode == 2)
    {
        // PROC: when displaying preferred members, an extra column is added for
        //       the rebate amount
        theTable->setColumnCount(6);

        theTable->setRowCount(members.preferred_size());
        theTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Rebate"));
        theTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);

        for (int i = 0; i < total_size; i++)
        {
            if (members[i].get_type() == true)
            {
                theTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(members[i].get_name())));
                theTable->setItem(row, 1, new QTableWidgetItem(QString::number(members[i].get_member_id())));
                theTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(members[i].get_expiration_date().returnNumeric())));
                theTable->setItem(row, 3, new QTableWidgetItem("Preferred"));
                theTable->setItem(row, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
                theTable->setItem(row, 5, new QTableWidgetItem("$" + QString::number(members[i].get_rebate())));

                row++;
            }
        }
    }
    else if (display_mode == 3)
    {
        theTable->setRowCount(members.basic_size());

        for (int i = 0; i < total_size; i++)
        {
            if (members[i].get_type() == false)
            {
                theTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(members[i].get_name())));
                theTable->setItem(row, 1, new QTableWidgetItem(QString::number(members[i].get_member_id())));
                theTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(members[i].get_expiration_date().returnNumeric())));
                theTable->setItem(row, 3, new QTableWidgetItem("Basic"));
                theTable->setItem(row, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));

                row++;
            }
        }
    }

    theTable->show();
}

void MainWindow::display_found(QString name)
{
    // variables          DATA TABLE
    int rows;             // CALC - used as indexing variable to display results
    int index;            // CALC - the index position of the member in the
                          //        member container that has the QString
                          //        argument as a substring
    Member the_member;    // CALC - the member who's name contains the QString
                          //        argument
    QString notice;       //  OUT - stores the notification message telling the
                          //        user that the table is showing the results
                          //        of the search

    QTableWidget * theTable; // CALC - used for table widget setup

    rows = 0;
    notice = "Showing results for '" + name + "'";
    theTable = ui->membersTableWidget;

    // PROC & OUT: set up ui
    ui->memberInfoTextBrowser->clear();
    ui->selectToViewLabel    ->show();
    ui->membersTableWidget   ->clearContents();
    ui->displayNoticeLabel   ->setText(notice);
    ui->viewTotalPurchasesPushButton->hide();
    if (!deleting)
        ui->notificationLabel->clear();

    // PROC & OUT: go through the member list and check each member name if it
    //             contains the QString argument as a substring, display if so
    for (int i = 0; i < members.size(); i++)
    {
        // PROC: call the find function from the member container class
        index = members.find(name.toStdString(), i);

        // PROC: index >= 0 if the member's name contains the substring
        if (index >= 0)
        {
            the_member = members[index];

            if (display_mode == 1)
            {
                rows++;
                theTable->setRowCount(rows);
                theTable->setColumnCount(5);

                theTable->setItem(rows - 1, 0, new QTableWidgetItem(QString::fromStdString(the_member.get_name())));
                theTable->setItem(rows - 1, 1, new QTableWidgetItem(QString::number(the_member.get_member_id())));
                theTable->setItem(rows - 1, 2, new QTableWidgetItem(QString::fromStdString(the_member.get_expiration_date().returnNumeric())));

                if (members[i].get_type() == true)
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Preferred"));
                else
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Basic"));

                theTable->setItem(rows - 1, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
            }
            else if (display_mode == 2)
            {
                if (the_member.get_type() == true)
                {
                    rows++;
                    theTable->setRowCount(rows);
                    theTable->setColumnCount(5);

                    theTable->setItem(rows - 1, 0, new QTableWidgetItem(QString::fromStdString(the_member.get_name())));
                    theTable->setItem(rows - 1, 1, new QTableWidgetItem(QString::number(the_member.get_member_id())));
                    theTable->setItem(rows - 1, 2, new QTableWidgetItem(QString::fromStdString(the_member.get_expiration_date().returnNumeric())));
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Preferred"));
                    theTable->setItem(rows - 1, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
                }
            }
            else if (display_mode == 3)
            {
                if (the_member.get_type() == false)
                {
                    rows++;
                    theTable->setRowCount(rows);
                    theTable->setColumnCount(5);

                    theTable->setItem(rows - 1, 0, new QTableWidgetItem(QString::fromStdString(the_member.get_name())));
                    theTable->setItem(rows - 1, 1, new QTableWidgetItem(QString::number(the_member.get_member_id())));
                    theTable->setItem(rows - 1, 2, new QTableWidgetItem(QString::fromStdString(the_member.get_expiration_date().returnNumeric())));
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Basic"));
                    theTable->setItem(rows - 1, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
                }
            }

            i = index;
        }
        else
        {
            break;
        }
    }

    // PROC & OUT: if there are no results, let the user know
    if (rows == 0)
    {
        notice = "No results for '" + name + "'";
        ui->displayNoticeLabel->setText(notice);
        theTable->setRowCount(rows);
        theTable->setColumnCount(5);
    }
}

void MainWindow::display_found(int id)
{
    // variables          DATA TABLE
    int rows;             // CALC - used as indexing variable to display results
    int index;            // CALC - the index position of the member in the
                          //        member container that has the QString
                          //        argument as a substring
    Member the_member;    // CALC - the member who's name contains the QString
                          //        argument
    QString notice;       //  OUT - stores the notification message telling the
                          //        user that the table is showing the results
                          //        of the search

    QTableWidget * theTable; // CALC - used for table widget setup

    rows = 0;
    notice = "Showing results for ID#" + QString::fromStdString(to_string(id));
    theTable = ui->membersTableWidget;

    // PROC: set up ui
    ui->memberInfoTextBrowser->clear();
    ui->selectToViewLabel    ->show();
    ui->membersTableWidget   ->clearContents();
    ui->displayNoticeLabel   ->setText(notice);
    ui->viewTotalPurchasesPushButton->hide();
    if (!deleting)
        ui->notificationLabel->clear();

    // PROC & OUT: go through the member list and check each member id if it
    //             matches the argument id, display member if so
    for (int i = 0; i < members.size(); i++)
    {
        // PROC: call the find function from the member container class
        index = members.find(id, i);

        // PROC: index >= 0 if the member's id matches the argument
        if (index >= 0)
        {
            the_member = members[index];

            if (display_mode == 1)
            {
                rows++;
                theTable->setRowCount(rows);
                theTable->setColumnCount(5);

                theTable->setItem(rows - 1, 0, new QTableWidgetItem(QString::fromStdString(the_member.get_name())));
                theTable->setItem(rows - 1, 1, new QTableWidgetItem(QString::number(the_member.get_member_id())));
                theTable->setItem(rows - 1, 2, new QTableWidgetItem(QString::fromStdString(the_member.get_expiration_date().returnNumeric())));

                if (members[i].get_type() == true)
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Preferred"));
                else
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Basic"));

                theTable->setItem(rows - 1, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
            }
            else if (display_mode == 2)
            {
                if (the_member.get_type() == true)
                {
                    rows++;
                    theTable->setRowCount(rows);
                    theTable->setColumnCount(5);

                    theTable->setItem(rows - 1, 0, new QTableWidgetItem(QString::fromStdString(the_member.get_name())));
                    theTable->setItem(rows - 1, 1, new QTableWidgetItem(QString::number(the_member.get_member_id())));
                    theTable->setItem(rows - 1, 2, new QTableWidgetItem(QString::fromStdString(the_member.get_expiration_date().returnNumeric())));
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Preferred"));
                    theTable->setItem(rows - 1, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
                }
            }
            else if (display_mode == 3)
            {
                if (the_member.get_type() == false)
                {
                    rows++;
                    theTable->setRowCount(rows);
                    theTable->setColumnCount(5);

                    theTable->setItem(rows - 1, 0, new QTableWidgetItem(QString::fromStdString(the_member.get_name())));
                    theTable->setItem(rows - 1, 1, new QTableWidgetItem(QString::number(the_member.get_member_id())));
                    theTable->setItem(rows - 1, 2, new QTableWidgetItem(QString::fromStdString(the_member.get_expiration_date().returnNumeric())));
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Basic"));
                    theTable->setItem(rows - 1, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
                }
            }

            i = index;
        }
        else
        {
            break;
        }
    }

    // PROC & OUT: if there are no results, let the user know
    if (rows == 0)
    {
        notice = "No results for ID#" + QString::fromStdString(to_string(id));
        ui->displayNoticeLabel->setText(notice);
        theTable->setRowCount(rows);
        theTable->setColumnCount(5);
    }
}

void MainWindow::display_found(int day, int month, int year)
{
    // variables          DATA TABLE
    int rows;             // CALC - used as indexing variable to display results
    int index;            // CALC - the index position of the member in the
                          //        member container that has the QString
                          //        argument as a substring
    Member the_member;    // CALC - the member who's name contains the QString
                          //        argument
    QString notice;       //  OUT - stores the notification message telling the
                          //        user that the table is showing the results
                          //        of the search

    QTableWidget * theTable; // CALC - used for table widget setup

    rows = 0;
    theTable = ui->membersTableWidget;

    if (month == 0)
    {
        notice = "Showing results for member expiration year " + QString::fromStdString(to_string(year));
    }
    else if (day == 0)
    {
        notice = "Showing results for member expiration month " + QString::fromStdString(to_string(month)) +
                 "/" + QString::fromStdString(to_string(year));
    }
    else
    {
        notice = "Showing results for member expiration date " + QString::fromStdString(to_string(month)) +
                 "/" + QString::fromStdString(to_string(day)) + "/" + QString::fromStdString(to_string(year));
    }

    // PROC: set up ui
    ui->memberInfoTextBrowser->clear();
    ui->selectToViewLabel    ->show();
    ui->membersTableWidget   ->clearContents();
    ui->displayNoticeLabel   ->setText(notice);
    ui->viewTotalPurchasesPushButton->hide();
    if (!deleting)
        ui->notificationLabel->clear();

    // PROC & OUT: go through the member list and check each membership exp. if
    //             it matches the argument date, display member if so
    for (int i = 0; i < members.size(); i++)
    {
        // PROC: call the find function from the member container class
        index = members.find(day, month, year, i);

        // PROC: index >= 0 if the member's expiration date matches the argument
        if (index >= 0)
        {
            the_member = members[index];

            if (display_mode == 1)
            {
                rows++;
                theTable->setRowCount(rows);
                theTable->setColumnCount(5);

                theTable->setItem(rows - 1, 0, new QTableWidgetItem(QString::fromStdString(the_member.get_name())));
                theTable->setItem(rows - 1, 1, new QTableWidgetItem(QString::number(the_member.get_member_id())));
                theTable->setItem(rows - 1, 2, new QTableWidgetItem(QString::fromStdString(the_member.get_expiration_date().returnNumeric())));

                if (members[i].get_type() == true)
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Preferred"));
                else
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Basic"));

                theTable->setItem(rows - 1, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
            }
            else if (display_mode == 2)
            {
                if (the_member.get_type() == true)
                {
                    rows++;
                    theTable->setRowCount(rows);
                    theTable->setColumnCount(5);

                    theTable->setItem(rows - 1, 0, new QTableWidgetItem(QString::fromStdString(the_member.get_name())));
                    theTable->setItem(rows - 1, 1, new QTableWidgetItem(QString::number(the_member.get_member_id())));
                    theTable->setItem(rows - 1, 2, new QTableWidgetItem(QString::fromStdString(the_member.get_expiration_date().returnNumeric())));
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Preferred"));
                    theTable->setItem(rows - 1, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
                }
            }
            else if (display_mode == 3)
            {
                if (the_member.get_type() == false)
                {
                    rows++;
                    theTable->setRowCount(rows);
                    theTable->setColumnCount(5);

                    theTable->setItem(rows - 1, 0, new QTableWidgetItem(QString::fromStdString(the_member.get_name())));
                    theTable->setItem(rows - 1, 1, new QTableWidgetItem(QString::number(the_member.get_member_id())));
                    theTable->setItem(rows - 1, 2, new QTableWidgetItem(QString::fromStdString(the_member.get_expiration_date().returnNumeric())));
                    theTable->setItem(rows - 1, 3, new QTableWidgetItem("Basic"));
                    theTable->setItem(rows - 1, 4, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
                }
            }

            i = index;
        }
        else
        {
            break;
        }
    }

    // PROC & OUT: if there are no results, let the user know
    if (rows == 0)
    {
        notice.replace(0, 7, "No");
        ui->displayNoticeLabel->setText(notice);
        theTable->setRowCount(rows);
        theTable->setColumnCount(5);
    }
}

void MainWindow::display_member_info(int id)
{
    QString memberInfo;    // OUT - stores member info formatted for output

    memberInfo = "";

    // PROC & OUT: go through the members container and display the info
    //             about the member whose id matches the argument id
    for (int i = 0; i < members.size(); i++)
    {
        if (members[i].get_member_id() == id)
        {
            memberInfo = "Name: " + QString::fromStdString(members[i].get_name()) + "\n";
            memberInfo += "ID#: " + QString::number(members[i].get_member_id()) + "\n\n";

            if (members[i].get_type() == true)
                memberInfo += "Membership type: Preferred\n";
            else
                memberInfo += "Membership type: Basic\n";

            memberInfo += "Membership expiration:\n       " + QString::fromStdString(members[i].get_expiration_date().returnAlpha()) + "\n\n";
            memberInfo += "Annual due amount: $" + QString::number(members[i].get_annual_dues()) + "\n";

            if (members[i].get_type() == true)
                memberInfo += "Rebate amount: $" + QString::number(members[i].get_rebate(), 'f', 2) + "\n";
            else
                memberInfo += "Potential rebate: $" + QString::number(members[i].get_rebate(), 'f', 2) + "\n";

            memberInfo += "Total spent: $" + QString::number(members[i].get_total_amount_spent(), 'f', 2) + "\n";

            break;
        }
    }

    // PROC & OUT: set up ui and display memberInfo onto the member info text
    //             browser
    ui->viewTotalPurchasesPushButton->setText("View Total Purchases");
    ui->viewTotalPurchasesPushButton->show();
    ui->memberInfoTextBrowser       ->setText(memberInfo);
    ui->selectToViewLabel           ->hide();
}

void MainWindow::display_items_sold_no_dup(SaleContainer& items)
{
    // variables           DATA TABLE
    double price;          // CALC - assigned the price of an item for revenue
                           //        calculation
    int quantity;          // CALC - assigned the quantity of an item for
                           //        total_quantity calculation
    int total_quantity;    // CALC - used to calculate the revenue for an item
    double revenue;        // CALC - assigned the revenue for an item
    int row;               // CALC - used to displaying items so that there are
                           //        no duplicate items displayed
    bool exists;           // CALC - true if the item has already been displayed

    QTableWidget * theTable; // CALC - used for table widget setup

    row = 0;

    // OUT: determine which notification to show
    if (ui->showItemsSoldGroupBox->isChecked())
    {
        theTable = ui->itemsSoldOnlyTableWidget;

        if (ui->reportsAllMembersRadioButton->isChecked())
        {
            ui->reportsNotificationLabel->setText("Showing report on all items sold");
            ui->reportsNotificationLabel->show();
        }
        else if (ui->reportsPreferredMembersRadioButton->isChecked())
        {
            ui->reportsNotificationLabel->setText("Showing report on items sold to Preferred members");
            ui->reportsNotificationLabel->show();
        }
        else if (ui->reportsBasicMembersRadioButton->isChecked())
        {
            ui->reportsNotificationLabel->setText("Showing report on items sold to Basic members");
            ui->reportsNotificationLabel->show();
        }

    }
    else
    {
        theTable = ui->reportsItemsSoldTableWidget;
    }

    theTable->clearContents();
    theTable->setRowCount(0);

    // PROC & OUT: display items sold depending on membership type selected by
    //             the user and whether the show all items sold group box is
    //             checked or the sales report group box is checked
    if (ui->reportsAllMembersRadioButton->isChecked())
    {
        for (int i = 0; i < items.size(); i++)
        {
            exists = false;
            for (int j = 0; j < theTable->rowCount(); j++)
            {
                if (theTable->item(j, 0)->text() == QString::fromStdString(items[i].getItemName()))
                {
                    total_quantity = theTable->item(j, 2)->text().toInt();
                    total_quantity += items[i].getQuantity();
                    theTable->item(j, 2)->setText(QString::number(total_quantity));
                    exists = true;
                    break;
                }
            }

            if (!exists)
            {
                theTable->insertRow(row);
                price = items[i].getItemPrice();
                quantity = items[i].getQuantity();
                revenue = price * quantity;

                theTable->setItem(row,0,new QTableWidgetItem(QString::fromStdString(items[i].getItemName())));
                theTable->setItem(row,1,new QTableWidgetItem("$" + QString::number(price, 'f', 2)));
                theTable->setItem(row,2,new QTableWidgetItem(QString::number(quantity)));
                theTable->setItem(row,3,new QTableWidgetItem("$" + QString::number(revenue, 'f', 2)));
                row++;
            }
        }
    }
    else if (ui->reportsPreferredMembersRadioButton->isChecked())
    {
        for (int i = 0; i < items.size(); i++)
        {
            for (int j = 0; j < members.size(); j++)
            {
                if (items[i].getID() == members[j].get_member_id() && members[j].get_type() == true)
                {
                    exists = false;
                    for (int k = 0; k < theTable->rowCount(); k++)
                    {
                        if (theTable->item(k, 0)->text() == QString::fromStdString(items[i].getItemName()))
                        {
                            total_quantity = theTable->item(k, 2)->text().toInt();
                            total_quantity += items[i].getQuantity();
                            theTable->item(k, 2)->setText(QString::number(total_quantity));
                            exists = true;
                            break;
                        }
                    }

                    if (!exists)
                    {
                        theTable->insertRow(row);
                        price = items[i].getItemPrice();
                        quantity = items[i].getQuantity();
                        revenue = price * quantity;

                        theTable->setItem(row,0,new QTableWidgetItem(QString::fromStdString(items[i].getItemName())));
                        theTable->setItem(row,1,new QTableWidgetItem("$" + QString::number(price, 'f', 2)));
                        theTable->setItem(row,2,new QTableWidgetItem(QString::number(quantity)));
                        theTable->setItem(row,3,new QTableWidgetItem("$" + QString::number(revenue, 'f', 2)));
                        row++;
                    }
                }
            }
        }
    }
    else if (ui->reportsBasicMembersRadioButton->isChecked())
    {
        for (int i = 0; i < items.size(); i++)
        {
            for (int j = 0; j < members.size(); j++)
            {
                if (items[i].getID() == members[j].get_member_id() && members[j].get_type() == false)
                {
                    exists = false;
                    for (int k = 0; k < theTable->rowCount(); k++)
                    {
                        if (theTable->item(k, 0)->text() == QString::fromStdString(items[i].getItemName()))
                        {
                            total_quantity = theTable->item(k, 2)->text().toInt();
                            total_quantity += items[i].getQuantity();
                            theTable->item(k, 2)->setText(QString::number(total_quantity));
                            exists = true;
                            break;
                        }
                    }

                    if (!exists)
                    {
                        theTable->insertRow(row);
                        price = items[i].getItemPrice();
                        quantity = items[i].getQuantity();
                        revenue = price * quantity;

                        theTable->setItem(row,0,new QTableWidgetItem(QString::fromStdString(items[i].getItemName())));
                        theTable->setItem(row,1,new QTableWidgetItem("$" + QString::number(price, 'f', 2)));
                        theTable->setItem(row,2,new QTableWidgetItem(QString::number(quantity)));
                        theTable->setItem(row,3,new QTableWidgetItem("$" + QString::number(revenue, 'f', 2)));
                        row++;
                    }
                }
            }
        }
    }
}

void MainWindow::display_items_sold(SaleContainer& items)
{
    QTableWidget * theTable;    // CALC - used to set up table widget

    if (ui->showItemsSoldGroupBox->isChecked())
        theTable = ui->itemsSoldOnlyTableWidget;
    else
        theTable = ui->reportsItemsSoldTableWidget;

    theTable->clearContents();
    theTable->setRowCount(0);

    // OUT: display items onto table widget
    for (int i = 0; i < items.size(); i++)
    {
        theTable->insertRow(i);
        theTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(items[i].getItemName())));
        theTable->setItem(i,1,new QTableWidgetItem("$" + QString::number(items[i].getItemPrice(), 'f', 2)));
        theTable->setItem(i,2,new QTableWidgetItem(QString::number(items[i].getQuantity())));
        theTable->setItem(i,3,new QTableWidgetItem("$" + QString::number(items[i].getItemPrice() * items[i].getQuantity(), 'f', 2)));
    }
}

void MainWindow::display_item_info(QString item)
{
    QString item_info;           //  OUT - contains the item info as a string
                                 //        which will be outputted in the
                                 //        additional info text browser
    QTableWidget * currentTW;    // CALC - used to determine which item's info
                                 //        is to be displayed

    item_info = "";

    if (ui->showItemsSoldGroupBox->isChecked())
        currentTW = ui->itemsSoldOnlyTableWidget;
    else
        currentTW = ui->reportsItemsSoldTableWidget;

    // PROC: add basic item info such as price and quantity sold to item_info
    for (int i = 0; i < currentTW->rowCount(); i++)
    {
        if (currentTW->item(i,0)->text() == item)
        {
            item_info += "Item: " + item;
            item_info += "\nPrice: " + currentTW->item(i,1)->text();
            item_info += "\nTotal quantity sold: " + currentTW->item(i,2)->text() + "\n\n";
            break;
        }
    }

    item_info += "                Bought By\n\n";

    // PROC: add the list of members who bought that item to item_info
    if (ui->salesReportGroupBox->isChecked())
    {
        for (int i = 0; i < items_sold_that_time.size(); i++)
        {
            if (items_sold_that_time[i].getItemName() == item.toStdString())
            {
                for (int j = 0; j < members_shopped_that_time.size(); j++)
                {
                    if (members_shopped_that_time[j].get_member_id() == items_sold_that_time[i].getID())
                    {
                        item_info += "Member: " + QString::fromStdString(members_shopped_that_time[j].get_name()) + "\n";

                        if (members_shopped_that_time[j].get_type() == true)
                            item_info += "  Membership type: Preferred\n";
                        else
                            item_info += "  Membership type: Basic\n";

                        item_info += "  Quantity bought: " + QString::number(items_sold_that_time[i].getQuantity()) + "\n";
                        item_info += "  Date of purchase: " + QString::fromStdString(items_sold_that_time[i].getDate()) + "\n\n";
                        break;
                    }
                }
            }
        }
    }
    else if (ui->showItemsSoldGroupBox->isChecked())
    {
        for (int i = 0; i < items_sold.size(); i++)
        {
            if (items_sold[i].getItemName() == item.toStdString())
            {
                for (int j = 0; j < members.size(); j++)
                {
                    if (ui->reportsAllMembersRadioButton->isChecked())
                    {
                        if (members[j].get_member_id() == items_sold[i].getID())
                        {
                            item_info += "Member: " + QString::fromStdString(members[j].get_name()) + "\n";

                            if (members[j].get_type() == true)
                                item_info += "  Membership type: Preferred\n";
                            else
                                item_info += "  Membership type: Basic\n";

                            item_info += "  Quantity bought: " + QString::number(items_sold[i].getQuantity()) + "\n";
                            item_info += "  Date of purchase: " + QString::fromStdString(items_sold[i].getDate()) + "\n\n";
                            break;
                        }
                    }
                    else if (ui->reportsPreferredMembersRadioButton->isChecked())
                    {
                        if (members[j].get_member_id() == items_sold[i].getID() && members[j].get_type() == true)
                        {
                            item_info += "Member: " + QString::fromStdString(members[j].get_name()) + "\n";

                            if (members[j].get_type() == true)
                                item_info += "  Membership type: Preferred\n";
                            else
                                item_info += "  Membership type: Basic\n";

                            item_info += "  Quantity bought: " + QString::number(items_sold[i].getQuantity()) + "\n";
                            item_info += "  Date of purchase: " + QString::fromStdString(items_sold[i].getDate()) + "\n\n";
                            break;
                        }
                    }
                    else if (ui->reportsBasicMembersRadioButton->isChecked())
                    {
                        if (members[j].get_member_id() == items_sold[i].getID() && members[j].get_type() == false)
                        {
                            item_info += "Member: " + QString::fromStdString(members[j].get_name()) + "\n";

                            if (members[j].get_type() == true)
                                item_info += "  Membership type: Preferred\n";
                            else
                                item_info += "  Membership type: Basic\n";

                            item_info += "  Quantity bought: " + QString::number(items_sold[i].getQuantity()) + "\n";
                            item_info += "  Date of purchase: " + QString::fromStdString(items_sold[i].getDate()) + "\n\n";
                            break;
                        }
                    }
                }
            }
        }
    }

    // OUT: set the text of the additional info text browser to item_info
    ui->additionalInfoTextBrowser->setText(item_info);
}

void MainWindow::add_purchases()
{
    // PROC: go through the sales list and add each sale to the member who
    //       made the purchase
    for (int i = 0; i < items_sold.size(); i++)
    {
        for (int j = 0; j < members.size(); j++)
        {
            if (items_sold[i].id == members[j].get_member_id())
                members[j].add_purchase(Sale(items_sold[i].item, items_sold[i].date_of_purchase, items_sold[i].id, items_sold[i].quantity));
        }
    }

    // PROC: calculate the total amount spent and the rebate amount for each
    //       member
    for (int i = 0; i < members.size(); i++)
    {
        members[i].calc_total_amount_spent();
        members[i].calculate_rebate();
    }

    members.typeChange();
}

void MainWindow::on_addPushButton_clicked()
{
    // variables
    AddMemberPopUp addMember_w;  // CALC - add-member pop up object for showing
                                 //        the add-member dialog
    int dialog_result;           // CALC - assigned the return value of the
                                 //        add member dialog
    string name;                 //  IN  - the new member's name
    bool type;                   //  IN  - the new member's membership type
    int id;                      // CALC - the new member's member ID

    // PROC: set up ui
    ui->memberInfoTextBrowser->clear();
    ui->selectToViewLabel->show();
    ui->viewTotalPurchasesPushButton->hide();

    // PROC: show the add member dialog
    addMember_w.setModal(true);
    dialog_result = addMember_w.exec();

    // PROC: dialog_result == 1 if the user adds a member; dialog_result == 0 if
    //       if the user clicks cancel on the pop up
    if (dialog_result == 1)
    {
        name = addMember_w.get_name().toStdString();
        type = addMember_w.get_type();

        // PROC: add the new member to the member container
        members.add_member(name, 0, type, addMember_w.get_date());

        // PROC & OUT: display the new member's info on the member info text
        //             browser
        id = members[members.size() - 1].get_member_id();
        on_sortByComboBox_currentTextChanged(ui->sortByComboBox->currentText());
        display_member_info(id);

        ui->notificationLabel->setText("Successfully added member");
    }

}

void MainWindow::on_deletePushButton_clicked()
{
    deleting = true;

    // PROC: change ui when the delete push button is clicked
    ui->memberInfoTextBrowser  ->clear();
    ui->selectToViewLabel      ->show();
    ui->notificationLabel      ->setText("Select a member to delete");
    ui->confirmDeletePushButton->show();
    ui->cancelDeletePushButton ->show();
    ui->addPushButton          ->setDisabled(true);
    ui->deletePushButton       ->setDisabled(true);
    ui->viewTotalPurchasesPushButton->hide();
}

void MainWindow::on_confirmDeletePushButton_clicked()
{
    int id;    // CALC - id of the member that the user clicked on to choose to
               //        delete

    id = ui->membersTableWidget->item(active_row, 1)->text().toInt();

    // PROC: perform the member removal
    members.remove_member(id);

    // PROC: make ui changes
    deleting = false;
    ui->confirmDeletePushButton->hide();
    ui->confirmDeletePushButton->setDisabled(true);
    ui->cancelDeletePushButton ->hide();
    ui->addPushButton          ->setEnabled(true);
    ui->deletePushButton       ->setEnabled(true);
    ui->memberInfoTextBrowser  ->clear();
    ui->selectToViewLabel      ->show();
    ui->notificationLabel      ->setText("Successfully removed member");
    ui->viewTotalPurchasesPushButton->hide();

    // PROC: display the members again
    display();
}

void MainWindow::on_cancelDeletePushButton_clicked()
{
    // PROC: make ui changes
    deleting = false;
    ui->cancelDeletePushButton ->hide();
    ui->confirmDeletePushButton->setDisabled(true);
    ui->confirmDeletePushButton->hide();
    ui->notificationLabel      ->setText("");
    ui->addPushButton          ->setEnabled(true);
    ui->deletePushButton       ->setEnabled(true);
    ui->memberInfoTextBrowser  ->clear();
    ui->selectToViewLabel      ->show();
    ui->viewTotalPurchasesPushButton->hide();
}

void MainWindow::on_membersTableWidget_cellClicked(int row, int column)
{
    int id;    // CALC - id of the member that the user clicked on to view
               //        member info

    // OUT: if the user is trying to delete a member, after the user clicks on a
    //      member the program will ask the user to confirm the delete
    if (deleting)
    {
        ui->notificationLabel->setText("Delete member " + ui->membersTableWidget->item(row, 0)->text() + "?");
        ui->notificationLabel->setWordWrap(true);
        ui->confirmDeletePushButton->setEnabled(true);
    }

    ui->selectToViewLabel->hide();
    ui->viewTotalPurchasesPushButton->show();

    active_row = row;
    id = ui->membersTableWidget->item(active_row, 1)->text().toInt();

    // PROC: display the member's info
    for (int i = 0; i < members.size(); i++)
    {
        if (members[i].get_member_id() == id)
        {
            display_member_info(id);
            break;
        }
    }
}

void MainWindow::on_searchNameLineEdit_textEdited(const QString &arg1)
{
    // PROC: make ui changes
    ui->searchIDLineEdit   ->setText("");
    ui->searchDayLineEdit  ->setText("");
    ui->searchMonthLineEdit->setText("");
    ui->searchYearLineEdit ->setText("");
    ui->confirmSearchPushButton->setDisabled(true);

    // PROC: each time the search name line is edited, results will be displayed
    display_found(arg1);
}

void MainWindow::on_searchIDLineEdit_textEdited(const QString &arg1)
{
    // PROC: make ui changes
    ui->searchNameLineEdit ->setText("");
    ui->searchDayLineEdit  ->setText("");
    ui->searchMonthLineEdit->setText("");
    ui->searchYearLineEdit ->setText("");
    ui->confirmSearchPushButton->setEnabled(true);

    if (arg1 == "")
        ui->searchClearPushButton->click();
}

void MainWindow::on_searchClearPushButton_clicked()
{
    // PROC: make ui changes
    ui->searchNameLineEdit ->setText("");
    ui->searchIDLineEdit   ->setText("");
    ui->searchDayLineEdit  ->setText("");
    ui->searchMonthLineEdit->setText("");
    ui->searchYearLineEdit ->setText("");
    ui->invalidSearchLabel ->hide();
    ui->confirmSearchPushButton->setDisabled(true);

    // PROC: if the user clicks the clear push button, display all members
    display();
}

void MainWindow::on_searchDayLineEdit_textEdited(const QString &arg1)
{
    // PROC: make ui changes
    ui->searchNameLineEdit->setText("");
    ui->searchIDLineEdit->setText("");
    ui->confirmSearchPushButton->setEnabled(true);
}

void MainWindow::on_searchMonthLineEdit_textEdited(const QString &arg1)
{
    // PROC: make ui changes
    ui->searchNameLineEdit->setText("");
    ui->searchIDLineEdit->setText("");
    ui->confirmSearchPushButton->setEnabled(true);
}

void MainWindow::on_searchYearLineEdit_textEdited(const QString &arg1)
{
    // PROC: make ui changes
    ui->searchNameLineEdit->setText("");
    ui->searchIDLineEdit->setText("");
    ui->confirmSearchPushButton->setEnabled(true);
}

void MainWindow::on_confirmSearchPushButton_clicked()
{
    // variables
    int id;          // IN - id to search for inputted by user
    unsigned day;    // IN - membership exp. day to search for inputted by user
    unsigned month;  // IN - membership exp. mo. to search for inputted by user
    unsigned year;   // IN - membership exp. year to search for inputted by user

    // PROC & OUT: If the user provided an entry in the ID section, show search
    //             results for the ID. If the user provided an entry in the
    //             expiration date section, show search results for the
    //             expiration date.
    if (ui->searchIDLineEdit->text() != "")
    {
        id = ui->searchIDLineEdit->text().toInt();

        // PROC & OUT: contingency handling
        if (id < 10000 || id > 99999)
        {
            ui->invalidSearchLabel->setText("Invalid ID");
            ui->invalidSearchLabel->show();
        }
        else
        {
            ui->invalidSearchLabel->hide();
            display_found(id);
        }
    }
    else if (ui->searchDayLineEdit->text() != "" || ui->searchMonthLineEdit->text() != "" || ui->searchYearLineEdit->text() != "")
    {
        // PROC: determine whether the user provided a month or a day
        if (ui->searchDayLineEdit->text() == "")
            day = 0;
        else
            day = ui->searchDayLineEdit->text().toInt();

        if (ui->searchMonthLineEdit->text() == "")
            month = 0;
        else
            month = ui->searchMonthLineEdit->text().toInt();

        if (ui->searchYearLineEdit->text() == "")
            year = 0;
        else
            year = ui->searchYearLineEdit->text().toInt();

        // PROC & OUT: if date entry is valid, show
        //             search results for the member expiration
        if (year == 0)
        {
            // PROC: contingency handling
            ui->invalidSearchLabel->setText("Invalid date entry");
            ui->invalidSearchLabel->show();
        }
        else if (day == 0 && month == 0)
        {
            ui->invalidSearchLabel->hide();
            display_found(day, month, year);
        }
        else if (day == 0)
        {
            if (month > 0 && month < 13)
            {
                ui->invalidSearchLabel->hide();
                display_found(day, month, year);
            }
            else
            {
                // PROC: contingency handling
                ui->invalidSearchLabel->setText("Invalid date entry");
                ui->invalidSearchLabel->show();
            }
        }
        else
        {
            Date test(month, day, year);

            if (test.get_day() == day && test.get_month() == month && test.get_year() == year)
            {
                ui->invalidSearchLabel->hide();
                display_found(day, month, year);
            }
            else
            {
                // PROC: contingency handling
                ui->invalidSearchLabel->setText("Invalid date entry");
                ui->invalidSearchLabel->show();
            }
        }
    }
}

void MainWindow::on_searchNameLineEdit_textChanged(const QString &arg1)
{
    // OUT: if the search name line is empty, display all members
    if (arg1 == "")
        display();
}

void MainWindow::on_displayAllMembersRadioButton_clicked()
{
    // OUT: display all members if user clicks display all members radio button
    display_mode = 1;
    display();
}

void MainWindow::on_displayPreferredMembersRadioButton_clicked()
{
    // OUT: display Preferred members if user clicks display Preferred members
    //      radio button
    display_mode = 2;
    display();
}

void MainWindow::on_displayBasicMembersRadioButton_clicked()
{
    // OUT: display Basic members if user clicks display Basic members radio
    //      button
    display_mode = 3;
    display();
}

void MainWindow::on_searchIDLineEdit_returnPressed()
{
    on_confirmSearchPushButton_clicked();
}

void MainWindow::on_searchDayLineEdit_returnPressed()
{
    on_confirmSearchPushButton_clicked();
}

void MainWindow::on_searchMonthLineEdit_returnPressed()
{
    on_confirmSearchPushButton_clicked();
}

void MainWindow::on_searchYearLineEdit_returnPressed()
{
    on_confirmSearchPushButton_clicked();
}

void MainWindow::on_sortByComboBox_currentTextChanged(const QString &arg1)
{
    // PROC & OUT: sort the member list by name, ID, or exp. date depending on
    //             which the user has selected and display (if the user is using
    //             the search function, only display sorted search results)
    if (arg1 == "Name")
    {
        members.sort_by_name();

        if (ui->searchNameLineEdit->text() != "")
            display_found(ui->searchNameLineEdit->text());
        else if (ui->searchIDLineEdit->text() != "" || ui->searchYearLineEdit->text() != "")
            on_confirmSearchPushButton_clicked();
        else
            display();

    } else if (arg1 == "Member ID")
    {
        members.sort_by_member_id();

        if (ui->searchNameLineEdit->text() != "")
            display_found(ui->searchNameLineEdit->text());
        else if (ui->searchIDLineEdit->text() != "" || ui->searchYearLineEdit->text() != "")
            on_confirmSearchPushButton_clicked();
        else
            display();

    } else if (arg1 == "Membership Expiration")
    {
        members.sort_by_date();

        if (ui->searchNameLineEdit->text() != "")
            display_found(ui->searchNameLineEdit->text());
        else if (ui->searchIDLineEdit->text() != "" || ui->searchYearLineEdit->text() != "")
            on_confirmSearchPushButton_clicked();
        else
            display();
    }
}

void MainWindow::on_viewTotalPurchasesPushButton_clicked()
{
    // variables              DATA TABLE
    QString totalPurchases;   //  OUT - the member's purchase history that will
                              //        be displayed with the member info text
                              //        browser
    SaleContainer purchases;  // CALC - the member's purchases
    int id;                   // CALC - the ID of the member whose purchases are
                              //        to be shown

    id = ui->membersTableWidget->item(active_row, 1)->text().toInt();
    totalPurchases = "";

    // PROC: If the push button below the member info text browser shows "View
    //       Total Purchases," display the member's total purchases. If it shows
    //       "View Member Info," display the member's info.
    if (ui->viewTotalPurchasesPushButton->text() == "View Total Purchases")
    {
        for (int i = 0; i < members.size(); i++)
        {
            if (members[i].get_member_id() == id)
            {
                purchases = members[i].get_purchases();

                totalPurchases = "Name: " + QString::fromStdString(members[i].get_name()) + "\n";
                totalPurchases += "ID#: " + QString::number(members[i].get_member_id()) + "\n\n";

                if (purchases.size() == 0)
                    totalPurchases += "          No Purchases\n\n";
                else
                    totalPurchases += "          Total Purchases\n\n";

                for (int j = 0; j < purchases.size(); j++)
                {
                    totalPurchases += "Item: " + QString::fromStdString(purchases[j].item.name) + "\n";
                    totalPurchases += "Price: $" + QString::number(purchases[j].item.price, 'f', 2) + "\n";
                    totalPurchases += "Quantity: " + QString::number(purchases[j].quantity) + "\n";
                    totalPurchases += "Date: " + QString::fromStdString(purchases[j].getDate()) + "\n\n";
                }

                break;
            }
        }

        ui->viewTotalPurchasesPushButton->setText("View Member Info");
        ui->memberInfoTextBrowser->setText(totalPurchases);
    }
    else
    {
        display_member_info(id);
    }
}

void MainWindow::on_dailySalesReportRadioButton_clicked()
{
    // PROC: make ui changes
    ui->salesReportMonthLabel   ->setEnabled(true);
    ui->salesReportMonthLineEdit->setEnabled(true);
    ui->salesReportDayLabel     ->setEnabled(true);
    ui->salesReportDayLineEdit  ->setEnabled(true);
    ui->salesReportYearLabel    ->setEnabled(true);
    ui->salesReportYearLineEdit ->setEnabled(true);
}

void MainWindow::on_monthlySalesReportRadioButton_clicked()
{
    // PROC: make ui changes
    ui->salesReportMonthLabel   ->setEnabled(true);
    ui->salesReportMonthLineEdit->setEnabled(true);
    ui->salesReportDayLabel     ->setDisabled(true);
    ui->salesReportDayLineEdit  ->setDisabled(true);
    ui->salesReportYearLabel    ->setEnabled(true);
    ui->salesReportYearLineEdit ->setEnabled(true);
    ui->salesReportDayLineEdit  ->clear();
}

void MainWindow::on_yearlySalesReportRadioButton_clicked()
{
    // PROC: make ui changes
    ui->salesReportMonthLabel   ->setDisabled(true);
    ui->salesReportMonthLineEdit->setDisabled(true);
    ui->salesReportDayLabel     ->setDisabled(true);
    ui->salesReportDayLineEdit  ->setDisabled(true);
    ui->salesReportYearLabel    ->setEnabled(true);
    ui->salesReportYearLineEdit ->setEnabled(true);
    ui->salesReportDayLineEdit  ->clear();
    ui->salesReportMonthLineEdit->clear();
}

void MainWindow::on_generateSalesReportPushButton_clicked()
{
    // variables               DATA TABLE
    double total_revenue;      // CALC/OUT - total revenue for the day/month/yr
    bool exists;               //     CALC - true if an item in the items_sold
                               //            container is already displayed on
                               //            the table
    bool dateMatches;          //     CALC - true if the item's purchase date
                               //            matches the specified day/month/yr
    int basic_members;         // CALC/OUT - # of Basic members who shopped
    int preferred_members;     // CALC/OUT - # of Preferred members who shopped
    unsigned month;            //   IN/OUT - report month
    unsigned day;              //   IN/OUT - report day
    unsigned year;             //   IN/OUT - report year
    int index;                 //     CALC - indexing variable for various loops
    int a;                     //     CALC - indexing variable for various loops
    QString summary_msg;       //      OUT - report summary info to be displayed
                               //            on the reports summary text browser
    QString best_items[3];     //      OUT - 3 best performing items by revenue
    QString worst_items[3];    //      OUT - 3 worst performing items by revenue
    double best_revenues[3];   // CALC/OUT - 3 best revenue amounts
    double worst_revenues[3];  // CALC/OUT - 3 worst revenue amounts

    total_revenue = 0;
    dateMatches = false;
    basic_members = 0;
    preferred_members = 0;
    month = 0;
    day   = 0;
    year  = 0;
    summary_msg = "";
    items_sold_that_time.clear();
    members_shopped_that_time.clear();

    // PROC: acquire the date entered by the user
    if (ui->dailySalesReportRadioButton->isChecked())
    {
        month = ui->salesReportMonthLineEdit->text().toInt();
        day   = ui->salesReportDayLineEdit->text().toInt();
        year  = ui->salesReportYearLineEdit->text().toInt();
    }
    else if (ui->monthlySalesReportRadioButton->isChecked())
    {
        month = ui->salesReportMonthLineEdit->text().toInt();
        day   = 1;
        year  = ui->salesReportYearLineEdit->text().toInt();
    }
    else if (ui->yearlySalesReportRadioButton->isChecked())
    {
        month = 1;
        day   = 1;
        year  = ui->salesReportYearLineEdit->text().toInt();
    }

    // PROC: test the date entry for validity (contingency handling)
    Date test_date(month, day, year);
    if (test_date.get_month() != month || test_date.get_day() != day || test_date.get_year() != year || year > 2021 || year < 1990)
    {
        // OUT: if the date entry is invalid, tell the user
        ui->salesReportInvalidEntryLabel->show();
        return;
    }
    else
    {
        ui->salesReportInvalidEntryLabel->hide();
    }

    // PROC: Compile a list of items purchased in that day/month/year. Compile a
    //       list of members who shopped during that day/month/year.
    for (int i = 0; i < items_sold.size(); i++)
    {
        // PROC: check each item if it was purchase in that day/month/year
        if (ui->dailySalesReportRadioButton->isChecked())
            dateMatches = (items_sold[i].date_of_purchase == test_date);
        else if (ui->monthlySalesReportRadioButton->isChecked())
            dateMatches = (items_sold[i].date_of_purchase.get_month() == test_date.get_month() &&
                           items_sold[i].date_of_purchase.get_year()  == test_date.get_year());
        else if (ui->yearlySalesReportRadioButton->isChecked())
            dateMatches = (items_sold[i].date_of_purchase.get_year() == test_date.get_year());

        // PROC: Add the item to the items_sold_that_time container. If the item
        //       already exists in the container, simply increase the quantity
        //       sold.
        if (dateMatches)
        {
            items_sold_that_time.add_sale(items_sold[i]);

            exists = false;
            for (int j = 0; j < members_shopped_that_time.size(); j++)
            {
                if (members_shopped_that_time[j].get_member_id() == items_sold[i].getID())
                {
                    exists = true;
                    break;
                }
            }

            // PROC: add members to the members_shopped_that_time container who
            //       bought that particular item
            if (!exists)
            {
                for (int j = 0; j < members.size(); j++)
                {
                    if (items_sold[i].getID() == members[j].get_member_id())
                    {
                        members_shopped_that_time.add_member(members[j].get_name(), members[j].get_member_id(), members[j].get_type(), members[j].get_expiration_date());
                        break;
                    }
                }
            }
        }
    }

    // OUT: display items sold in that day/month/year
    display_items_sold_no_dup(items_sold_that_time);

    // OUT: make ui changes
    if (ui->dailySalesReportRadioButton->isChecked())
    {
        if (ui->reportsAllMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing sales report for " + QString::fromStdString(test_date.returnNumeric()));
        else if (ui->reportsPreferredMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing sales report for " + QString::fromStdString(test_date.returnNumeric()) + " for Preferred members");
        else if (ui->reportsBasicMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing sales report for " + QString::fromStdString(test_date.returnNumeric()) + " for Basic members");

        ui->reportsItemsSoldLabel->setText("Items sold on that day");
        ui->reportsMembersShoppedLabel->setText("Members who shopped that day");
        ui->reportsNotificationLabel->show();
    }
    else if (ui->monthlySalesReportRadioButton->isChecked())
    {
        if (ui->reportsAllMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing sales report for " + QString::number(test_date.get_month()) + "/" + QString::number(test_date.get_year()));
        else if (ui->reportsPreferredMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing sales report for " + QString::number(test_date.get_month()) + "/" + QString::number(test_date.get_year()) + " for Preferred members");
        else if (ui->reportsBasicMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing sales report for " + QString::number(test_date.get_month()) + "/" + QString::number(test_date.get_year()) + " for Basic members");

        ui->reportsItemsSoldLabel->setText("Items sold that month");
        ui->reportsMembersShoppedLabel->setText("Members who shopped that month");
        ui->reportsNotificationLabel->show();
    }
    else if (ui->yearlySalesReportRadioButton->isChecked())
    {
        if (ui->reportsAllMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing sales report for year " + QString::number(test_date.get_year()));
        else if (ui->reportsPreferredMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing sales report for year " + QString::number(test_date.get_year()) + " for Preferred members");
        else if (ui->reportsBasicMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing sales report for year " + QString::number(test_date.get_year()) + " for Basic members");

        ui->reportsItemsSoldLabel->setText("Items sold that year");
        ui->reportsMembersShoppedLabel->setText("Members who shopped that year");
        ui->reportsNotificationLabel->show();
    }

    // PROC: If the Preferred members radio button is checked, remove all Basic
    //       members from the members_shopped_that_time container. If the Basic
    //       members radio is checked, remove all Preferred members from the
    //       container.
    if (ui->reportsPreferredMembersRadioButton->isChecked())
    {
        index = 0;
        while (index != members_shopped_that_time.size())
        {
            if (members_shopped_that_time[index].get_type() == false)
                members_shopped_that_time.remove_member_by_index(index);
            else
                index++;
        }
    }
    else if (ui->reportsBasicMembersRadioButton->isChecked())
    {

        index = 0;
        while (index != members_shopped_that_time.size())
        {
            if (members_shopped_that_time[index].get_type() == true)
                members_shopped_that_time.remove_member_by_index(index);
            else
                index++;
        }
    }

    // PROC: calculate the total revenue for that day/month/year
    for (int i = 0; i < ui->reportsItemsSoldTableWidget->rowCount(); i++)
        total_revenue += stod(ui->reportsItemsSoldTableWidget->item(i,1)->text().toStdString().erase(0,1)) *
                              ui->reportsItemsSoldTableWidget->item(i,2)->text().toInt();

    for (int i = 0; i < members_shopped_that_time.size(); i++)
    {
        if (members_shopped_that_time[i].get_type() == true)
            preferred_members++;
        else
            basic_members++;
    }

    // PROC: display the list of members who shopped by calling this function so
    //       that the order of the members displayed matches the current
    //       selection in the members shopped "Sort By" combo box
    on_membersShoppedSortByComboBox_currentTextChanged(ui->membersShoppedSortByComboBox->currentText());

    // PROC: find the three highest revenue figures in the current list of items
    //       sold
    for (a = 0; a < 3; a++)
    {
        if (a == ui->reportsItemsSoldTableWidget->rowCount())
            break;

        best_revenues[a] = stod(ui->reportsItemsSoldTableWidget->item(a, 3)->text().toStdString().erase(0,1));
    }
    sort(best_revenues, best_revenues + a);
    for (int i = 3; i < ui->reportsItemsSoldTableWidget->rowCount(); i++)
    {
        for (int j = 0; j < a; j++)
        {
            if (stod(ui->reportsItemsSoldTableWidget->item(i,3)->text().toStdString().erase(0,1)) > best_revenues[j])
            {
                best_revenues[j] = stod(ui->reportsItemsSoldTableWidget->item(i,3)->text().toStdString().erase(0,1));
                sort(best_revenues, best_revenues + a);
                break;
            }
        }
    }

    // PROC: find the three items with the highest revenue figures
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < ui->reportsItemsSoldTableWidget->rowCount(); j++)
        {
            if (stod(ui->reportsItemsSoldTableWidget->item(j,3)->text().toStdString().erase(0,1)) == best_revenues[i])
            {
                best_items[i] = ui->reportsItemsSoldTableWidget->item(j,0)->text();
                break;
            }
        }
    }

    // PROC: find the three lowest revenue figures in the current list of items
    //       sold
    for (a = 0; a < 3; a++)
    {
        if (a == ui->reportsItemsSoldTableWidget->rowCount())
            break;

        worst_revenues[a] = stod(ui->reportsItemsSoldTableWidget->item(a, 3)->text().toStdString().erase(0,1));
    }
    sort(worst_revenues, worst_revenues + a);
    for (int i = 3; i < ui->reportsItemsSoldTableWidget->rowCount(); i++)
    {
        for (int j = 0; j < a; j++)
        {
            if (stod(ui->reportsItemsSoldTableWidget->item(i,3)->text().toStdString().erase(0,1)) < worst_revenues[j])
            {
                worst_revenues[j] = stod(ui->reportsItemsSoldTableWidget->item(i,3)->text().toStdString().erase(0,1));
                sort(worst_revenues, worst_revenues + a);
                break;
            }
        }
    }

    // PROC: find the three items with the lowest revenue figures
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < ui->reportsItemsSoldTableWidget->rowCount(); j++)
        {
            if (stod(ui->reportsItemsSoldTableWidget->item(j,3)->text().toStdString().erase(0,1)) == worst_revenues[i])
            {
                worst_items[i] = ui->reportsItemsSoldTableWidget->item(j,0)->text();
                break;
            }
        }
    }

    // PROC: compile the report summary text and add it to summary_msg
    if (ui->dailySalesReportRadioButton->isChecked())
        summary_msg += "Total revenue for " + QString::fromStdString(test_date.returnAlpha()) +
                       "\n                    $" + QString::number(total_revenue, 'f', 2) + "\n\n";
    else if (ui->monthlySalesReportRadioButton->isChecked())
        summary_msg += "Total revenue for " + QString::fromStdString(test_date.get_month_name()) +
                       " " + QString::number(test_date.get_year()) + "\n                    $" +
                       QString::number(total_revenue, 'f', 2) + "\n\n";
    else if (ui->yearlySalesReportRadioButton->isChecked())
        summary_msg += "Total revenue for year " + QString::number(test_date.get_year()) +
                       "\n                    $" + QString::number(total_revenue, 'f', 2) + "\n\n";

    summary_msg += "# of members who shopped...\n";
    summary_msg += "Preferred: " + QString::number(preferred_members) + "\n";
    summary_msg += "Basic: " + QString::number(basic_members) + "\n\n";
    summary_msg += "         Best performing items\n";
    summary_msg += "By revenue:\n";

    for (int i = a - 1; i >= 0; i--)
        summary_msg += " " + QString::number(abs(i - a)) + ". " + best_items[i] + "($" + QString::number(best_revenues[i], 'f', 2) + ")\n";

    summary_msg += "By quantity:\n";
    items_sold_that_time.sort_by_quantity(true);

    // PROC: find the three items with the highest quantity sold
    for (int i = 0; i < 3; i++)
    {
        if (i == ui->reportsItemsSoldTableWidget->rowCount())
            break;

        summary_msg += " " + QString::number(i + 1) + ". " + QString::fromStdString(items_sold_that_time[i].getItemName()) + "(" + QString::number(items_sold_that_time[i].getQuantity()) + ")\n";
    }

    summary_msg += "\n        Worst performing items\n";

    summary_msg += "By revenue:\n";

    for (int i = 0; i < a; i++)
        summary_msg += " " + QString::number(i + 1) + ". " + worst_items[i] + "($" + QString::number(worst_revenues[i], 'f', 2) + ")\n";

    summary_msg += "By quantity:\n";
    items_sold_that_time.sort_by_quantity(false);

    // PROC: find the three items with the lowest quantity sold
    for (int i = 0; i < 3; i++)
    {
        if (i == ui->reportsItemsSoldTableWidget->rowCount())
            break;

        summary_msg += " " + QString::number(i + 1) + ". " + QString::fromStdString(items_sold_that_time[i].getItemName()) + "(" + QString::number(items_sold_that_time[i].getQuantity()) + ")\n";
    }

    // PROC & OUT: make ui changes and display the report summary
    ui->reportsSummaryTextBrowser->setText(summary_msg);
    on_itemsSoldSortByComboBox_currentTextChanged(ui->itemsSoldSortByComboBox->currentText());
    ui->additionalInfoTextBrowser->clear();
    ui->reportsSelectToViewLabel->show();
}

void MainWindow::on_salesReportMonthLineEdit_textChanged(const QString &arg1)
{
    // PROC: enable or disable the generate report push button depending on
    //       whether all the required date fields have been filled in
    if (ui->dailySalesReportRadioButton->isChecked())
    {
        if (ui->salesReportDayLineEdit->text() == "" || ui->salesReportMonthLineEdit->text() == "" || ui->salesReportYearLineEdit->text() == "")
            ui->generateSalesReportPushButton->setDisabled(true);
        else
            ui->generateSalesReportPushButton->setEnabled(true);
    }
    else if (ui->monthlySalesReportRadioButton->isChecked())
    {
        if (ui->salesReportMonthLineEdit->text() == "" || ui->salesReportYearLineEdit->text() == "")
            ui->generateSalesReportPushButton->setDisabled(true);
        else
            ui->generateSalesReportPushButton->setEnabled(true);
    }
    else if (ui->yearlySalesReportRadioButton->isChecked())
    {
        if (ui->salesReportYearLineEdit->text() == "")
            ui->generateSalesReportPushButton->setDisabled(true);
        else
            ui->generateSalesReportPushButton->setEnabled(true);
    }
}

void MainWindow::on_salesReportDayLineEdit_textChanged(const QString &arg1)
{
    // PROC: enable or disable the generate report push button depending on
    //       whether all the required date fields have been filled in
    if (ui->dailySalesReportRadioButton->isChecked())
    {
        if (ui->salesReportDayLineEdit->text() == "" || ui->salesReportMonthLineEdit->text() == "" || ui->salesReportYearLineEdit->text() == "")
            ui->generateSalesReportPushButton->setDisabled(true);
        else
            ui->generateSalesReportPushButton->setEnabled(true);
    }
    else if (ui->monthlySalesReportRadioButton->isChecked())
    {
        if (ui->salesReportMonthLineEdit->text() == "" || ui->salesReportYearLineEdit->text() == "")
            ui->generateSalesReportPushButton->setDisabled(true);
        else
            ui->generateSalesReportPushButton->setEnabled(true);
    }
    else if (ui->yearlySalesReportRadioButton->isChecked())
    {
        if (ui->salesReportYearLineEdit->text() == "")
            ui->generateSalesReportPushButton->setDisabled(true);
        else
            ui->generateSalesReportPushButton->setEnabled(true);
    }
}

void MainWindow::on_salesReportYearLineEdit_textChanged(const QString &arg1)
{
    // PROC: enable or disable the generate report push button depending on
    //       whether all the required date fields have been filled in
    if (ui->dailySalesReportRadioButton->isChecked())
    {
        if (ui->salesReportDayLineEdit->text() == "" || ui->salesReportMonthLineEdit->text() == "" || ui->salesReportYearLineEdit->text() == "")
            ui->generateSalesReportPushButton->setDisabled(true);
        else
            ui->generateSalesReportPushButton->setEnabled(true);
    }
    else if (ui->monthlySalesReportRadioButton->isChecked())
    {
        if (ui->salesReportMonthLineEdit->text() == "" || ui->salesReportYearLineEdit->text() == "")
            ui->generateSalesReportPushButton->setDisabled(true);
        else
            ui->generateSalesReportPushButton->setEnabled(true);
    }
    else if (ui->yearlySalesReportRadioButton->isChecked())
    {
        if (ui->salesReportYearLineEdit->text() == "")
            ui->generateSalesReportPushButton->setDisabled(true);
        else
            ui->generateSalesReportPushButton->setEnabled(true);
    }
}

void MainWindow::on_salesReportMonthLineEdit_returnPressed()
{
    on_generateSalesReportPushButton_clicked();
}

void MainWindow::on_salesReportDayLineEdit_returnPressed()
{
    on_generateSalesReportPushButton_clicked();
}

void MainWindow::on_salesReportYearLineEdit_returnPressed()
{
    on_generateSalesReportPushButton_clicked();
}

void MainWindow::on_reportsFindItemClearPushButton_clicked()
{
    // PROC: clear the find item field
    ui->findItemLineEdit->clear();

    // OUT: after the "Clear" push button in the find item area of the reports
    //      tab has been clicked, display all items sold
    if (ui->reportsAllMembersRadioButton->isChecked())
        on_reportsAllMembersRadioButton_clicked();
    else if (ui->reportsPreferredMembersRadioButton->isChecked())
        on_reportsPreferredMembersRadioButton_clicked();
    else if (ui->reportsBasicMembersRadioButton->isChecked())
        on_reportsBasicMembersRadioButton_clicked();
}

void MainWindow::on_reportsAllMembersRadioButton_clicked()
{
    if (ui->showItemsSoldGroupBox->isChecked())
    {
        // OUT: display all items sold
        display_items_sold_no_dup(items_sold);

        // PROC: make ui changes
        on_itemsSoldSortByComboBox_currentTextChanged(ui->itemsSoldSortByComboBox->currentText());
        ui->additionalInfoTextBrowser->clear();
        ui->reportsSelectToViewLabel->show();
    }
}

void MainWindow::on_reportsPreferredMembersRadioButton_clicked()
{
    if (ui->showItemsSoldGroupBox->isChecked())
    {
        // OUT: display all items sold to Preferred members
        display_items_sold_no_dup(items_sold);

        // PROC: make ui changes
        on_itemsSoldSortByComboBox_currentTextChanged(ui->itemsSoldSortByComboBox->currentText());
        ui->additionalInfoTextBrowser->clear();
        ui->reportsSelectToViewLabel->show();
    }
}

void MainWindow::on_reportsBasicMembersRadioButton_clicked()
{
    if (ui->showItemsSoldGroupBox->isChecked())
    {
        // OUT: display all items sold to Basic members
        display_items_sold_no_dup(items_sold);

        // PROC: make ui changes
        on_itemsSoldSortByComboBox_currentTextChanged(ui->itemsSoldSortByComboBox->currentText());
        ui->additionalInfoTextBrowser->clear();
        ui->reportsSelectToViewLabel->show();
    }
}

void MainWindow::on_itemsSoldSortByComboBox_currentTextChanged(const QString &arg1)
{
    SaleContainer items;    // CALC - contains the items currently displayed on
                            //        the items sold table

    // PROC: add the items currently displayed on the items sold table to the
    //       items container
    if (ui->showItemsSoldGroupBox->isChecked())
    {
        for (int i = 0; i < ui->itemsSoldOnlyTableWidget->rowCount(); i++)
            items.add_sale(Sale(Item(ui->itemsSoldOnlyTableWidget->item(i, 0)->text().toStdString(), stod(ui->itemsSoldOnlyTableWidget->item(i, 1)->text().toStdString().erase(0,1))), Date(), 0, ui->itemsSoldOnlyTableWidget->item(i, 2)->text().toInt()));
    }
    else if (ui->salesReportGroupBox->isChecked())
    {
        for (int i = 0; i < ui->reportsItemsSoldTableWidget->rowCount(); i++)
            items.add_sale(Sale(Item(ui->reportsItemsSoldTableWidget->item(i, 0)->text().toStdString(), stod(ui->reportsItemsSoldTableWidget->item(i, 1)->text().toStdString().erase(0,1))), Date(), 0, ui->reportsItemsSoldTableWidget->item(i, 2)->text().toInt()));
    }

    // PROC: sort the list of items
    if (arg1 == "Name")
        items.sort_by_name();
    else if (arg1 == "Price (>)")
        items.sort_by_price(true);
    else if (arg1 == "Price (<)")
        items.sort_by_price(false);
    else if (arg1 == "Quantity Sold (>)")
        items.sort_by_quantity(true);
    else if (arg1 == "Quantity Sold (<)")
        items.sort_by_quantity(false);

    // PROC: display the list of items
    display_items_sold(items);
}

void MainWindow::on_reportsFindItemSearchPushButton_clicked()
{
    // variables            DATA TABLE
    int rows;               // CALC - used for displaying item search results in
                            //        the table
    int index;              // CALC - the index position of the item in the item
                            //        list that contains the string inputted in
                            //        find item field as a substring
    Sale the_item;          // CALC - one of the items that constitute the
                            //        search results
    SaleContainer items;    // CALC - contains the items currently displayed on
                            //        the items sold table
    QString notice;         //  OUT - this will be set as the notification
                            //        telling the user that the program is
                            //        showing results for the user's search
    QString itemName;       //  IN  - the entry that the user provided in the
                            //        find item field

    QTableWidget * theTable;    // CALC - used to display search results

    rows  = 0;
    theTable = ui->itemsSoldOnlyTableWidget;

    if (ui->findItemLineEdit->text() != "")
    {
        // PROC: make ui changes
        ui->additionalInfoTextBrowser->clear();
        ui->reportsSelectToViewLabel->show();

        itemName = ui->findItemLineEdit->text();
        notice = "Showing results for '" + itemName + "'";

        ui->reportsNotificationLabel->setText(notice);

        // PROC: add the items currently displayed on the items sold table to
        //       the items container
        for (int i = 0; i < theTable->rowCount(); i++)
            items.add_sale(Sale(Item(theTable->item(i, 0)->text().toStdString(),
                                     stod(theTable->item(i, 1)->text().toStdString().erase(0,1))),
                                Date(), 0, theTable->item(i, 2)->text().toInt()));

        // PROC: check each item to see if its name contains the user's entry as
        //       a substring
        for (int i = 0; i < items.size(); i++)
        {
            // PROC: the find function returns the index position of the item
            //       whose name contains the user's entry as a substring
            index = items.find(itemName.toStdString(), i);

            // PROC: index >= 0 if an item is found to contain the user's entry
            if (index >= 0)
            {
                the_item = items[index];

                rows++;
                theTable->setRowCount(rows);
                theTable->setColumnCount(4);

                // OUT: display the found item on the new row
                theTable->setItem(rows - 1, 0, new QTableWidgetItem(QString::fromStdString(the_item.getItemName())));
                theTable->setItem(rows - 1, 1, new QTableWidgetItem("$" + QString::number(the_item.getItemPrice(), 'f', 2)));
                theTable->setItem(rows - 1, 2, new QTableWidgetItem(QString::number(the_item.getQuantity())));
                theTable->setItem(rows - 1, 3, new QTableWidgetItem("$" + (QString::number(the_item.getItemPrice() * the_item.getQuantity()))));

                i = index;
            }
            else
            {
                break;
            }
        }

        // PROC & OUT: if there are no search results (if the number of rows is
        //             zero), let the user know
        if (rows == 0)
        {
            notice = "No results for '" + itemName + "'";
            ui->reportsNotificationLabel->setText(notice);

            theTable->setRowCount(rows);
            theTable->setColumnCount(4);
        }
    }
}

void MainWindow::on_findItemLineEdit_returnPressed()
{
    on_reportsFindItemSearchPushButton_clicked();
}

void MainWindow::on_membersShoppedSortByComboBox_currentTextChanged(const QString &arg1)
{
    QTableWidget * theTable;    // CALC - used to display the sorted member list

    // PROC: sort the members shopped list by whatever the user selected in the
    //       sort combo box
    if (arg1 == "Name")
        members_shopped_that_time.sort_by_name();
    else if (arg1 == "Member ID")
        members_shopped_that_time.sort_by_member_id();
    else if (arg1 == "Member Exp.")
        members_shopped_that_time.sort_by_date();

    theTable = ui->reportsMembersShoppedTableWidget;
    theTable->setRowCount(0);

    // OUT: display the sorted member list
    for (int i = 0; i < members_shopped_that_time.size(); i++)
    {
        theTable->insertRow(i);

        theTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(members_shopped_that_time[i].get_name())));
        theTable->setItem(i, 1, new QTableWidgetItem(QString::number(members_shopped_that_time[i].get_member_id())));

        if (members_shopped_that_time[i].get_type() == true)
            theTable->setItem(i, 2, new QTableWidgetItem("Preferred"));
        else
            theTable->setItem(i, 2, new QTableWidgetItem("Basic"));

        theTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(members_shopped_that_time[i].get_expiration_date().returnNumeric())));
    }
}

void MainWindow::on_reportsItemsSoldTableWidget_cellClicked(int row, int column)
{
    QString item_name;    // CALC - name of the item that the user clicked

    ui->reportsSelectToViewLabel->hide();

    active_row = row;
    item_name = ui->reportsItemsSoldTableWidget->item(active_row, 0)->text();

    // OUT: display the item's info in the additional info text browser
    display_item_info(item_name);
}

void MainWindow::on_itemsSoldOnlyTableWidget_cellClicked(int row, int column)
{
    QString item_name;    // CALC - name of the item that the user clicked

    ui->reportsSelectToViewLabel->hide();

    active_row = row;
    item_name = ui->itemsSoldOnlyTableWidget->item(active_row, 0)->text();

    // OUT: display the item's info in the additional info text browser
    display_item_info(item_name);
}

/*
void MainWindow::on_reportsRebateButton_clicked()
{
    if(ui->additionalReportsGroupBox->isChecked())
    {
        ui->reportsItemsSoldLabel->setText("Rebate Report");
    }
}
/*

/*
void MainWindow::on_reportsMembershipDues_clicked()
{
    if(ui->additionalReportsGroupBox->isChecked())
    {
        ui->reportsItemsSoldLabel->setText("Membership Dues");
    }
}
*/

void MainWindow::on_additionalReportsGroupBox_toggled(bool arg1)
{
    QTableWidget * theTable;    // CALC - used for displaying the rebate and
                                //        membership dues report

    // PROC: make ui changes
    if (arg1)
    {
        ui->showItemsSoldGroupBox->setChecked(false);
        ui->salesReportGroupBox->setChecked(false);

        ui->additionaReportsTableWidget ->show();
        ui->reportsItemsSoldTableWidget ->hide();
        ui->membersShoppedSortByLabel   ->hide();
        ui->membersShoppedSortByComboBox->hide();
        ui->reportsMembersShoppedLabel  ->hide();
        ui->itemsSoldOnlyTableWidget    ->hide();
        ui->reportsSummaryGroupBox      ->hide();
        ui->reportsSummaryTextBrowser   ->hide();
        ui->reportsNotificationLabel    ->hide();
        ui->salesReportMonthLineEdit    ->clear();
        ui->salesReportDayLineEdit      ->clear();
        ui->salesReportYearLineEdit     ->clear();
        ui->dailySalesReportRadioButton ->click();
        ui->reportsItemsSoldTableWidget ->clearContents();
        ui->reportsItemsSoldTableWidget ->setRowCount(0);
        ui->reportsSummaryTextBrowser   ->clear();
        ui->reportsSummaryGroupBox      ->hide();
        ui->additionalInfoTextBrowser   ->clear();
        ui->reportsSelectToViewLabel    ->hide();
        ui->reportsItemsSoldTableWidget ->clear();
        ui->reportsMembersShoppedTableWidget->clearContents();
        ui->reportsMembersShoppedTableWidget->setRowCount(0);
        ui->reportsMembersShoppedTableWidget->hide();

        ui->reportsItemsSoldLabel->setText("Additional Reports");
    }

    // OUT: display rebate and membership dues report
    theTable = ui->additionaReportsTableWidget;
    theTable->setColumnCount(4);
    theTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Member Name"));
    theTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Member ID"));
    theTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Membership Dues"));
    theTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Rebate"));

    theTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    theTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    theTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    theTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    theTable->clearContents();
    theTable->setRowCount(members.size());

    for(int i = 0; i < members.size(); i++)
    {
        theTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(members[i].get_name())));
        theTable->setItem(i, 1, new QTableWidgetItem(QString::number(members[i].get_member_id())));
        theTable->setItem(i, 2, new QTableWidgetItem("$" + QString::number(members[i].get_annual_dues())));
        theTable->setItem(i, 3, new QTableWidgetItem("$" + QString::number(members[i].get_rebate())));
    }
}

void MainWindow::on_showItemsSoldGroupBox_toggled(bool arg1)
{
    // PROC: make ui changes
    if (arg1)
    {
        ui->salesReportGroupBox->setChecked(false);
        //ui->additionalReportsGroupBox->setChecked(false);

        ui->additionaReportsTableWidget ->hide();
        ui->reportsItemsSoldTableWidget ->hide();
        ui->membersShoppedSortByLabel   ->hide();
        ui->membersShoppedSortByComboBox->hide();
        ui->reportsMembersShoppedLabel  ->hide();
        ui->itemsSoldOnlyTableWidget    ->show();
        ui->reportsSummaryGroupBox      ->hide();
        ui->reportsSummaryTextBrowser   ->hide();
        ui->reportsNotificationLabel    ->hide();
        ui->salesReportMonthLineEdit    ->clear();
        ui->salesReportDayLineEdit      ->clear();
        ui->salesReportYearLineEdit     ->clear();
        ui->dailySalesReportRadioButton ->click();
        ui->reportsItemsSoldTableWidget ->clearContents();
        ui->reportsItemsSoldTableWidget ->setRowCount(0);
        ui->reportsSummaryTextBrowser   ->clear();
        ui->reportsSummaryGroupBox      ->hide();
        ui->additionalInfoTextBrowser   ->clear();
        ui->reportsSelectToViewLabel    ->show();
        ui->reportsMembersShoppedTableWidget->hide();
        ui->reportsMembersShoppedTableWidget->setRowCount(0);
        ui->reportsMembersShoppedTableWidget->clearContents();

        if (ui->reportsAllMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing all items sold");
        else if (ui->reportsPreferredMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing items sold to Preferred members");
        else if (ui->reportsBasicMembersRadioButton->isChecked())
            ui->reportsNotificationLabel->setText("Showing items sold to Basic members");

        // OUT: display items sold
        display_items_sold_no_dup(items_sold);
    }
}

void MainWindow::on_salesReportGroupBox_toggled(bool arg1)
{
    // PROC: make ui changes
    if (arg1)
    {
        ui->showItemsSoldGroupBox->setChecked(false);
        //ui->additionalReportsGroupBox->setChecked(false);

        ui->additionaReportsTableWidget ->hide();
        ui->reportsItemsSoldTableWidget ->show();
        ui->membersShoppedSortByLabel   ->show();
        ui->membersShoppedSortByComboBox->show();
        ui->reportsMembersShoppedLabel  ->show();
        ui->itemsSoldOnlyTableWidget    ->hide();
        ui->reportsSummaryGroupBox      ->show();
        ui->reportsSummaryTextBrowser   ->show();
        ui->itemsSoldOnlyTableWidget    ->clearContents();
        ui->itemsSoldOnlyTableWidget    ->setRowCount(0);
        ui->additionalInfoTextBrowser   ->clear();
        ui->reportsSelectToViewLabel    ->show();
        ui->reportsNotificationLabel    ->hide();
        ui->reportsMembersShoppedLabel  ->setText("Members who shopped");
        ui->reportsItemsSoldLabel       ->setText("Items sold");
        ui->reportsFindItemClearPushButton->click();
        ui->reportsMembersShoppedTableWidget->show();
    }
}

void MainWindow::on_importPushButton_1_clicked()
{
    MemberContainer addMembers;    //  IN  - list of members from new file
    bool exists;
    int i;                         // CALC - for loop indexing
    int j;                         // CALC - for loop indexing

    // PROC: the load function from the MemberContainer class returns 0 if file
    //       is opened and loaded successfully, returns 1 if there was an error
    if (addMembers.load(ui->filePathLineEdit_1->text()) == 0)
    {
        ui->noFileFoundLabel_1->hide();

        for (i = 0; i < addMembers.size(); i++)
        {
            exists = false;
            for (j = 0; j < members.size(); j++)
            {
                if (addMembers[i].get_member_id() == members[j].get_member_id())
                {
                    exists = true;
                    break;
                }
            }

            if (!exists)
                members.add_member(addMembers[i]);
        }

        // PROC: update member information from imported sales file
        add_purchases();

        ui->filePathLineEdit_1->selectAll();
        ui->memberListUpdatedLabel->show();
        on_sortByComboBox_currentTextChanged(ui->sortByComboBox->currentText());
        ui->displayAllMembersRadioButton->click();
        ui->reportsAllMembersRadioButton->click();
    }
    else
    {
        ui->noFileFoundLabel_1->show();
    }
}

void MainWindow::on_importPushButton_2_clicked()
{
    SaleContainer addSales;    //  IN  - list of sales from new file
    int i;                     // CALC - for loop indexing

    // PROC: the load function from the SaleContainer class returns 0 if file
    //       is opened and loaded successfully, returns 1 if there was an error
    if (addSales.load(ui->filePathLineEdit_2->text()) == 0)
    {
        ui->noFileFoundLabel_2->hide();

        for (i = 0; i < addSales.size(); i++)
            items_sold.add_sale(addSales[i]);

        // PROC: update member information from imported sales file
        add_purchases();

        ui->filePathLineEdit_2->selectAll();
        ui->salesListUpdatedLabel->show();
        on_sortByComboBox_currentTextChanged(ui->sortByComboBox->currentText());
        ui->displayAllMembersRadioButton->click();
        ui->reportsAllMembersRadioButton->click();
    }
    else
    {
        ui->noFileFoundLabel_2->show();
    }
}

void MainWindow::on_findItemLineEdit_textChanged(const QString &arg1)
{
    if (arg1 == "")
        ui->reportsFindItemClearPushButton->click();
}

void MainWindow::on_chooseFilePushButton_1_clicked()
{
    QString fileName;    // CALC - path of member file

    fileName = QFileDialog::getOpenFileName(this, tr("Open Members File"));
    ui->filePathLineEdit_1->setText(fileName);
}

void MainWindow::on_chooseFilePushButton_2_clicked()
{
    QString fileName;    // CALC - path of sales file

    fileName = QFileDialog::getOpenFileName(this, tr("Open Sales File"));
    ui->filePathLineEdit_2->setText(fileName);
}

void MainWindow::on_tabs_currentChanged(int index)
{
    ui->memberListUpdatedLabel->hide();
    ui->salesListUpdatedLabel->hide();
}
