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
       Member();
       Member(string n, int id, bool member_type, Date d);
       void add_purchase(Sale s);
       void update_expiration_date(Date d);

       // getters
       string get_name() const { return this->name; }
       int get_member_id() const { return this->member_id; }
       bool get_type() const { return this->type; }
       Date get_expiration_date() const { return this->expiration_date; }
       double get_rebate() const { return this->rebate_amount; }
       double get_total_amount_spent() const { return this->total_amount_spent; }
       double get_annual_dues() const { return this->annual_dues; }
       SaleContainer get_purchases() const { return this->purchases; }

       void calc_total_amount_spent();
       void calculate_rebate();

       void markForBasic();
       void markForPreferred();

   private:

       string name;
       int member_id;     // random 5-digit
       bool type;   // true == preferred, false == basic
       Date expiration_date;    // four years after joining

       SaleContainer purchases;
       double total_amount_spent;
       double rebate_amount;
       double annual_dues;

};

#endif // MEMBER_H
