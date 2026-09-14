#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "Resource.h"
#include "ReservationManager.h"

using namespace std;

void readResources(ifstream& file, vector<Resource>& resources, int& longestName, int& longestType) {
    string id;
    string name;
    string type;
    string availableS;

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

void viewResources(vector<Resource>& resources, int longestName, int longestType) {
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

int main() {
    int choice = -1;
    int longestName = 0;
    int longestType = 0;

    // reads from resources.txt
    ifstream resourceFile("data/resources.txt");
    vector<Resource> resources;

    if (!resourceFile.is_open()) {
        cout << "Could not open resources.txt!" << endl;
        return 1;
    }

    readResources(resourceFile, resources, longestName, longestType);

    resourceFile.close();

    ReservationManager reservMan;

    while (choice != 9) {
        cout << "===== Campus Resource Reservation System =====\n";
        cout << "1. View Resources\n";
        cout << "2. Create Reservation\n";
        cout << "3. Cancel Reservation\n";
        cout << "4. View Waiting Lists\n";
        cout << "5. Undo Cancellation\n";
        cout << "6. Search Reservations\n";
        cout << "7. Sort Resources\n";
        cout << "8. Generate Report\n";
        cout << "9. Exit\n\n" << flush;

        cout << "Enter Choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                viewResources(resources, longestName, longestType);
                break;
            case 2:
                reservMan.CreateReservation();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                reservMan.ViewReservations();
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