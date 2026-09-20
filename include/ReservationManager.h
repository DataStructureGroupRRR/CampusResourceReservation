#ifndef RESERVATION_MAN_H
#define RESERVATION_MAN_H

#include <stack>
#include <vector>
#include <fstream>
#include <map>
#include <string>

#include "Resource.h"
#include "Reservation.h"
#include "Node.h"
#include "WaitingList.h"
#include "CancellationHistory.h"

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
        static void ViewReservations(Node<Reservation>* head);

        ReservationManager();

        void ReadResources(std::ifstream& file);
        void ViewResources();

        void CreateReservation();
        void CancelReservation();
        void RestoreReservation();
        void ViewReservations() const;
        bool SearchReservations(Node<Reservation>*& listHead) const;
        void ViewWaitingLists() const;
        void ViewCancellationHistory() const;
        ~ReservationManager();
    private:
        int highestId;

        int longestName;
        int longestType;

        std::vector<Resource> resources;

        Node<Reservation>* head;
        Node<Reservation>* tail;

        CancellationHistory cancellationHistory;

        std::map<std::string, WaitingList>waitingLists;

        Resource* FindResource(const std::string& resID);

        void MakeReservation(int studId, const std::string& studNAme, const std::string& resID);

        bool IsResourceBookedOnDate(const std::string& resID, const std::string& date) const;

        
};

#endif // RESERVATION_MAN_H