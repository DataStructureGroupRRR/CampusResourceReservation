#include <iostream>

#include "ReservationManager.h"

using namespace std;

void ReservationManager::CreateReservation() {
    string studId;
    string studName;
    string resId;
    
    cout << "Student ID: ";
    cin >> studId;
    cin.get();
    
    cout << "Student Name: ";
    getline(cin, studName);
    cout << "Resource ID: ";
    cin >> resId;

    // TODO: write proper ids and dates
    Reservation r("0", studId, studName, resId, "today");
    Node<Reservation>* node = new Node<Reservation>(r);

    if (head) {
        tail->next = node;
        node->prev = tail;

        tail = node;
    } else {
        head = node;
        tail = node;
    }

    cout << "Reservation Created Successfully." << endl;
}

void ReservationManager::CancelReservation() {

}

void ReservationManager::RestoreReservation() {
    
}

void ReservationManager::ViewReservations() const {

}

Node<Reservation>* ReservationManager::SearchReservations() const {
    return nullptr;
}

ReservationManager::~ReservationManager() {
    // destroy all nodes

    Node<Reservation>* node = head;
    Node<Reservation>* nextNode = nullptr;

    do {
        nextNode = node->next;
        delete node;

        node = nextNode;
    } while (node);
}