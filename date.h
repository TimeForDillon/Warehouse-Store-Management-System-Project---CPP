#ifndef DATE_H
#define DATE_H

#include <string>
#include <sstream>
using namespace std;

class Date
{
private:
    unsigned day;       // IN/OUT: day of the month
    unsigned month;     // IN/OUT: month of the year
    string monthName;   // IN/OUT: month as a string
    unsigned year;      // IN/OUT: year

public:
    // Default constructor
    Date();

    // Constructor with numeric values for month, day, and year
    Date(unsigned m, unsigned d, unsigned y);

    // Constructor with month name, day, and year
    Date(const string &mn, unsigned d, unsigned y);

    // Print the date in numeric format (mm/dd/yyyy)
    void printNumeric() const;

    // Print the date in alphanumeric format (month day, year)
    void printAlpha() const;

    // Add a specified number of days to the date and return a new date object
    Date addDays(int days) const;

    // Getters for individual date components
    unsigned get_day() { return this->day; }
    unsigned get_month() { return this->month; }
    string get_month_name() { return this->monthName; }
    unsigned get_year() { return this->year; }

    // Overloaded equality operator to compare two Date objects
    bool operator==(const Date& other);

    // Return the date in numeric format as a string
    string returnNumeric() const;

    // Return the date in alphanumeric format as a string
    string returnAlpha() const;

private:

    // Check if a given year is a leap year
    bool isLeap(unsigned) const;

    // Get the number of days in a month for a given year
    unsigned daysPerMonth(unsigned m, unsigned y) const;

    // Get the name of a month based on its number
    string name(unsigned m) const;

    // Get the number corresponding to a month name
    unsigned number(const string &mn) const;
};

#endif // DATE_H
