#include <iostream>
#include <iomanip>
#include <ctime>

#include "ReservationManager.h"

using namespace std;

void ReservationManager::ViewReservations(Node<Reservation>* head) {
    int studLen = 0;

    int curLen = 0;
    Node<Reservation>* node = head;
    while (node) {
        curLen = node->value.GetStudentName().length();
        if (curLen > studLen) {
            studLen = curLen;
        }

        node = node->next;
    }
    studLen = max(studLen, 12) + 2;

    cout << setfill(' ') << left;

    cout << setw(8) << "ID";
    cout << setw(12) << "Student ID";
    cout << setw(studLen) << "Student Name";
    cout << setw(14) << "Resource ID";
    cout << setw(12) << "Date" << endl;

    cout << setfill('-') << setw(8 + 12 + studLen + 14 + 12) << "" << endl;

    node = head;
    while (node) {
        cout << right;
        cout << setfill('0') << setw(3) << node->value.GetId();
        cout << setfill(' ') << setw(5) << "";
        cout << setfill('0') << setw(4) << node->value.GetStudentId();
        cout << setfill(' ') << setw(8) << "";

        cout << left;
        cout << setw(studLen) << node->value.GetStudentName();
        cout << setw(14) << node->value.GetResourceId();
        cout << setw(12) << node->value.GetDate() << endl;

        node = node->next;
    }

    cout << endl;
}

ReservationManager::ReservationManager() {
    this->highestId = 0;
    this->longestName = 0;
    this->longestType = 0;

    this->head = nullptr;
    this->tail = nullptr;
}

void ReservationManager::ReadResources(ifstream& file) {
    string id;
    string name;
    string type;
    string availableS;

    resources.clear();

    while (file.peek() != EOF && !file.eof()) {
        getline(file, id, '|');
        getline(file, name, '|');
        getline(file, type, '|');
        getline(file, availableS);

        Resource rs(id, name, type, availableS == "Available");
        resources.push_back(rs);

        // gets the lengths of the longest names for formatting
        if (name.length() > longestName) {
            longestName = name.length();
        }

        if (type.length() > longestType) {
            longestType = type.length();
        }
    }
}

void ReservationManager::ViewResources() {
    // adds padding to formatting

    int nameLen = max(longestName, 2) + 4;
    int typeLen = max(longestType, 4) + 4;

    cout << setfill(' ') << left;

    cout << setw(8) << "ID";
    cout << setw(nameLen) << "Name";
    cout << setw(typeLen) << "Type";
    cout << setw(12) << "Availability" << endl;

    cout << setfill('-') << setw(8 + nameLen + typeLen + 12) << "" << endl;
    
    cout << setfill(' ');
    for (const Resource& res : resources) {
        cout << setw(8) << res.GetId();
        cout << setw(nameLen) << res.GetName();
        cout << setw(typeLen) << res.GetType();
        cout << setw(12) << (res.IsAvailable() ? "Available" : "Unavailable") << endl;
    }

    cout << endl;
}
// WAITLIST: helper to get a mutable pointer to a resource by ID, since
// 'resources' is a vector of values and existing loops used const refs.
Resource* ReservationManager::FindResource(const string& resId) {
    for (Resource& res : resources) {
        if (res.GetId() == resId) {
            return &res;
        }
    }
    return nullptr;
}

// WAITLIST: factored out of CreateReservation() so CancelReservation() can
// auto-create a reservation for the next waiting student using identical logic.
void ReservationManager::MakeReservation(int studId, const string& studName, const string& resId) {
    char date[11];

    highestId++;

    time_t timestamp = time(nullptr);
    tm* dateTime = localtime(&timestamp);
    strftime(date, 11, "%m/%d/%Y", dateTime);

    Reservation r(highestId, studId, studName, resId, date);
    Node<Reservation>* node = new Node<Reservation>(r);

    if (head) {
        tail->next = node;
        node->prev = tail;

        tail = node;
    }
    else {
        head = node;
        tail = node;
    }
}
void ReservationManager::CreateReservation() {
    int studId;
    string studName;
    string resId;

    bool foundRes = false;
    char date[11];
    
    cout << "Student ID: ";
    cin >> studId;
    cin.get();
    
    cout << "Student Name: ";
    getline(cin, studName);
    cout << "Resource ID: ";
    cin >> resId;

    for (const Resource& res : resources) {
        if (resId == res.GetId()) {
            foundRes = true;
            break;
        }
    }

    if (!foundRes) {
        cout << "No reservation with ID " << resId << " was found.\n\n" << flush;
        return;
    }

    highestId++;

    time_t timestamp = time(nullptr);
    tm* dateTime = localtime(&timestamp);
    strftime(date, 11, "%m/%d/%Y", dateTime);

    Reservation r(highestId, studId, studName, resId, date);
    Node<Reservation>* node = new Node<Reservation>(r);

    if (head) {
        tail->next = node;
        node->prev = tail;

        tail = node;
    } else {
        head = node;
        tail = node;
    }

    cout << "Reservation Created Successfully.\n\n" << flush;
}

void ReservationManager::CancelReservation() {
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

void ReservationManager::RestoreReservation() {
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

void ReservationManager::ViewReservations() const {
    ReservationManager::ViewReservations(this->head);
}

bool ReservationManager::SearchReservations(Node<Reservation>*& listHead) const {
    int choice = 0;
    Node<Reservation>* node = nullptr;

    listHead = nullptr;
    Node<Reservation>* listTail = nullptr;
    
    cout << "Search via\n";
    cout << "1. Resource ID\n";
    cout << "2. Reservation ID\n";
    cout << "3. Student ID\n";
    cout << "4. Student Name\n";
    cout << "5. Cancel\n\n" << flush;

    while (choice == 0) {
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string resId;
                
                cout << "Enter Resource ID: ";
                cin >> resId;

                node = head;
                while (node) {
                    if (node->value.GetResourceId() == resId) {
                        ADD_LIST
                    }
                    node = node->next;
                }
                break;
            }
            case 2: {
                int id;

                cout << "Enter Reservation ID: ";
                cin >> id;

                node = head;
                while (node) {
                    if (node->value.GetId() == id) {
                        ADD_LIST
                    }
                    node = node->next;
                }
                break;
            }
            case 3: {
                int studId;

                cout << "Enter Student ID: ";
                cin >> studId;

                node = head;
                while (node) {
                    if (node->value.GetStudentId() == studId) {
                        ADD_LIST
                    }
                    node = node->next;
                }
                break;
            }
            case 4: {
                string studName;

                cout << "Enter Student Name: ";

                // removes new line character from buffer if present
                if (cin.peek() == '\n') {
                    cin.get();
                }
                getline(cin, studName);

                node = head;
                while (node) {
                    if (node->value.GetStudentName() == studName) {
                        ADD_LIST
                    }
                    node = node->next;
                }
                break;
            }
            case 5:
                return false;
            default:
                cout << "Please enter a valid choice." << endl;
                choice = 0;
                break;
        }
    }

    return true;
}

void ReservationManager::ViewWaitingLists() const {
    
}

ReservationManager::~ReservationManager() {
    // destroy all nodes

    Node<Reservation>* node = head;
    Node<Reservation>* nextNode = nullptr;

    DELETE_LL(node, nextNode)
}