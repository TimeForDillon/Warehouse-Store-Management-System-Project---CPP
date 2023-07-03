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
    /********************************
    ********* CONSTRUCTORS *********
    ********************************/

        Date();
        Date(unsigned m, unsigned d, unsigned y);
        Date(const string &mn, unsigned d, unsigned y);

    /***************
     ** ACCESSORS **
     ***************/
        void printNumeric() const;
        void printAlpha() const;
        Date addDays(int days) const;
        unsigned get_day() { return this->day; }
        unsigned get_month() { return this->month; }
        string   get_month_name() { return this->monthName; }
        unsigned get_year() { return this->year; }
        bool operator==(const Date& other);
        string returnNumeric() const;
        string returnAlpha() const;

    private:
    /***************
     ** ACCESSORS **
     ***************/
        bool isLeap(unsigned) const;
        unsigned daysPerMonth(unsigned m, unsigned y) const;
        string name(unsigned m) const;
        unsigned number(const string &mn) const;
};

#endif // DATE_H
