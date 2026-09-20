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
    
    cout << "Student ID: ";
    cin >> studId;
    cin.get();
    
    cout << "Student Name: ";
    getline(cin, studName);
    cout << "Resource ID: ";
    cin >> resId;

    //using FindResource() helper (previously unused)
    Resource* res = FindResource(resId);

    if (!res) {
        cout << "No resource with ID " << resId << " was found.\n\n" << flush;
        return;
    }
    if (res -> IsAvailable()){
        res->SetAvailable(false);

        MakeReservation(studId, studName, resId);
        cout<< "Reservation Created Successfully.\n\n" << flush;
    }else{
        waitingLists[resId].AddStudent(studId, studName, resId);
        cout<<"Resource "<<resId<<" is currently unavailable. "<<studName<<" has been added to the waiting list.\n\n"<<flush;
    }
}


void ReservationManager::CancelReservation() {
    string resId = cancellationHistory.CancelReservation(head, tail);

    if (resId.empty()) {
        return; // no reservation was cancelled
    }

    auto it = waitingLists.find(resId);
    if (it != waitingLists.end() && !it->second.IsEmpty()) {
        WaitingStudent nextStudent (0,"","");
        it->second.RemoveStudent(nextStudent); //dequeue the front

         // Resource it's handed directly to the next student
        MakeReservation(nextStudent.studId , nextStudent.studName, resId);

        cout<<"Resource "<<resId<<" has been assigned to the next student in the waiting list: "<<nextStudent.studName<<" (Student ID: "<<nextStudent.studId<<").\n\n"<<flush;
    }else{
        //If nobody is waiting: restore availability
        Resource* res = FindResource(resId);
        if (res) {
            res->SetAvailable(true);
        }
    }
}

void ReservationManager::RestoreReservation() {
    cancellationHistory.RestoreReservation(head, tail);
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
    if (waitingLists.empty()) {
        cout << "No waiting lists available.\n\n" << flush;
        return;
    }

    bool anyNonEmpty = false;
    for (const auto& pair : waitingLists) {
        if (!pair.second.IsEmpty()) {
            anyNonEmpty = true;
            cout << "Waiting List for Resource ID " << pair.first << ":\n";
            pair.second.Display();
        }
    }
    if (!anyNonEmpty) {
        cout<<"All waiting lists are empty.\n\n"<<flush;
        }
    }
    


ReservationManager::~ReservationManager() {
    // destroy all nodes

    Node<Reservation>* node = head;
    Node<Reservation>* nextNode = nullptr;

    DELETE_LL(node, nextNode)
}