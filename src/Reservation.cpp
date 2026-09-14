#include "Reservation.h"

using namespace std;

Reservation::Reservation(
    int id, 
    int studId, 
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

int Reservation::GetId() const {
    return id;
}

int Reservation::GetStudentId() const {
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