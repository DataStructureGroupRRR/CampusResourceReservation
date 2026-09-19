#include <iostream>

#include "CancellationHistory.h"

using namespace std;

void CancellationHistory::CancelReservation(Node<Reservation>*& head, Node<Reservation>*& tail) {
    int id;

    cout << "Reservation ID: ";
    cin >> id;

    // find the node with the matching reservation ID
    Node<Reservation>* node = head;
    while (node) {
        if (node->value.GetId() == id) {
            break;
        }

        node = node->next;
    }

    if (!node) {
        cout << "No reservation found with ID " << id << ".\n\n" << flush;
        return;
    }

    // unlink node from the doubly linked list
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }

    // push the cancelled reservation onto the history stack so it can be undone
    cancelledHistory.push(node->value);
    delete node;

    cout << "Reservation Cancelled.\n";
    cout << "Added to cancellation history.\n\n" << flush;
}

void CancellationHistory::RestoreReservation(Node<Reservation>*& head, Node<Reservation>*& tail) {
    if (cancelledHistory.empty()) {
        cout << "No cancellations to undo.\n\n" << flush;
        return;
    }

    // only the most recently cancelled reservation may be restored
    Reservation r = cancelledHistory.top();
    cancelledHistory.pop();

    Node<Reservation>* node = new Node<Reservation>(r);

    if (head) {
        tail->next = node;
        node->prev = tail;

        tail = node;
    } else {
        head = node;
        tail = node;
    }

    cout << "Reservation Restored Successfully.\n\n" << flush;
}