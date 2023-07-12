#include "member.h"

Member::Member() : name("")
{
    // Default constructor: Initializes the member object with default values
}

Member::Member(string n, int id, bool member_type, Date d)
{
    // Parameterized constructor: Initializes the member object with provided values
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
    // Adds a purchase (sale) to the member's purchase history
    this->purchases.add_sale(s);
}

void Member::update_expiration_date(Date d)
{
    // Updates the member's expiration date
    this->expiration_date = d;
}

void Member::calculate_rebate()
{
    // Calculates the rebate amount for the member based on their purchases
    double total = 0;
    for (int i = 0; i < this->purchases.size(); ++i)
        total += this->purchases[i].item.price * this->purchases[i].quantity;

    total -= total * 0.0875;
    rebate_amount = total * 0.05;
    rebate_amount = std::ceil(rebate_amount * 100.0) / 100.0;
}

void Member::calc_total_amount_spent()
{
    // Calculates the total amount spent by the member on purchases
    double total = 0;
    for (int i = 0; i < this->purchases.size(); ++i)
        total += this->purchases[i].item.price;

    total_amount_spent = total;
    total_amount_spent = std::ceil(total_amount_spent * 100.0) / 100.0;
}

void Member::markForBasic()
{
    // Marks the member's name to indicate Basic membership
    if (this->name[name.length() - 1] != '*')
        this->name += "*";
}

void Member::markForPreferred()
{
    // Marks the member's name to indicate Preferred membership
    if (this->name[name.length() - 2] != '*')
        this->name += "**";
}
