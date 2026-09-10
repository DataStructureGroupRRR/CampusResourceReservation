#include "Reservation.h"

using namespace std;

Reservation::Reservation(
    const string& id, 
    const string& studId, 
    const string& studName, 
    const string& resId, 
    const string& date
) {
    this->id = id;
    this->studId = studId;
    this->studName = studName;
    this->resId = resId;
    this->date = date;
}

string Reservation::GetId() const {
    return id;
}

string Reservation::GetStudentId() const {
    return studId;
}

string Reservation::GetStudentName() const {
    return studName;
}

string Reservation::GetResourceId() const {
    return resId;
}

string Reservation::GetDate() const {
    return date;
}