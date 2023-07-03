#include "itemcontainer.h"

ItemContainer::ItemContainer()
{
    current_date = Date(1,1,2013);
}

ItemContainer::ItemContainer(string file)
{
    load(file);
}

void ItemContainer::add_item(Item i)
{
    this->items.push_back(i);
}

void ItemContainer::load(string file)
{
    ifstream in_file;

    string item_name;
    string item_price;
    string dateHolder;

    in_file.open(file);
    if (!in_file)
    {
        cout << "ERROR: file could not open" << endl;
        exit(1);
    }

    getline(in_file, dateHolder);
    current_date = Date(stoi(dateHolder.substr(0, 2)),
                        stoi(dateHolder.substr(3, 2)),
                        stoi(dateHolder.substr(6, 4)));

    while (getline(in_file, item_name))
    {
        if(item_name != "")
        {
            getline(in_file, item_price);
            this->add_item(Item(item_name, stod(item_price)));
        }
    }
}
