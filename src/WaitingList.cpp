#include "WaitingList.h"
#include <iostream>
#include <iomanip>

using namespace std;

WaitingList::WaitingList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

WaitingList::~WaitingList() {
    // clean up any remaining nodes to avoid memory leaks
    WaitNode* node = head;
    WaitNode* nextNode = nullptr;

    while (node) {
        nextNode = node->next;
        delete node;
        node = nextNode;
    }
}

//Function to add a student to the waiting list
void WaitingList::AddStudent(int studId, const string& studName, const string& resId) {
    WaitingStudent newStudent(studId, studName, resId);
    WaitNode* node = new WaitNode(newStudent);

    if (tail) {
        tail->next = node;
        tail = node;
    }
    else {
        head = node;
        tail = node;
    }

    count++;
}

//Function to remove a student from the waiting list
bool WaitingList::RemoveStudent(WaitingStudent& outStudent) {
    if (!head) {
        return false;
    }

    WaitNode* toDelete = head;
    outStudent = toDelete->value;

    head = head->next;
    if (!head) {
        tail = nullptr;
    }

    delete toDelete;
    count--;
    return true;
}

//fucntion to see the waiting list for a specific resource.
void WaitingList::Display() const {
    if (!head) {
        cout << "Waiting list is empty.\n\n" << flush;
        return;
    }

    cout << setfill(' ') << left;
    cout << setw(6) << "Pos";
    cout << setw(12) << "Student ID";
    cout << setw(20) << "Student Name";
    cout << setw(12) << "Resource ID" << endl;

    cout << setfill('-') << setw(50) << "" << endl;
    cout << setfill(' ');

    WaitNode* node = head;
    int position = 1;
    while (node) {
        cout << setw(6) << position;
        cout << setw(12) << node->value.studId;
        cout << setw(20) << node->value.studName;
        cout << setw(12) << node->value.resId << endl;

        node = node->next;
        position++;
    }

    cout << endl;
}

bool WaitingList::IsEmpty() const {
    return head == nullptr;
}

int WaitingList::Size() const {
    return count;
}