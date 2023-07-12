#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include <vector>
#include <fstream>
#include <iostream>
#include "item.h"
#include "date.h"
using namespace std;

class ItemContainer
{
private:
    vector<Item> items;         // Vector to store items
    Date current_date;          // Current date

public:

    // Default constructor
    ItemContainer();

    // Constructor that takes a file name to load items from
    ItemContainer(string file);

    // Overloaded subscript operator to access items by index
    Item operator[](int index) const { return this->items[index]; }

    // Get the number of items in the container
    int size() const { return this->items.size(); }

    // Get the current date
    Date get_date() const { return this->current_date; }

    // Clear the container by removing all items
    void clear() { this->items.clear(); }

    // Add an item to the container
    void add_item(Item i);

    // Load items from a file
    void load(string file);
};

#endif // ITEMCONTAINER_H
