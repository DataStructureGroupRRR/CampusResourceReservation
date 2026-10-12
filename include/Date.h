#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
    public:
        static Date Today();

        int year = 0;
        int month = 0;
        int day = 0;

        bool operator==(const Date& other) const;
        bool operator!=(const Date& other) const;
        bool operator<(const Date& other) const;
        bool operator>(const Date& other) const;
        bool operator<=(const Date& other) const;
        bool operator>=(const Date& other) const;

        std::string ToString() const;
};

#endif // DATE_H