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

    // main menu loop
    while (choice != 12) {
        cout << "===== Campus Resource Reservation System =====\n";
        cout << "1. View Resources\n";
        cout << "2. View Reservations\n";
        cout << "3. Create Reservation\n";
        cout << "4. Cancel Reservation\n";
        cout << "5. View Waiting Lists\n";
        cout << "6. Undo Cancellation\n";
        cout << "7. Search Reservations\n";
        cout << "8. Sort Resources\n";
        cout << "9. Generate Report\n";
        cout << "10. View Cancellation History\n";
        cout << "11. Search Resource by ID\n";
        cout << "12. Exit\n\n" << flush;

        cout << "Enter Choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                reservMan.ViewResources();
                break;
            case 2:
                reservMan.ViewReservations();
                break;
            case 3:
                reservMan.CreateReservation();
                break;
            case 4:
                reservMan.CancelReservation();
                break;
            case 5:
                reservMan.ViewWaitingLists();
                break;
            case 6:
                reservMan.RestoreReservation();
                break;
            case 7: {
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
            case 8:
                reservMan.SortResourcesByName();
                break;
            case 9:
                reservMan.GenerateReport();
                break;
            case 10:
                reservMan.ViewCancellationHistory();
                break;
            case 11:
                reservMan.SearchResourceById();
                break;
            case 12:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Please enter a valid choice." << endl;
                break;
        }
    }

    return 0;
}