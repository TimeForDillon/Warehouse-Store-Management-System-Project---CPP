#include "member.h"

Member::Member() : name("")
{

}

Member::Member(string n,int id, bool member_type, Date d)
{
    this->name = n;
    this->member_id = id;
    this->type = member_type;
    this->expiration_date = d;

    this->total_amount_spent = 0;
    this->rebate_amount = 0;

    if (this->type == false)
        this->annual_dues = 60;
    else if (this->type == true)
        this->annual_dues = 75;
}

void Member::add_purchase(Sale s)
{
    this->purchases.add_sale(s);
}

void Member::update_expiration_date(Date d)
{
    this->expiration_date = d;
}

void Member::calculate_rebate()
{
    double total = 0;
    for (int i = 0; i < this->purchases.size(); ++i)
        total += this->purchases[i].item.price * this->purchases[i].quantity;

    total -= total * 0.0875;
    rebate_amount = total * 0.05;
    rebate_amount = std::ceil(rebate_amount * 100.0) / 100.0;
}

void Member::calc_total_amount_spent()
{
    double total = 0;
    for ( int i = 0; i < this->purchases.size(); ++i)
        total += this->purchases[i].item.price;

    total_amount_spent = total;
    total_amount_spent = std::ceil(total_amount_spent * 100.0) / 100.0;
}

void Member::markForBasic()
{
    if (this->name[name.length() - 1] != '*')
        this->name += "*";
}

void Member::markForPreferred()
{
    if (this->name[name.length() - 2] != '*')
        this->name += "**";
}
