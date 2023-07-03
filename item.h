#ifndef ITEM_H
#define ITEM_H
#include <string>

using namespace std;
struct Item
{
    string name;
    double price;
    Item(string n = "", double p = 0) {name = n; price = p;}
};

#endif // ITEM_H
