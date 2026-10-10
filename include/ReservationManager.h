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

        //Milestone 2: sorts 'resources' alphabetically by name using merge sort
        void SortResourcesByName();

        //Prints active reservations, resource utilization, most requested resource
        // and waiting list statistics
        void GenerateReport() const;
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

        //Sorting(merger sort)
        void MergeSortByName(std::vector<Resource>& vec, int left, int right);
        void MeergeByName(std::vector<Resource>& vec, int left, int mid, int right);

        //Searching (binary search)
        void MergeSortById(std::vector<Resource>& vec, int left, int right)const;
        void MergeById(std::vector<Resource>& vec, int left, int mid, int right)const;
        int BinarySearchById(const std::vector<Resource>& sortedById, const std::string& resID)const;
        
};

#endif // RESERVATION_MAN_H