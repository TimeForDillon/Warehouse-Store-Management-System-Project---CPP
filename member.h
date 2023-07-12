#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include "date.h"
#include "salecontainer.h"
#include <cmath>

using namespace std;

class Member
{
public:
    // Constructors
    Member();
    Member(string n, int id, bool member_type, Date d);

    // Member functions
    void add_purchase(Sale s);
    void update_expiration_date(Date d);
    void calc_total_amount_spent();
    void calculate_rebate();
    void markForBasic();
    void markForPreferred();

    // Accessors
    string get_name() const { return this->name; }
    int get_member_id() const { return this->member_id; }
    bool get_type() const { return this->type; }
    Date get_expiration_date() const { return this->expiration_date; }
    double get_rebate() const { return this->rebate_amount; }
    double get_total_amount_spent() const { return this->total_amount_spent; }
    double get_annual_dues() const { return this->annual_dues; }
    SaleContainer get_purchases() const { return this->purchases; }

private:
    string name;                    // Name of the member
    int member_id;                  // Member ID (random 5-digit number)
    bool type;                      // Member type: true == preferred, false == basic
    Date expiration_date;           // Membership expiration date (four years after joining)
    SaleContainer purchases;        // Container for member purchases
    double total_amount_spent;      // Total amount spent by the member
    double rebate_amount;           // Rebate amount for the member
    double annual_dues;             // Annual membership dues
};

#endif // MEMBER_H
