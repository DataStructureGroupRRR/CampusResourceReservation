#include <iostream>

using namespace std;

int choice = -1;

int main() {
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

    cout << choice << endl;

    return 0;
}