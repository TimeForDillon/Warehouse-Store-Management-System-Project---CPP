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
        vector<Item> items;
        Date current_date;

    public:
        ItemContainer();
        ItemContainer(string file);

        Item operator[](int index) const { return this->items[index]; }
        int size() const { return this->items.size(); }
        Date get_date() const { return this->current_date; }

        void clear() { this->items.clear(); }
        void add_item(Item i);

        void load(string file);
};

#endif // ITEMCONTAINER_H
