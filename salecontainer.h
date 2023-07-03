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
        vector<Sale> sales;

    public:
        SaleContainer();
        SaleContainer(QString file);

        Sale operator[](int index) { return this->sales[index]; }
        SaleContainer& operator=(const SaleContainer& other);
        int size() { return this->sales.size(); }
        void add_sale(Sale s);
        int find(string the_name, int pos);
        void sort_by_name();
        void sort_by_price(bool high_to_low);
        void sort_by_quantity(bool high_to_low);
        void erase_sale(int index);
        void clear();

        int load(QString file);
};

#endif // SALECONTAINER_H
