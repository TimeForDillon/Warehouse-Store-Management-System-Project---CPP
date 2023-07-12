#include "date.h"
#include <iostream>
using namespace std;

Date::Date()
{
    // Default constructor: Initializes the date to January 1, 2000
    day = 1;
    month = 1;
    monthName = "January";
    year = 2000;
}

Date::Date(unsigned m, unsigned d, unsigned y)
{
    // Parameterized constructor: Initializes the date based on provided month, day, and year values
    // The month and day values are adjusted to valid ranges if necessary
    // If there was an error setting the date attributes, a correction is made and a message is displayed
    int num_of_days = daysPerMonth(month, y);

    if (m == 0)
        month = 1;
    else if (m > 12)
        month = 12;
    else
        month = m;

    if (d < 1)
        day = 1;
    else if (d > num_of_days)
        day = num_of_days;
    else
        day = d;

    year = y;
    monthName = name(month);

    if (m < 1 || m > 12 || d < 1 || d > num_of_days) {
        cout << "Invalid date values: Date corrected to ";
        printNumeric();
        cout << '.' << endl;
    }
}

Date::Date(const string &mn, unsigned d, unsigned y)
{
    // Parameterized constructor: Initializes the date based on provided month name, day, and year values
    // The month name is converted to an integer month value and validated
    // The day value is adjusted to a valid range if necessary
    // If there was an error setting the date attributes, a correction is made and a message is displayed
    int num_of_days = daysPerMonth(month, y);
    monthName = string() + static_cast<char>(toupper(mn[0])) + mn.substr(1, mn.size());

    month = number(mn);

    if (month != 0) {
        if (d < 1)
            day = 1;
        else if (d > num_of_days)
            day = num_of_days;
        else
            day = d;

        year = y;

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

void Date::printNumeric() const
{
    // Prints the date in numeric format (mm/dd/yyyy)
    cout << month << '/' << day << '/' << year;
}

void Date::printAlpha() const
{
    // Prints the date in alpha format (monthName day, year)
    cout << monthName << ' ' << day << ", " << year;
}

Date Date::addDays(int days) const
{
    // Adds the specified number of days to the date and returns the resulting date
    // The days value can be positive or negative
    // If days > 0, the date is incremented by that many days
    // If days < 0, the date is decremented by the absolute value of days
    // The resulting date is adjusted based on the number of days in each month and leap years
    int current_day = day;
    int current_month = month;
    int current_year = year;
    int daysInMonth;

    if (days > 0)
    {
        // Increment the date by the specified number of days
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
        // Decrement the date by the absolute value of the specified number of days
        while (days < 0)
        {
            while (current_month >= 1)
            {
                while (current_day >= 1)
                {
                    ++days;
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

bool Date::isLeap(unsigned y) const
{
    // Checks if the given year is a leap year
    if (y % 4 == 0) {
        if (y % 100 == 0)
            if (y % 400 == 0)
                return true;
        return false;
        return true;
    }
    return false;
}

unsigned Date::daysPerMonth(unsigned m, unsigned y) const
{
    // Returns the number of days in the specified month of the given year
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

string Date::name(unsigned m) const
{
    // Returns the name of the month based on the month number
    const string MONTHS[12] = {"January", "February", "March", "April",
                               "May", "June", "July", "August",
                               "September", "October", "November",
                               "December"};
    return MONTHS[m - 1];
}

unsigned Date::number(const string &mn) const
{
    // Returns the month number based on the month name
    const string MONTHS[12] = {"January", "February", "March", "April",
                               "May", "June", "July", "August",
                               "September", "October", "November",
                               "December"};

    for (int i = 0; i < 12; ++i) {
        if (mn == MONTHS[i])
            return i + 1;
    }
    return 0; // Return 0 if the month doesn't exist
}

bool Date::operator==(const Date& other)
{
    // Equality operator: Checks if two Date objects have the same month, day, and year
    return this->month == other.month &&
           this->day == other.day &&
           this->year == other.year;
}

string Date::returnAlpha() const
{
    // Returns the date in alpha format as a string
    stringstream ss;
    ss << this->monthName << ' ' << this->day << ", " << this->year;
    return ss.str();
}

string Date::returnNumeric() const
{
    // Returns the date in numeric format as a string
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
