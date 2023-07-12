#ifndef SALE_H
#define SALE_H

#include "item.h"
#include "date.h"

struct Sale
{
    Item item;                  // Item purchased
    Date date_of_purchase;      // Date of purchase
    int id;                     // Sale ID
    double price;               // Price of the item
    int quantity = 0;           // Quantity of items purchased

    // Default constructor
    Sale() {}

    // Constructor with parameters
    Sale(Item i, Date d, int id, int q): item(i), date_of_purchase(d), id(id), quantity(q) { }

    // Getters for member variables
    string getItemName() const { return this->item.name; }               // Returns the name of the item
    double getItemPrice() const { return this->item.price; }             // Returns the price of the item
    string getDate() const { return this->date_of_purchase.returnNumeric(); }   // Returns the date of purchase as a string
    int getID() const { return this->id; }                               // Returns the sale ID
    int getQuantity() const { return this->quantity; }                   // Returns the quantity of items purchased
};

#endif // SALE_H
