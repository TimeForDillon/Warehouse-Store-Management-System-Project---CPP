#include "date.h"
#include <iostream>
using namespace std;

/************************************************************
 * Constructor Date: Class Date
 * _________________________________________________________
 *  This method is the default constructor of the Date class.
 *  Default date is January 1, 2000.
 * _________________________________________________________
 *  PRE-CONDITIONS
 *   None
 *
 *  POST-CONDITIONS
 *      Constructs default rational number
 ***********************************************************/
Date::Date()
{
    day = 1;
    month = 1;
    monthName = "January";
    year = 2000;
}

/************************************************************
 * Constructor Date(unsigned m,
 *                  unsigned d,
 *                  unsigned y)): Class Date
 * _________________________________________________________
 *  This method constructs a date given the month, date, and
 *   year as integers.
 * _________________________________________________________
 *  PRE-CONDITIONS
 *   The following need previously defined values:
 *      m: month
 *      d: day
 *      y: year
 *
 *  POST-CONDITIONS
 *      Constructs date with given values.
 ***********************************************************/
Date::Date(unsigned m, // IN: month as integer
           unsigned d, // IN: day
           unsigned y) // IN: year
{
    int num_of_days;    // OUTPUT: number of days in the month

    // OUTPUT: set the month from the given value
    //          if the month is invalid, make it as
    //          close to valid as possible
    if (m == 0)
        month = 1;
    else if (m > 12)
        month = 12;
    else
        month = m;

    // OUTPUT: daysPerMonth -> get the number of days in the month
    num_of_days = daysPerMonth(month, y);

    // OUTPUT: set the day from the given value
    //          if the day is invalid, make it as close
    //          to valid as possible
    if (d < 1)
        day = 1;
    else if (d > num_of_days)
        day = num_of_days;
    else
        day = d;

    // OUTPUT: name -> set the year and month name
    year = y;
    monthName = name(month);

    // OUTPUT: if there was an error when setting the attributes,
    //          display a message and the date it was corrected to
    if (m < 1 || m > 12 || d < 1 || d > num_of_days) {
        cout << "Invalid date values: Date corrected to ";
        printNumeric();
        cout << '.' << endl;
    }
}

/************************************************************
 * Constructor Date(const string &mn,
 *                  unsigned d,
 *                  unsigned y)): Class Date
 * _________________________________________________________
 *  This method constructs a date given the day and year as
 *   integers and the month name as a string.
 * _________________________________________________________
 *  PRE-CONDITIONS
 *   The following need previously defined values:
 *      mn: month name
 *      d: day
 *      y: year
 *
 *  POST-CONDITIONS
 *      Constructs date with month as a string.
 ***********************************************************/
Date::Date(const string &mn,    // IN: month as a string
           unsigned d,          // IN: day
           unsigned y)          // IN: year
{
    int num_of_days;            // OUTPUT: number of days in the month

    // OUTPUT: make the first character of the given month uppercase
    monthName = string() +
                static_cast<char>(toupper(mn[0])) + mn.substr(1, mn.size());

    // OUTPUT: number -> convert the string month to an integer
    month = number(mn);

    if (month != 0) {
        // OUTPUT: check if the day is correct
        num_of_days = daysPerMonth(month, y);
        if (d < 1)
            day = 1;
        else if (d > num_of_days)
            day = num_of_days;
        else
            day = d;

        year = y;

        // OUTPUT: if there was an error, display a message
        if (d < 1 || d > num_of_days) {
        cout << "Invalid date values: Date corrected to ";
        printNumeric();
        cout << '.' << endl;
        }
    }
    else {
        cout << "Invalid month name: the Date was set to 1/1/2000." << endl;
        month = 1;
        day = 1;
        year = 2000;
        monthName = "January";
    }
}

/************************************************************
 * Accessor printNumeric: Class Date
 * _________________________________________________________
 *  This method displays the date in a numeric format
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      None
 *
 *  POST-CONDITIONS
 *      Displays date
 ***********************************************************/
void Date::printNumeric() const
{
    cout << month << '/' << day << '/' << year;
}

/************************************************************
 * Accessor printAlpha: Class Date
 * _________________________________________________________
 *  This method displays the date in an alphabetical format
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      None
 *
 *  POST-CONDITIONS
 *      Displays date
 ***********************************************************/
void Date::printAlpha() const
{
    cout << monthName << ' ' << day << ", " << year;
}

/************************************************************
 * Accessor addDays: Class Date
 * _________________________________________________________
 *  This method adds (or subtracts) days from the date and
 *   returns the result as a new date
 * _________________________________________________________
 *  PRE-CONDITIONS
 *      days: the number of days to add/subtract
 *
 *  POST-CONDITIONS
 *      Returns Date instance;
 ***********************************************************/
Date Date::addDays(int days) const
{
    int current_day = day;
    int current_month = month;
    int current_year = year;
    int daysInMonth;
    int count = 0;
    if (days > 0)
    {
        while (days > 0)
        {
            while (current_month <= 12)
            {
                daysInMonth = daysPerMonth(current_month, current_year);
                while (current_day <= daysInMonth)
                {
                    --days;
                    if (days == 0)
                        return Date(current_month, current_day, current_year);
                    current_day += 1;

                }
                current_day = 1;
                current_month += 1;
            }
            current_month = 1;
            current_year += 1;
        }
    }
    else
    {
        int count = 0;
        while (days < 0)
        {
            while (current_month >= 1)
            {
                while (current_day >= 1)
                {
                    ++days;
                    count += 1;
                    cout << current_month << '/' << current_day << '/' << current_year << '\t' << "days = " << days << endl;
                    current_day -= 1;
                    if (days == 0)
                        return Date(current_month, current_day, current_year);
                }
                current_month -= 1;
                current_day = daysPerMonth(current_month, current_year);
            }
            current_month = 12;
            current_year -= 1;
        }
    }
    return Date(current_month, current_day, current_year);
}

// PRIVATE HELPER FUNCTIONS
/************************************************************
 * Accessor isLeap: Class Date
 * _________________________________________________________
 *  This method determines whether a given year is a leap year
 * _________________________________________________________
 *  PRE-CONDITIONS
 *   The following need previously defined values:
 *      year: the year to check
 *
 *  POST-CONDITIONS
 *      Returns true if leap year, false otherwise
 ***********************************************************/
bool Date::isLeap(unsigned y) const // IN: year to check
{
    if (y % 4 == 0) {
        if (y % 100 == 0)
            if (y % 400 == 0)
                return true;
            return false;
        return true;
    }
    return false;
}

/************************************************************
 * Accessor daysPerMonth: Class Date
 * _________________________________________________________
 *  This method return the number of days in a given month
 * _________________________________________________________
 *  PRE-CONDITIONS
 *   The following need previously defined values:
 *      month: the month to check
 *      year: if leap year, # of days in February changes
 *
 *  POST-CONDITIONS
 *      Returns # of days in the month
 ***********************************************************/
unsigned Date::daysPerMonth(unsigned m,         // IN: month to check
                            unsigned y) const   // IN: year
{
    const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31,
                                 31, 30, 31, 30, 31};
    if (m < 1)
        return 1;
    else if (m > 12)
        return 12;

    if (m == 2)
        if (isLeap(y))
            return 29;
    return daysInMonth[m - 1];
}

/************************************************************
 * Accessor name: Class Date
 * _________________________________________________________
 *  This method converts an integer month into a string
 * _________________________________________________________
 *  PRE-CONDITIONS
 *   The following need previously defined values:
 *      month: the month as an integer
 *
 *  POST-CONDITIONS
 *      Returns a string; the name of the month
 ***********************************************************/
string Date::name(unsigned m) const // IN: month (int)
{
    const string MONTHS[12] = {"January", "February", "March", "April",
                               "May", "June", "July", "August",
                               "September", "October", "November",
                               "December"};
    return MONTHS[m - 1];
}

/************************************************************
 * Accessor number: Class Date
 * _________________________________________________________
 *  This method converts a string month into an integer
 * _________________________________________________________
 *  PRE-CONDITIONS
 *   The following need previously defined values:
 *      month: the month as a string
 *
 *  POST-CONDITIONS
 *      Returns an int; the month as an integer
 ***********************************************************/
unsigned Date::number(const string &mn) const // IN: month (string)
{
    const string MONTHS[12] = {"January", "February", "March", "April",
                               "May", "June", "July", "August",
                               "September", "October", "November",
                               "December"};

    for (int i = 0; i < 12; ++i) {
        if (mn == MONTHS[i])
            return i + 1;
    }
    // if the month doesn't exist, return 0
    return 0;
}

bool Date::operator==(const Date& other)
{
    return this->month == other.month &&
            this->day == other.day &&
            this->year == other.year;
}

string Date::returnAlpha() const
{
    stringstream ss;
    ss << this->monthName << ' ' << this->day << ", " << this->year;
    return ss.str();
}

string Date::returnNumeric() const
{
    stringstream ss;
    if (this->month < 10)
        ss << '0' << this->month;
    else
        ss << this->month;
    ss << '/';
    if (this->day < 10)
        ss << '0' << this->day;
    else
        ss << this->day;
    ss << '/' << this->year;

    return ss.str();
}
