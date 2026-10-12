#include <sstream>
#include <iomanip>
#include <ctime>

#include "Date.h"

using namespace std;

Date Date::Today() {
    Date date;

    time_t timestamp = time(nullptr);
    tm* dateTime = localtime(&timestamp);

    date.year = dateTime->tm_year + 1900;
    date.month = dateTime->tm_mon + 1;
    date.day = dateTime->tm_mday;

    return date;
}

bool Date::operator==(const Date& other) const {
    return year == other.year
        && month == other.month
        && day == other.day;
}

bool Date::operator!=(const Date& other) const {
    return !(operator==(other));
}

bool Date::operator<(const Date& other) const {
    return year < other.year
        || month < other.month
        || day < other.day;
}

bool Date::operator>(const Date& other) const {
    return year > other.year
        || month > other.month
        || day > other.day;
}

bool Date::operator<=(const Date& other) const {
    return !(operator>(other));
}

bool Date::operator>=(const Date& other) const {
    return !(operator<(other));
}

string Date::ToString() const {
    stringstream ss;

    ss << right << setfill('0');
    
    ss << setw(2) << month << "/";
    ss << setw(2) << day << "/";
    ss << setw(4) << year;

    return ss.str();
}