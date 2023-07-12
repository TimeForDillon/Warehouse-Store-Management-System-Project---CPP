#include "salecontainer.h"
#include <iostream>

SaleContainer::SaleContainer()
{

}

SaleContainer::SaleContainer(QString file)
{
    load(file);
}

SaleContainer& SaleContainer::operator=(const SaleContainer& other)
{
    // Assignment operator to copy the contents of another SaleContainer
    // Copy the sales vector from the other SaleContainer to this SaleContainer
    // Return a reference to this SaleContainer
    this->sales = other.sales;

    return *this;
}

void SaleContainer::add_sale(Sale s)
{
    // Add a sale to the container
    // Add the given sale object to the sales vector
    this->sales.push_back(s);
}

int SaleContainer::find(string the_name, int pos)
{
    // Find a sale with the given item name starting from the specified position
    // Iterate through sales from pos to size() and compare item names
    // Return the index of the found sale or -1 if not found
    for (int i = pos; i < size(); i++)
    {
        if (strstr(sales[i].getItemName().c_str(), the_name.c_str()) != nullptr)
            return i;
    }

    return -1;
}

void SaleContainer::sort_by_name()
{
    // Sort sales based on the item name in ascending order
    stable_sort( sales.begin( ), sales.end( ), [ ]( const Sale& lhs, const Sale& rhs )
    {
       return lhs.getItemName() < rhs.getItemName();
    });
}

void SaleContainer::sort_by_price(bool high_to_low)
{
    // Sort sales based on the item price in either ascending or descending order
    if (high_to_low)
    {
        stable_sort( sales.begin( ), sales.end( ), [ ]( const Sale& lhs, const Sale& rhs )
        {
           return lhs.getItemPrice() > rhs.getItemPrice();
        });
    }
    else
    {
        stable_sort( sales.begin( ), sales.end( ), [ ]( const Sale& lhs, const Sale& rhs )
        {
           return lhs.getItemPrice() < rhs.getItemPrice();
        });
    }
}

void SaleContainer::sort_by_quantity(bool high_to_low)
{
    // Sort sales based on the quantity in either ascending or descending order
    if (high_to_low)
    {
        stable_sort( sales.begin( ), sales.end( ), [ ]( const Sale& lhs, const Sale& rhs )
        {
           return lhs.getQuantity() > rhs.getQuantity();
        });
    }
    else
    {
        stable_sort( sales.begin( ), sales.end( ), [ ]( const Sale& lhs, const Sale& rhs )
        {
           return lhs.getQuantity() < rhs.getQuantity();
        });
    }
}

void SaleContainer::erase_sale(int index)
{
    // Erase a sale at the specified index from the container
    sales.erase(sales.begin() + index);
}

void SaleContainer::clear()
{
    // Clear all sales from the container
    this->sales.clear();
}

int SaleContainer::load(QString file)
{
    // Load sale data from a file and populate the container
    // Open the file for reading
    // Read sale information line by line
    // Parse the line to extract the date, ID, item name, price, and quantity
    // Create a new Sale object with the parsed information and add it to the sales vector
    // Close the file
    // Return 0 for success or 1 for failure
    QFile inFile;
    Date date;
    int id;
    string dateHolder;
    string itemName;
    QString itemLine;
    QString priceHolder;
    QString quantityHolder;

    inFile.setFileName(file);

    if (!inFile.exists())
    {
        cout << "File doesn't exist" << endl;
        return 1;
    }

    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Error: Can't Open File.\n";
        return 1;
    }

    QTextStream in(&inFile);
    while (!in.atEnd())
    {
        dateHolder = in.readLine().toStdString();
        id = in.readLine().toInt();
        itemName = in.readLine().toStdString();
        itemLine = in.readLine();

        priceHolder = "";
        quantityHolder = "";

        MyTextStream st(&itemLine);
        st >> priceHolder >> quantityHolder;

        date = Date(stoi(dateHolder.substr(0, 2)),
                    stoi(dateHolder.substr(3, 2)),
                    stoi(dateHolder.substr(6, 4)));

        sales.push_back(Sale(Item(itemName, priceHolder.toDouble()), date, id, quantityHolder.toInt()));
    }

    inFile.close();
    return 0;
}
