#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H

#include <stack>

#include "Reservation.h"
#include "Node.h"

class CancellationHistory {
    public:
        void CancelReservation(Node<Reservation>*& head, Node<Reservation>*& tail);
        void RestoreReservation(Node<Reservation>*& head, Node<Reservation>*& tail);
    private:
        std::stack<Reservation> cancelledHistory;
};

#endif // CANCELLATION_HISTORY_H