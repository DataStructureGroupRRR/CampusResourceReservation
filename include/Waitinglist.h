#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <string>

// Represents a student waiting for a resource to become available.
struct WaitingStudent {
    int studId;
    std::string studName;
    std::string resId;   // matches Resource::GetId(), which returns string

    WaitingStudent(int studId, const std::string& studName, const std::string& resId) {
        this->studId = studId;
        this->studName = studName;
        this->resId = resId;
    }
};

// Internal linked-list node for the queue.
struct WaitNode {
    WaitingStudent value;
    WaitNode* next;

    WaitNode(const WaitingStudent& value) : value(value) {
        this->next = nullptr;
    }
};

// A FIFO waiting list implemented as a singly linked list with
// front and rear pointers, giving O(1) enqueue and O(1) dequeue.
class WaitingList {
private:
    WaitNode* head;
    WaitNode* tail;
    int count;

public:
    WaitingList();
    ~WaitingList();

    // Adds a student to the back of the waiting list. O(1).
    void AddStudent(int studId, const std::string& studName, const std::string& resId);

    // Removes and returns the student at the front of the list.
    // Returns false if the list was empty (outStudent left unset).
    bool RemoveStudent(WaitingStudent& outStudent);

    // Prints all students currently on the waiting list, front to back. O(n).
    void Display() const;

    bool IsEmpty() const;
    int Size() const;
};

#endif // WAITINGLIST_H