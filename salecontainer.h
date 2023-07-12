#ifndef SALECONTAINER_H
#define SALECONTAINER_H

#include "sale.h"
#include <vector>
#include <QFile>
#include <QTextStream>
#include <mytextstream.h>
#include <cstring>
#include <algorithm>

class SaleContainer
{
private:
    vector<Sale> sales; // Vector to store sale objects

public:
    // Constructors
    SaleContainer();
    SaleContainer(QString file);

    // Operator overloading
    Sale operator[](int index) { return this->sales[index]; }
    SaleContainer& operator=(const SaleContainer& other);

    // Member functions
    int size() { return this->sales.size(); }     // Returns the number of sales
    void add_sale(Sale s);                        // Adds a sale to the container
    int find(string the_name, int pos);           // Finds a sale by item name starting from the specified position
    void sort_by_name();                          // Sorts sales by item name
    void sort_by_price(bool high_to_low);         // Sorts sales by price in ascending or descending order
    void sort_by_quantity(bool high_to_low);      // Sorts sales by quantity in ascending or descending order
    void erase_sale(int index);                   // Removes a sale at the specified index
    void clear();                                 // Clears the sale container

    // Loading function
    int load(QString file);                       // Loads sale data from a file
};

#endif // SALECONTAINER_H
