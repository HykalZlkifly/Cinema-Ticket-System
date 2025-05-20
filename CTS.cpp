#include "CTS.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

CTS::CTS(int movieCount, int seatCount) {
    this->movieCount = movieCount;
    this->seatCount = seatCount;

    movies = new string[movieCount]{
        "Kahar Kapla High Council",
        "Babah",
        "Ejen Ali the Movie 2",
        "Spider-Man: Beyond the Spider-Verse",
        "Sonic The Hedgehog 3",
        "The Matrix Reimagined",
        "Fast and Furious 11",
        "Avatar: The Next Journey",
        "Mission Impossible: Beyond",
        "Frozen: The Final Chapter"
    };

    time = new string*[movieCount];
    for (int i = 0; i < movieCount; i++) {
        time[i] = new string[5]{
            "10:00 AM", "12:00 PM", "2:00 PM", "4:00 PM", "6:00 PM"
        };
    }

    hall = new string[movieCount]{
        "Hall 1", "Hall 2", "Hall 3", "Hall 4", "Hall 5",
        "Hall 6", "Hall 7", "Hall 8", "Hall 9", "Hall 10"
    };

    prices = new double[movieCount]{15.00, 12.00, 20.00, 18.00, 22.00, 17.50, 16.00, 19.00, 14.50, 21.00};

    foodAndBeverageOptions = new string*[movieCount];
    for (int i = 0; i < movieCount; i++) {
        foodAndBeverageOptions[i] = new string[3]{"Popcorn", "Soda", "Combo Meal"};
    }

    seats = new int**[movieCount];
    payments = new double**[movieCount];
    bookingStatus = new bool**[movieCount];
    foodChoices = new string**[movieCount];
    movieCharges = new double*[movieCount]();
    foodCharges = new double*[movieCount]();
    waitingLists = new Queue[movieCount];

    for (int i = 0; i < movieCount; i++) {
        seats[i] = new int*[5];
        payments[i] = new double*[5];
        bookingStatus[i] = new bool*[5];
        foodChoices[i] = new string*[5];
        movieCharges[i] = new double[5]();
        foodCharges[i] = new double[5]();

        for (int j = 0; j < 5; j++) {
            seats[i][j] = new int[seatCount]();
            payments[i][j] = new double[seatCount]();
            bookingStatus[i][j] = new bool[seatCount]();
            foodChoices[i][j] = new string[seatCount]();
        }
    }
}

CTS::~CTS() {
    for (int i = 0; i < movieCount; i++) {
        for (int j = 0; j < 5; j++) {
            delete[] seats[i][j];
            delete[] payments[i][j];
            delete[] bookingStatus[i][j];
            delete[] foodChoices[i][j];
        }
        delete[] seats[i];
        delete[] payments[i];
        delete[] bookingStatus[i];
        delete[] foodChoices[i];
        delete[] foodAndBeverageOptions[i];
        delete[] time[i];
    }
    delete[] seats;
    delete[] payments;
    delete[] bookingStatus;
    delete[] foodChoices;
    delete[] foodAndBeverageOptions;
    delete[] time;
    delete[] movies;
    delete[] hall;
    delete[] prices;
    delete[] movieCharges;
    delete[] foodCharges;
    delete[] waitingLists;
}

void CTS::ShowMovies() {
    cout << "Available Movies:\n";
    for (int i = 0; i < movieCount; i++) {
        cout << i + 1 << ". " << movies[i]
             << " | Hall: " << hall[i]
             << " | Price: $" << fixed << setprecision(2) << prices[i] << endl;
        cout << "   Showtimes: ";
        for (int j = 0; j < 5; j++) {
            cout << time[i][j];
            if (j < 4) cout << ", ";
        }
        cout << endl;
    }
}

void CTS::Display(int movieID, int showtimeID) {
    if (movieID < 1 || movieID > movieCount) {
        cout << "Invalid movie selection!\n";
        return;
    }

    if (showtimeID < 1 || showtimeID > 5) {
        cout << "Invalid showtime selection!\n";
        return;
    }

    movieID--;
    showtimeID--;
    cout << movies[movieID] << " | Hall: " << hall[movieID] << endl;
    cout << "Showtime: " << time[movieID][showtimeID] << endl;

    for (int j = 0; j < seatCount; j++) {
        cout << "Seat " << j + 1 << ": " << (seats[movieID][showtimeID][j] ? "Booked" : "Empty") << endl;
    }
}

void CTS::BookSeat(int movieID, int showtimeID, int seatNumber) {
    if (movieID < 1 || movieID > movieCount) {
        cout << "Invalid movie selection!\n";
        return;
    }

    if (showtimeID < 1 || showtimeID > 5) {
        cout << "Invalid showtime selection!\n";
        return;
    }

    movieID--;
    showtimeID--;

    if (seatNumber < 1 || seatNumber > seatCount) {
        cout << "Invalid seat number!\n";
        return;
    }

    if (seats[movieID][showtimeID][seatNumber - 1] == 1) {
        cout << "Seat " << seatNumber << " for movie " << movies[movieID] << " at " << time[movieID][showtimeID] << " is already booked!\n";
        return;
    }

    seats[movieID][showtimeID][seatNumber - 1] = 1;
    bookingStatus[movieID][showtimeID][seatNumber - 1] = true;
    payments[movieID][showtimeID][seatNumber - 1] = prices[movieID];
    movieCharges[movieID][showtimeID] += prices[movieID];
    cout << "Seat " << seatNumber << " reserved for movie " << movies[movieID] << " at " << time[movieID][showtimeID] << ".\n";

    string buyFood;
    while (true) {
        cout << "\nWould you like to buy food or beverage? (yes/no): ";
        cin >> buyFood;
        if (buyFood == "yes" || buyFood == "Yes" || buyFood == "no" || buyFood == "No") {
            break;
        } else {
            cout << "Invalid input. Please enter 'yes' or 'no'.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    if (buyFood == "yes" || buyFood == "Yes") {
        int foodChoice;
        while (true) {
            cout << "\nFood and Beverage Options:\n";
            cout << "1. Popcorn ($5.00)\n";
            cout << "2. Soda ($3.00)\n";
            cout << "3. Combo Meal ($7.00)\n";
            cout << "4. None (Skip)\n";
            cout << "Please select your option (1-4): ";
            cin >> foodChoice;

            if (cin.fail() || foodChoice < 1 || foodChoice > 4) {
                cout << "Invalid choice. Please select a valid option.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
        }

        string food;
        if (foodChoice == 1) {
            food = "Popcorn";
            foodCharges[movieID][showtimeID] += 5.00;
        } else if (foodChoice == 2) {
            food = "Soda";
            foodCharges[movieID][showtimeID] += 3.00;
        } else if (foodChoice == 3) {
            food = "Combo Meal";
            foodCharges[movieID][showtimeID] += 7.00;
        } else {
            food = "None";
        }
        foodChoices[movieID][showtimeID][seatNumber - 1] = food;
        cout << "You selected: " << food << "\n";
    }
}

void CTS::CancelBooking(int movieID, int showtimeID, int seatNumber) {
    if (movieID < 1 || movieID > movieCount) {
        cout << "Invalid movie selection!\n";
        return;
    }

    if (showtimeID < 1 || showtimeID > 5) {
        cout << "Invalid showtime selection!\n";
        return;
    }

    movieID--;
    showtimeID--;

    if (seatNumber < 1 || seatNumber > seatCount) {
        cout << "Invalid seat number!\n";
        return;
    }

    if (seats[movieID][showtimeID][seatNumber - 1] == 0) {
        cout << "Seat " << seatNumber << " is not booked!\n";
        return;
    }

    seats[movieID][showtimeID][seatNumber - 1] = 0;
    bookingStatus[movieID][showtimeID][seatNumber - 1] = false;
    movieCharges[movieID][showtimeID] -= prices[movieID];
    cout << "Booking for Seat " << seatNumber << " has been canceled for movie " << movies[movieID] << " at " << time[movieID][showtimeID] << ".\n";
}

void CTS::AddToWaitingList(int movieID, string personName) {
    if (movieID < 1 || movieID > movieCount) {
        cout << "Invalid movie selection!\n";
        return;
    }

    movieID--;
    waitingLists[movieID].Insert(personName);
    cout << personName << " added to the waiting list for movie " << movies[movieID] << ".\n";
}

void CTS::ProcessWaitingList(int movieID) {
    if (movieID < 1 || movieID > movieCount) {
        cout << "Invalid movie selection!\n";
        return;
    }
    else
    cout <<"\nThere is no people waiting for any movie ";

    movieID--;
    while (waitingLists[movieID].getCount() > 0) {
        string personName = waitingLists[movieID].Remove();
        cout << "Processing waiting list: " << personName << " has been notified for available tickets for movie " << movies[movieID] << ".\n";
    }

}

void CTS::ProceedToPayment() {
    double totalPayment = 0;
    cout << "\nProceeding to Payment:\n";

    for (int i = 0; i < movieCount; i++) {
        for (int j = 0; j < 5; j++) {
            totalPayment += movieCharges[i][j] + foodCharges[i][j];
        }
    }

    cout << "Total Payment Due: $" << fixed << setprecision(2) << totalPayment << endl;

    double paymentAmount;
    while (true) {
        cout << "Enter payment amount: $";
        cin >> paymentAmount;

        // Handle invalid input
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid amount.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Handle insufficient amount
        if (paymentAmount < totalPayment) {
            string proceed;
            cout << "Insufficient amount. Would you like to proceed with this payment? (yes/no): ";
            cin >> proceed;

            if (proceed == "yes" || proceed == "Yes") {
                break;
            } else if (proceed == "no" || proceed == "No") {
                cout << "Returning to main menu.\n";
                return;
            } else {
                cout << "Invalid option. Please enter 'yes' or 'no'.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } else {
            double balance = paymentAmount - totalPayment;
            if (balance > 0) {
                cout << "Payment Successful! Your balance is $" << fixed << setprecision(2) << balance << ". Thank you for your payment.\n";
            } else {
                cout << "Payment Successful! Thank you for your payment.\n";
            }
            break;
        }
    }

    for (int i = 0; i < movieCount; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < seatCount; k++) {
                if (bookingStatus[i][j][k]) {
                    payments[i][j][k] = prices[i];
                }
            }
        }
    }

}

void CTS::SortMovies() {
    cout << "\nMovies with Paid Bookings Sorted by Earliest Showtime:\n";

    string* tempMovies = new string[movieCount];
    string* tempHalls = new string[movieCount];
    string* tempEarliestShowtime = new string[movieCount];
    int tempCount = 0;

    for (int i = 0; i < movieCount; i++) {
        bool hasPaidBooking = false;
        string earliestShowtime = "";
        int earliestTimeInMinutes = INT_MAX;

        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < seatCount; k++) {
                if (bookingStatus[i][j][k] && payments[i][j][k] > 0) {
                    hasPaidBooking = true;
                    int currentTimeInMinutes = stoi(time[i][j].substr(0, 2)) * 60 + stoi(time[i][j].substr(3, 2));
                    if (currentTimeInMinutes < earliestTimeInMinutes) {
                        earliestTimeInMinutes = currentTimeInMinutes;
                        earliestShowtime = time[i][j];
                    }
                }
            }
        }

        if (hasPaidBooking) {
            tempMovies[tempCount] = movies[i];
            tempHalls[tempCount] = hall[i];
            tempEarliestShowtime[tempCount] = earliestShowtime;
            tempCount++;
        }
    }

    for (int i = 0; i < tempCount - 1; i++) {
        for (int j = i + 1; j < tempCount; j++) {
            int timeI = stoi(tempEarliestShowtime[i].substr(0, 2)) * 60 + stoi(tempEarliestShowtime[i].substr(3, 2));
            int timeJ = stoi(tempEarliestShowtime[j].substr(0, 2)) * 60 + stoi(tempEarliestShowtime[j].substr(3, 2));
            if (timeJ < timeI) {
                swap(tempMovies[i], tempMovies[j]);
                swap(tempHalls[i], tempHalls[j]);
                swap(tempEarliestShowtime[i], tempEarliestShowtime[j]);
            }
        }
    }

    if (tempCount == 0) {
        cout << "No movies with paid bookings.\n";
    } else {
        for (int i = 0; i < tempCount; i++) {
            cout << tempMovies[i] << " | Hall: " << tempHalls[i] << " | Showtime: " << tempEarliestShowtime[i] << endl;
        }
    }

    delete[] tempMovies;
    delete[] tempHalls;
    delete[] tempEarliestShowtime;
}

void CTS::Menu() {
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Show available movies\n";
        cout << "2. Display seating\n";
        cout << "3. Book seat\n";
        cout << "4. Cancel booking\n";
        cout << "5. Add to waiting list\n";
        cout << "6. Process waiting list\n";
        cout << "7. Proceed to payment\n";
        cout << "8. Display movies by showtime\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate choice input
        if (cin.fail() || choice < 1 || choice > 9) {
            cout << "Invalid choice! Try again.\n";
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue;
        }

        switch (choice) {
        case 1:
            ShowMovies();
            break;
        case 2:
            {
                int movieID, showtimeID;
                cout << "Enter movie ID to display: ";
                cin >> movieID;
                // Validate movieID input
                if (cin.fail() || movieID < 1 || movieID > movieCount) {
                    cout << "Invalid movie ID! Try again.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    break;
                }
                cout << "Enter showtime ID to display (1-5): ";
                cin >> showtimeID;
                // Validate showtimeID input
                if (cin.fail() || showtimeID < 1 || showtimeID > 5) {
                    cout << "Invalid showtime ID! Try again.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    break;
                }
                Display(movieID, showtimeID);
                break;
            }
case 3:
            {
                int movieID, showtimeID, seatNumber;
                cout << "Enter movie ID to book: ";
                cin >> movieID;
                // Validate movieID input
                if (cin.fail() || movieID < 1 || movieID > movieCount) {
                    cout << "Invalid movie ID! Try again.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    break;
                }
                cout << "Available showtimes for movie " << movies[movieID - 1] << ":\n";
                for (int i = 0; i < 5; i++) {
                    cout << i + 1 << ". " << time[movieID - 1][i] << endl;
                }
                cout << "Enter showtime ID to book (1-5): ";
                cin >> showtimeID;
                // Validate showtimeID input
                if (cin.fail() || showtimeID < 1 || showtimeID > 5) {
                    cout << "Invalid showtime ID! Try again.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    break;
                }
                cout << "Enter seat number: ";
                cin >> seatNumber;
                // Validate seatNumber input
                if (cin.fail() || seatNumber < 1 || seatNumber > seatCount) {
                    cout << "Invalid seat number! Try again.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    break;
                }
                BookSeat(movieID, showtimeID, seatNumber);
                break;
            }
        case 4:
            {
                int movieID, showtimeID, seatNumber;
                cout << "Enter movie ID to cancel booking: ";
                cin >> movieID;
                // Validate movieID input
                if (cin.fail() || movieID < 1 || movieID > movieCount) {
                    cout << "Invalid movie ID! Try again.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    break;
                }
                cout << "Enter showtime ID to cancel booking (1-5): ";
                cin >> showtimeID;
                // Validate showtimeID input
                if (cin.fail() || showtimeID < 1 || showtimeID > 5) {
                    cout << "Invalid showtime ID! Try again.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    break;
                }
                cout << "Enter seat number to cancel: ";
                cin >> seatNumber;
                // Validate seatNumber input
                if (cin.fail() || seatNumber < 1 || seatNumber > seatCount) {
                    cout << "Invalid seat number! Try again.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    break;
                }
                CancelBooking(movieID, showtimeID, seatNumber);
                break;
            }
        case 5:
            {
                int movieID;
                string name;
                cout << "Enter movie ID to add to waiting list: ";
                cin >> movieID;
                // Validate movieID input
                if (cin.fail() || movieID < 1 || movieID > movieCount) {
                    cout << "Invalid movie ID! Try again.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    break;
                }
                cin.ignore(); // clear newline character from buffer
                cout << "Enter name: ";
                getline(cin, name);
                AddToWaitingList(movieID, name);
                break;
            }
        case 6:
            {
                int movieID;
                cout << "Enter movie ID to process waiting list: ";
                cin >> movieID;
                // Validate movieID input
                if (cin.fail() || movieID < 1 || movieID > movieCount) {
                    cout << "Invalid movie ID! Try again.\n";
                    cin.clear(); // Clear error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    break;
                }
                ProcessWaitingList(movieID);
                break;
            }
        case 7:
            ProceedToPayment();
            break;
        case 8:
            SortMovies();
            break;
        case 9:
            cout << "Exiting the system.\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
            break;
        }

    } while (choice != 9);
}