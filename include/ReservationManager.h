#include <stack>

#include "Reservation.h"
#include "Node.h"

class ReservationManager {
    public:
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
};