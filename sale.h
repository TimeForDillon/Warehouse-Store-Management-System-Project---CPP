#ifndef SALE_H
#define SALE_H

#include "item.h"
#include "date.h"

struct Sale
{
    Item item;
    Date date_of_purchase;
    int id;
    double price;
    int quantity = 0;

    Sale() {}
    Sale(Item i, Date d, int id, int q): item(i), date_of_purchase(d), id(id), quantity(q) { }

    //sales.push_back(Sale(Item(itemName, priceHolder.toDouble()), date, id, quantityHolder.toInt()));

    //Dillon
    string getItemName() const { return this->item.name; }
    double getItemPrice() const { return this->item.price; }
    string getDate() const { return this->date_of_purchase.returnNumeric(); }
    int getID() const { return this->id; }
    int getQuantity() const { return this->quantity; }
    //Dillon
};
#endif // SALE_H
