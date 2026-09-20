#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H

#include <stack>
#include <string>
#include "Reservation.h"
#include "Node.h"

class CancellationHistory {
    public:
        //Returns the reservation that was cancelled and removes it from the history stack
        std::string CancelReservation(Node<Reservation>*& head, Node<Reservation>*& tail);
        void RestoreReservation(Node<Reservation>*& head, Node<Reservation>*& tail);

        //displays the full cancellation stack
        void DisplayHistory() const;
    private:
        std::stack<Reservation> cancelledHistory;
};

#endif // CANCELLATION_HISTORY_H