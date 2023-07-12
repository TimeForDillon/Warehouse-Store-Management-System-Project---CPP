#include "membercontainer.h"

MemberContainer::MemberContainer()
{
    ;
}

MemberContainer::MemberContainer(QString file)
{
    load(file);
}

int MemberContainer::basic_size()
{
    // Calculate the total number of basic members
    // Iterate through members and count the ones with type = false
    int total_basics = 0;

    for (int i = 0; i < size(); i++)
    {
        if (members[i].get_type() == false)
            total_basics++;
    }

    return total_basics;
}

int MemberContainer::preferred_size()
{
    // Calculate the total number of preferred members
    // Iterate through members and count the ones with type = true
    int total_preferred = 0;

    for (int i = 0; i < size(); i++)
    {
        if (members[i].get_type() == true)
            total_preferred++;
    }

    return total_preferred;
}

int MemberContainer::find(int the_id, int pos)
{
    // Find a member with the given ID starting from the specified position
    // Iterate through members from pos to size() and compare member_id
    // Return the index of the found member or -1 if not found
    for (int i = pos; i < size(); i++)
    {
        if (members[i].get_member_id() == the_id)
            return i;
    }

    return -1;
}

int MemberContainer::find(string the_name, int pos)
{
    // Find a member with the given name starting from the specified position
    // Iterate through members from pos to size() and compare names
    // Return the index of the found member or -1 if not found
    for (int i = pos; i < size(); i++)
    {
        if (strstr(members[i].get_name().c_str(), the_name.c_str()) != nullptr)
            return i;
    }

    return -1;
}

int MemberContainer::find(int the_day, int the_month, int the_year, int pos)
{
    // Find a member with the given expiration date starting from the specified position
    // If the_day or the_month is 0, only check the year
    // Iterate through members from pos to size() and compare expiration dates
    // Return the index of the found member or -1 if not found
    if (the_month == 0)
    {
        for (int i = pos; i < size(); i++)
        {
            if (int(members[i].get_expiration_date().get_year()) == the_year)
                return i;
        }
    }
    else if (the_day == 0)
    {
        for (int i = pos; i < size(); i++)
        {
            if (int(members[i].get_expiration_date().get_month()) == the_month && int(members[i].get_expiration_date().get_year()) == the_year)
                return i;
        }
    }
    else
    {
        for (int i = pos; i < size(); i++)
        {
            if (int(members[i].get_expiration_date().get_day()) == the_day && int(members[i].get_expiration_date().get_month()) == the_month && int(members[i].get_expiration_date().get_year()) == the_year)
                return i;
        }
    }

    return -1;
}

//Dillon - this returns the members name for the given id
string MemberContainer::getMemberName(int id)
{
    // Get the name of a member with the given ID
    // Iterate through members and compare member_id
    // Return the name of the member or "Invalid ID" if not found
    for(int i = 0; i < int(this->members.size()); i++)
    {
        if(this->members[i].get_member_id() == id) return this->members[i].get_name();
    }
    return "Invalid ID";
}

//Dillon - this returns the members type for the given id
string MemberContainer::getMemberType(int id)
{
    // Get the type (basic or preferred) of a member with the given ID
    // Iterate through members and compare member_id
    // Return the type of the member or "Invalid ID" if not found
    for(int i = 0; i < int(this->members.size()); i++)
    {
        if(this->members[i].get_member_id() == id)
        {
            if(this->members[i].get_type()) return "Preferred";
            else return "Basic";
        }
    }
    return "Invalid ID";
}

void MemberContainer::view_single_member_purchases(string name)
{
    // Find a member with the given name and display their ID and total amount spent
    unsigned int index = 0;
    while (index < this->members.size() && this->members[index].get_name() != name)
        ++index;
    if (index == this->members.size())
    {
        cout << "ERROR: member not found" << endl;
        exit(0);
    }

    cout << "ID: " << this->members[index].get_member_id() << endl;
    cout << "Total Amount Spent: " << this->members[index].get_total_amount_spent() << endl;
}

void MemberContainer::view_grand_total_purchases()
{
    // Display the total purchase amount for each member and calculate the grand total
    double total = 0;
    cout << "ID\tTotal Purchase Amount" << endl;
    for (unsigned int i = 0; i < this->members.size(); ++i)
    {
        cout << this->members[i].get_member_id() << "\t$" << this->members[i].get_total_amount_spent() << endl;
        total += this->members[i].get_total_amount_spent();
    }
    cout << "------------------------------------------" << endl;
    cout << "Total: $" << total << endl;
}

void MemberContainer::view_expiration_dates(int month)
{
    // Create a temporary container to store members with the specified expiration month
    // Iterate through members and add the ones with the matching month to the temporary container
    // Display the ID and expiration date for each member in the temporary container
   MemberContainer temp;
    for (unsigned int i = 0; i < this->members.size(); ++i)
        if (int(this->members[i].get_expiration_date().get_month()) == month)
            temp.add_member(this->members[i].get_name(), this->members[i].get_member_id(), this->members[i].get_type(), this->members[i].get_expiration_date());

    for (unsigned int i = 0; i < temp.members.size(); ++i)
    {
        cout << "ID: " << temp.members[i].get_member_id() << "\tExpiration Date: ";
        temp.members[i].get_expiration_date().printNumeric();
    }
}

void MemberContainer::view_membership_dues(string type)
{
    // Create two temporary containers to store basic and preferred members separately
    // Iterate through members and add them to the appropriate temporary container based on their type
    // If type is "Basic" or "All", display the name and dues for each member in the basic container
    // If type is "Preferred" or "All", display the name and dues for each member in the preferred container
    MemberContainer basic;
    MemberContainer preferred;

    for (unsigned int i = 0; i < this->members.size(); ++i)
    {
        if (this->members[i].get_type() == false)
            basic.add_member(this->members[i].get_name(), this->members[i].get_member_id(), this->members[i].get_type(), this->members[i].get_expiration_date());
        else
            preferred.add_member(this->members[i].get_name(), this->members[i].get_member_id(), this->members[i].get_type(), this->members[i].get_expiration_date());
    }


    if (type == "Basic" || type == "All")
        for (unsigned int i = 0; i < basic.members.size(); ++i)
            cout << "Name: " << basic.members[i].get_name() << "\tDues: " << basic.members[i].get_annual_dues() << endl;
    if (type == "Preferred" || type == "All")
        for (unsigned int i = 0; i < preferred.members.size(); ++i)
            cout << "Name: " << preferred.members[i].get_name() << "\tDues: " << preferred.members[i].get_annual_dues() << endl;

}

void MemberContainer::view_preferred_members_rebate()
{
    // Calculate and display the rebate amount for each preferred member
}

string MemberContainer::sales_report(Date date)
{
    // Generate a sales report for the specified date
    // Iterate through members and their purchases to calculate the total amount spent on each item
    // Store the results in a vector and calculate the final total
    // Display the item names, amounts, and totals
    // Display the final total and separate the basic and preferred members
    // Return the sales report as a string
    stringstream stream;    // Convert output to a string
    string answer;          // Return string
    vector<string> basic;
    vector<string> preferred;
    string dashes(90, '-');

    // This vector stored the item name, amount, and its price on a day, but seperated by members
    vector<tuple<string, int, double>> list;
    stream << left << setw(30) << "Items" << setw(30) << "Amount" << setw(30) << "Total" << endl;
    stream << dashes << endl;
    // Processing
    for (size_t i = 0; i < members.size(); i++)
    {
        SaleContainer sales = members[i].get_purchases();
        int amount = 0;
        string itemName;
        vector<string> itemCounted;
        for (size_t j = 0; j < size_t(sales.size()); j++)
        {
            itemName = sales[j].item.name;
            // To avoid from repeating counting, if the item name has been counted, then
            // we do nothing, else we count the amount of it, and store name to another vector
            // that store counted name
            if (std::find(itemCounted.begin(), itemCounted.end(), itemName) == itemCounted.end())  //If not found, that means a item has not been counted yet.
            {
                // This loop check the date and item name and count the amount
                // And the reason is that one member may buy a same thing twice on the different day of
                amount = 0;
                for (size_t k = 0; k < size_t(sales.size()); k++)
                {

                    if (sales[k].date_of_purchase == date && sales[k].item.name == itemName)
                    {
                        amount += sales[k].quantity;
                    }
                }
                tuple<string, int, double> temp(itemName, amount, sales[j].item.price);
                list.push_back(temp);
                itemCounted.push_back(itemName);
            }
        }

        if (amount > 0 && members[i].get_type() == false)
            basic.push_back(members[i].get_name());
        else if (amount > 0 && members[i].get_type() == true)
            preferred.push_back(members[i].get_name());
    }
    vector<tuple<string, int, double>> list2;   // This vector is a general vector, item name, amount and total
    vector<string> itemCounted;
    // Push back a general list vector
    for (size_t i = 0; i < list.size(); i++)
    {
        string itemName = get<0>(list[i]);
        int amount = 0;
        if (std::find(itemCounted.begin(), itemCounted.end(), itemName) == itemCounted.end())
        {
            for (size_t j = 0; j < list.size(); j++)
            {
                if(itemName == get<0>(list[j]))
                {
                    amount+= get<1>(list[j]);
                }
            }
            tuple<string, int, double> temp(itemName, amount, get<2>(list[i]) * amount);
            list2.push_back(temp);
            itemCounted.push_back(itemName);
        }
    }
    double final_total = 0;
    for (size_t i = 0; i < list2.size(); i++)
    {
        stream << left << setw(30) << get<0>(list2[i]) << left << setw(30) << get<1>(list2[i]) << left << setw(30) << get<2>(list2[i]) << endl;
        final_total += get<2>(list2[i]);
    }
    stream << dashes << endl;
    stream << left << setw(60) << "Final Total: " << final_total << endl << endl;
    stream << "Basic: " << endl;
    for (unsigned int i = 0; i < basic.size(); ++i)
        stream << left << setw(60) << basic[i] << endl;
    stream << endl;
    stream << "Preferred: " << endl;
    for (unsigned int i = 0; i < preferred.size(); ++i)
        stream << left << setw(60) << preferred[i] << endl;
    stream << endl;
    answer += stream.str();
    cout << answer << endl;
    return stream.str();
}

string MemberContainer::member_information(int index)
{
    // Generate information about a member at the specified index
    // Get the member object at the specified index
    // Retrieve the member's name, ID, type, and purchases
    // Display the member information and the items purchased
    // Calculate and display the total amount spent by the member
    // Return the member information as a string
    stringstream ss;
    string dashes(30, '-');
    Member* m = &this->members[index];
    SaleContainer s = m->get_purchases();

    ss << left << setw(60) << "Name:" << m->get_name() << endl;
    ss << left << setw(60) << "ID:" << m->get_member_id() << endl;
    ss << left << setw(60) << "Type:" << m->get_type() << endl;
    ss << endl;
    ss << left << setw(30) << "Item" << right << setw(30) << "Price" << endl;
    ss << dashes << endl;
    for (int i = 0; i < m->get_purchases().size(); ++i)
        ss << left << setw(30) << s[i].item.name << right << setw(30) << s[i].item.price << endl;
    ss << dashes << endl;
    ss << left << setw(30) << "Total:" << right << setw(30) << m->get_total_amount_spent() << endl;

    return ss.str();
}
void MemberContainer::add_member(string the_name, int the_id, bool the_type, Date the_date)
{
    // Add a new member to the container with the specified name, ID, type, and expiration date
    int rand_digit = 0;
    int rand_id = 0;
    int multiplier;
    bool exists = false;

    srand((unsigned)time(0));

    if (the_id == 0)
    {
        while (true)
        {
            multiplier = 10000;

            for (int i = 0; i < 5; i++)
            {
                rand_digit = (rand() % 9) + 1;
                rand_digit *= multiplier;
                rand_id += rand_digit;
                multiplier /= 10;
            }

            for (int i = 0; i < int(members.size()); i++)
            {
                if (rand_id == members[i].get_member_id())
                    exists = true;
            }

            if (!exists)
                break;
        }

        Member m(the_name, rand_id, the_type, the_date);
        this->members.push_back(m);
    }
    else
    {
        Member m(the_name, the_id, the_type, the_date);
        this->members.push_back(m);
    }
}

void MemberContainer::add_member(Member m)
{
    // Add an existing member object to the container
    this->members.push_back(m);
}

void MemberContainer::remove_member(int id)
{
    // Remove a member with the specified ID from the container
    for (int i = 0; i < size(); i++)
    {
        if (id == members[i].get_member_id())
            members.erase(this->members.begin() + i);
    }
}

void MemberContainer::remove_member_by_index(int index)
{
    // Remove a member at the specified index from the container
    members.erase(members.begin() + index);
}

void MemberContainer::clear()
{
    // Clear all members from the container
    this->members.clear();
}

void MemberContainer::inputSales(const char* file_name)
{
    // Read sales data from a file and update member purchase information accordingly
    ifstream inFile;
    string line;
    inFile.open(file_name);
    int id;
    string item_name;
    string price;
    string quantity;
    string month, date, year;
    while (getline(inFile, line))
    {
        month += line[0];
        month += line[1];
        date += line[3];
        date += line[4];
        year += line.substr(6);

        getline(inFile, line);
        id = atoi(line.c_str());

        getline(inFile, line);
        item_name = line;

        getline(inFile, line);
        int i = 0;
        for (; line[i] != ' '; i++)
        {
            price += line[i];
        }
        quantity = line.substr(i);

        Date today(atoi(month.c_str()),
                    atoi(date.c_str()),
                    atoi(year.c_str()));
        Item addendItem(item_name, atof(price.c_str()));
        for (int k = 0; k < int(members.size()); k++)
        {
            if (members[k].get_member_id() == id)
            {
                members[k].add_purchase(Sale(addendItem, today, id,
                                        atoi(quantity.c_str())));
            }
        }
        month = "";
        date = "";
        year = "";
        price = "";
        quantity = "";
    }
    inFile.close();
}

int MemberContainer::load(QString file)
{
    // Load member data from a file and populate the container
    // Open the file for reading
    // Read member information line by line
    // Create a new member object with the read information and add it to the container
    // Close the file
    // Return 0 for success or 1 for failure
    QFile inFile;
    Date date;
    string nameHolder;
    string idHolder;
    string member_typeHolder;
    string dateHolder;

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
        nameHolder = in.readLine().toStdString();
        idHolder = in.readLine().toStdString();
        member_typeHolder = in.readLine().toStdString();
        dateHolder = in.readLine().toStdString();

        date = Date(stoi(dateHolder.substr(0, 2)),
                    stoi(dateHolder.substr(3, 2)),
                    stoi(dateHolder.substr(6, 4)));

        if (member_typeHolder == "Basic")
            members.push_back(Member(nameHolder, stoi(idHolder), false, date));
        else if (member_typeHolder == "Preferred")
            members.push_back(Member(nameHolder, stoi(idHolder), true, date));
    }

    inFile.close();
    return 0;
}

void MemberContainer::sort_by_member_id()
{
    // Sort members based on their member ID in ascending order
    stable_sort( members.begin( ), members.end( ), [ ]( const Member& lhs, const Member& rhs )
    {
       return lhs.get_member_id() < rhs.get_member_id();
    });
}

void MemberContainer::sort_by_name()
{
    // Sort members based on their names in ascending order
    stable_sort( members.begin( ), members.end( ), [ ]( const Member& lhs, const Member& rhs )
    {
       return lhs.get_name() < rhs.get_name();
    });
}

void MemberContainer::sort_by_date()
{
    // Sort members based on their expiration dates in ascending order
    stable_sort( members.begin( ), members.end( ), [ ]( const Member& lhs, const Member& rhs )
    {
         return lhs.get_expiration_date().get_day() < rhs.get_expiration_date().get_day();
    });

    stable_sort( members.begin( ), members.end( ), [ ]( const Member& lhs, const Member& rhs )
    {
         return lhs.get_expiration_date().get_month() < rhs.get_expiration_date().get_month();
    });

    stable_sort( members.begin( ), members.end( ), [ ]( const Member& lhs, const Member& rhs )
    {
         return lhs.get_expiration_date().get_year() < rhs.get_expiration_date().get_year();
    });
}

void MemberContainer::typeChange()
{
    // Change the type (basic or preferred) of members based on their total amount spent
    for(int i = 0; i < int(this->members.size()); i++)
    {
        if(this->members[i].get_total_amount_spent() < 300.00 && this->members[i].get_type() == true) //true = preferred
        {
            if(this->members[i].get_rebate() < 15.00)
            {
                //cout << "should be basic: " << this->members[i].get_name() << endl;
                this->members[i].markForBasic();
            }
        }
        else //false = basic
        {
            if(this->members[i].get_total_amount_spent() >= 300.00 && this->members[i].get_type() == false)
            {
                //cout << "should be preferred: " << this->members[i].get_name() << endl;
                this->members[i].markForPreferred();
            }
        }
    }
}
