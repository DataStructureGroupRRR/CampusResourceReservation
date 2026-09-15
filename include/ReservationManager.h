#ifndef RESERVATION_MAN_H
#define RESERVATION_MAN_H

#include <stack>

#include "Reservation.h"
#include "Node.h"

#define ADD_LIST \
Node<Reservation>* listNode = new Node<Reservation>(node->value);\
if (listHead) {\
    listTail->next = listNode;\
    listNode->prev = listTail;\
\
    listTail = listNode;\
} else {\
    listHead = listNode;\
    listTail = listNode;\
}

class ReservationManager {
    public:
        static void ViewReservations(Node<Reservation>* begin);

        ReservationManager();

        void CreateReservation();
        void CancelReservation();
        void RestoreReservation();
        void ViewReservations() const;
        Node<Reservation>* SearchReservations() const;

        ~ReservationManager();
    private:
        int highestId;

        Node<Reservation>* head;
        Node<Reservation>* tail;

        std::stack<Reservation> cancelledHistory;
};

#endif // RESERVATION_MAN_H