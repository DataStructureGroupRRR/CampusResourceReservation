#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "Resource.h"
#include "ReservationManager.h"

using namespace std;

int main() {
    int choice = -1;

    // reads from resources.txt
    ifstream resourceFile("data/resources.txt");
    ReservationManager reservMan;

    if (!resourceFile.is_open()) {
        cout << "Could not open resources.txt!" << endl;
        return 1;
    }

    reservMan.ReadResources(resourceFile);
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
                reservMan.ViewResources();
                break;
            case 2:
                reservMan.CreateReservation();
                break;
            case 3:
                reservMan.CancelReservation();
                break;
            case 4:
                reservMan.ViewWaitingLists();
                break;
            case 5:
                reservMan.RestoreReservation();
                break;
            case 6: {
                reservMan.ViewReservations();

                Node<Reservation>* searchHead = nullptr;
                Node<Reservation>* nextNode = nullptr;
                if (!reservMan.SearchReservations(searchHead)) {
                    break;
                }

                if (searchHead) {
                    ReservationManager::ViewReservations(searchHead);
                    DELETE_LL(searchHead, nextNode)
                } else {
                    cout << "No matching reservations found.\n\n" << flush;
                }
                break;
            }
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            default:
                cout << "Please enter a valid choice." << endl;
                break;
        }
    }

    return 0;
}