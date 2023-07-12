#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

// Structure representing an item
struct Item
{
    string name;    // Name of the item
    double price;   // Price of the item

    // Constructor with default values for name and price
    Item(string n = "", double p = 0)
    {
        name = n;
        price = p;
    }
};

#endif // ITEM_H
