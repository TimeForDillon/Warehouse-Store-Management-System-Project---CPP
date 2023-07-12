#ifndef MEMBERCONTAINER_H
#define MEMBERCONTAINER_H

#include "member.h"
#include "itemcontainer.h"
#include <vector>
#include <QFile>
#include <QTextStream>
#include <sstream>
#include <iomanip>
#include <tuple>
#include <algorithm>
#include <time.h>
#include <stdlib.h>

class MemberContainer
{
private:
    vector<Member> members; // Vector to store member objects

public:
    // Constructors
    MemberContainer();
    MemberContainer(QString file);

    // Operator overloading
    Member& operator[](int index) { return this->members[index]; }

    // Member functions
    int size() { return this->members.size(); }             // Returns the number of members
    bool empty() { return this->members.empty(); }          // Checks if the member container is empty
    int basic_size();                                       // Returns the number of basic members
    int preferred_size();                                   // Returns the number of preferred members
    int find(int the_id, int pos);                          // Finds a member by ID starting from the specified position
    int find(string the_name, int pos);                     // Finds a member by name starting from the specified position
    int find(int the_day, int the_month, int the_year, int pos); // Finds a member by expiration date starting from the specified position

    // View functions
    void view_single_member_purchases(string name);          // Views the purchases of a single member
    void view_grand_total_purchases();                       // Views the grand total of purchases for all members
    void view_expiration_dates(int month);                   // Views the expiration dates of members in the specified month
    void view_membership_dues(string type = "All");          // Views the membership dues for all members or a specific type
    void view_preferred_members_rebate();                    // Views the rebate for preferred members

    // Report functions
    string sales_report(Date date);                          // Generates a sales report for a specific date
    string member_information(int index);                    // Retrieves information about a member at the specified index

    // Getters
    string getMemberName(int id);                            // Retrieves the name of a member with the given ID
    string getMemberType(int id);                            // Retrieves the type of a member with the given ID

    // Member manipulation functions
    void typeChange();                                      // Changes the type of a member

    // Member modification functions
    void add_member(string the_name, int the_id, bool the_type, Date the_date);   // Adds a member with the given details
    void add_member(Member m);                              // Adds a member object
    void remove_member(int id);                              // Removes a member with the given ID
    void remove_member_by_index(int index);                  // Removes a member at the specified index
    void clear();                                           // Clears the member container

    // Sorting functions
    void sort_by_member_id();                               // Sorts members by member ID
    void sort_by_name();                                    // Sorts members by name
    void sort_by_date();                                    // Sorts members by expiration date

    // Input functions
    void inputSales(const char* file_name);                  // Inputs sales from a file

    // Loading function
    int load(QString file);                                 // Loads member data from a file
};

#endif // MEMBERCONTAINER_H
