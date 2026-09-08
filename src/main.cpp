#include <iostream>
#include <fstream>

#include "Resource.h"

using namespace std;

int choice = -1;

void readResources(ifstream& file) {
    string room;
    string name;
    string type;
    string availableS;

    while (!file.eof()) {
        getline(file, room, '|');
        cout << room << endl;

        getline(file, name, '|');
        cout << name << endl;

        getline(file, type, '|');
        cout << type << endl;

        getline(file, availableS);
        cout << availableS << endl;

        // reads newline character
        file.get();

        Resource rs(room, name, type, availableS == "Available");
        cout << rs.IsAvailable() << endl;
    }
}

int main() {
    ifstream resourceFile("data/resources.txt");
    if (!resourceFile.is_open()) {
        cout << "Could not open resources.txt!" << endl;
        return 1;
    }

    readResources(resourceFile);

    resourceFile.close();

    while (choice != 9) {
        cout << "===== Campus Resource Reservation System =====" << endl;
        cout << "1. View Resources" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. View Waiting Lists" << endl;
        cout << "5. Undo Cancellation" << endl;
        cout << "6. Search Reservations" << endl;
        cout << "7. Sort Resources" << endl;
        cout << "8. Generate Report" << endl;
        cout << "9. Exit\n\n" << flush;

        cout << "Enter Choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            default:
                // error message here
                break;
        }
    }

    return 0;
}