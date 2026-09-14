#include <iostream>
#include <iomanip>
#include <ctime>

#include "ReservationManager.h"

using namespace std;

ReservationManager::ReservationManager() {
    this->highestId = 0;

    this->head = nullptr;
    this->tail = nullptr;
}

void ReservationManager::CreateReservation() {
    int studId;
    string studName;
    string resId;

    char date[11];
    
    cout << "Student ID: ";
    cin >> studId;
    cin.get();
    
    cout << "Student Name: ";
    getline(cin, studName);
    cout << "Resource ID: ";
    cin >> resId;

    // TODO: write proper dates
    highestId++;

    time_t timestamp = time(nullptr);
    tm* dateTime = localtime(&timestamp);
    strftime(date, 11, "%m/%d/%Y", dateTime);

    Reservation r(highestId, studId, studName, resId, date);
    Node<Reservation>* node = new Node<Reservation>(r);

    if (head) {
        tail->next = node;
        node->prev = tail;

        tail = node;
    } else {
        head = node;
        tail = node;
    }

    cout << "Reservation Created Successfully.\n\n" << flush;
}

void ReservationManager::CancelReservation() {

}

void ReservationManager::RestoreReservation() {
    
}

void ReservationManager::ViewReservations() const {
    int studLen = 0;

    int curLen = 0;
    Node<Reservation>* node = head;
    while (node) {
        curLen = node->value.GetStudentName().length();
        if (curLen > studLen) {
            studLen = curLen;
        }

        node = node->next;
    }
    studLen = max(studLen, 12) + 2;

    cout << setfill(' ') << left;

    cout << setw(8) << "ID";
    cout << setw(12) << "Student ID";
    cout << setw(studLen) << "Student Name";
    cout << setw(14) << "Resource ID";
    cout << setw(12) << "Date" << endl;

    cout << setfill('-') << setw(8 + 12 + studLen + 14 + 12) << "" << endl;

    node = head;
    while (node) {
        cout << right;
        cout << setfill('0') << setw(3) << node->value.GetId();
        cout << setfill(' ') << setw(5) << "";
        cout << setfill('0') << setw(4) << node->value.GetStudentId();
        cout << setfill(' ') << setw(8) << "";

        cout << left;
        cout << setw(studLen) << node->value.GetStudentName();
        cout << setw(14) << node->value.GetResourceId();
        cout << setw(12) << node->value.GetDate() << endl;

        node = node->next;
    }

    cout << endl;
}

Node<Reservation>* ReservationManager::SearchReservations() const {
    int choice = 0;
    Node<Reservation>* node = nullptr;
    
    cout << "Search via" << endl;
    cout << "1. Resource ID\n";
    cout << "2. Reservation ID\n";
    cout << "3. Student ID\n";
    cout << "4. Student Name\n";
    cout << "5. Cancel\n\n" << flush;

    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            string resId;
            

            break;
        }
        case 2: {
            break;
        }
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }

    return nullptr;
}

ReservationManager::~ReservationManager() {
    // destroy all nodes

    Node<Reservation>* node = head;
    Node<Reservation>* nextNode = nullptr;

    while (node) {
        nextNode = node->next;
        delete node;

        node = nextNode;
    }
}