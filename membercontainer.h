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
        vector<Member> members;

    public:

        MemberContainer();
        MemberContainer(QString file);


        Member& operator[](int index) { return this->members[index]; }
        int size() { return this->members.size(); }
        bool empty() { return this->members.empty(); }
        int basic_size();
        int preferred_size();
        int find(int the_id, int pos);  // find functions return the index of the member object found in the member container
        int find(string the_name, int pos);   // returns -1 if nothing is found
        int find(int the_day, int the_month, int the_year, int pos);

        void view_single_member_purchases(string name);
        void view_grand_total_purchases();
        void view_expiration_dates(int month);
        void view_membership_dues(string type = "All");
        void view_preferred_members_rebate();

        string sales_report(Date date);
        string member_information(int index);

        string getMemberName(int id);     // Dillon - returns the members name for the id given
        string getMemberType(int id);   // Dillon - returns the members status for the id given
        void typeChange();

        void add_member(string the_name, int the_id, bool the_type, Date the_date);
        void add_member(Member m);
        void remove_member(int id);
        void remove_member_by_index(int index);
        void clear();
        void sort_by_member_id();
        void sort_by_name();
        void sort_by_date();
        void inputSales(const char* file_name);

        int load(QString file);
};

#endif // MEMBERCONTAINER_H
