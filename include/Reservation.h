#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

#include "Date.h"

class Reservation {
    public:
        Reservation(
            int id, 
            int studId, 
            const std::string& studName, 
            const std::string& resId, 
            const Date& date
        );

        int GetId() const;
        int GetStudentId() const;
        std::string GetStudentName() const;
        std::string GetResourceId() const;
        const Date& GetDate() const;
    private:
        int id;
        int studId;
        std::string studName;
        std::string resId;
        Date date;
};

#endif // RESERVATION_H