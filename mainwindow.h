#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "date.h"
#include "member.h"
#include "membercontainer.h"
#include "salecontainer.h"
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Functions for finding saved files
    void findSavedFiles();

    // Functions for displaying information
    void display();
    void display_found(QString name);
    void display_found(int id);
    void display_found(int day, int month, int year);
    void display_member_info(int id);
    void display_items_sold_no_dup(SaleContainer& items);
    void display_items_sold(SaleContainer& items);
    void display_item_info(QString item);

    // Functions for adding purchases
    void add_purchases();

private slots:
    // Slots for handling UI events
    void on_addPushButton_clicked();
    void on_deletePushButton_clicked();
    void on_confirmDeletePushButton_clicked();
    void on_cancelDeletePushButton_clicked();
    void on_membersTableWidget_cellClicked(int row, int column);
    void on_searchNameLineEdit_textEdited(const QString &arg1);
    void on_searchIDLineEdit_textEdited(const QString &arg1);
    void on_searchClearPushButton_clicked();
    void on_searchDayLineEdit_textEdited(const QString &arg1);
    void on_searchMonthLineEdit_textEdited(const QString &arg1);
    void on_searchYearLineEdit_textEdited(const QString &arg1);
    void on_confirmSearchPushButton_clicked();
    void on_searchNameLineEdit_textChanged(const QString &arg1);
    void on_displayAllMembersRadioButton_clicked();
    void on_displayPreferredMembersRadioButton_clicked();
    void on_displayBasicMembersRadioButton_clicked();
    void on_searchIDLineEdit_returnPressed();
    void on_searchDayLineEdit_returnPressed();
    void on_searchMonthLineEdit_returnPressed();
    void on_searchYearLineEdit_returnPressed();
    void on_sortByComboBox_currentTextChanged(const QString &arg1);
    void on_viewTotalPurchasesPushButton_clicked();
    void on_showItemsSoldGroupBox_toggled(bool arg1);
    void on_salesReportGroupBox_toggled(bool arg1);
    void on_dailySalesReportRadioButton_clicked();
    void on_monthlySalesReportRadioButton_clicked();
    void on_yearlySalesReportRadioButton_clicked();
    void on_generateSalesReportPushButton_clicked();
    void on_salesReportMonthLineEdit_textChanged(const QString &arg1);
    void on_salesReportDayLineEdit_textChanged(const QString &arg1);
    void on_salesReportYearLineEdit_textChanged(const QString &arg1);
    void on_salesReportMonthLineEdit_returnPressed();
    void on_salesReportDayLineEdit_returnPressed();
    void on_salesReportYearLineEdit_returnPressed();
    void on_reportsFindItemClearPushButton_clicked();
    void on_reportsAllMembersRadioButton_clicked();
    void on_reportsPreferredMembersRadioButton_clicked();
    void on_reportsBasicMembersRadioButton_clicked();
    void on_itemsSoldSortByComboBox_currentTextChanged(const QString &arg1);
    void on_reportsFindItemSearchPushButton_clicked();
    void on_findItemLineEdit_returnPressed();
    void on_membersShoppedSortByComboBox_currentTextChanged(const QString &arg1);
    void on_reportsItemsSoldTableWidget_cellClicked(int row, int column);
    void on_itemsSoldOnlyTableWidget_cellClicked(int row, int column);
    void on_reportsRebateButton_clicked();
    void on_reportsMembershipDues_clicked();
    void on_additionalReportsGroupBox_toggled(bool arg1);
    void on_importPushButton_1_clicked();
    void on_importPushButton_2_clicked();
    void on_findItemLineEdit_textChanged(const QString &arg1);
    void on_chooseFilePushButton_1_clicked();
    void on_chooseFilePushButton_2_clicked();
    void on_tabs_currentChanged(int index);

public:
    Ui::MainWindow *ui;    // User interface pointer

    MemberContainer members;                // Container for members
    MemberContainer members_shopped_that_time;
    SaleContainer items_sold;               // Container for sold items
    SaleContainer items_sold_that_time;

    bool deleting;                          // Flag for deletion mode
    int display_mode;                       // Display mode: 1 == all, 2 == preferred, 3 == basic
    int active_row;                         // Active row in the table
};

#endif // MAINWINDOW_H
