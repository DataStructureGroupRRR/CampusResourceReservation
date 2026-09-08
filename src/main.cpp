#include <iostream>
#include <fstream>
#include <vector>

#include "Resource.h"

using namespace std;

int choice = -1;

void readResources(ifstream& file, vector<Resource>& resources) {
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
    }
}

void viewResources(vector<Resource>& resources) {
    for (const Resource& res : resources) {
        cout << res.GetId() << endl;
    }
}

int main() {
    ifstream resourceFile("data/resources.txt");
    vector<Resource> resources;

    if (!resourceFile.is_open()) {
        cout << "Could not open resources.txt!" << endl;
        return 1;
    }

    readResources(resourceFile, resources);

    resourceFile.close();

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
                viewResources(resources);
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