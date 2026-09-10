#include <stack>

#include "Reservation.h"
#include "Node.h"

class ReservationManager {
    public:
        void CreateReservation();
        void CancelReservation();
        void RestoreReservation();
        void ViewReservations() const;
        Node<Reservation>* SearchReservations() const;

        ~ReservationManager();
    private:
        Node<Reservation>* head;
        Node<Reservation>* tail;
};