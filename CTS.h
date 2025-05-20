#ifndef CTS_H
#define CTS_H
using namespace std;
#include "Queue.h"
#include <string>

class CTS {
public:
    CTS(int movieCount, int seatCount);
    ~CTS();
    void ShowMovies();
    void Display(int movieID, int showtimeID);
    void BookSeat(int movieID, int showtimeID, int seatNumber);
    void AddToWaitingList(int movieID, std::string personName);
    void ProcessWaitingList(int movieID);
    void ProceedToPayment();
    void SortMovies();
    void Menu();
    void CancelBooking(int movieID, int showtimeID, int seatNumber);

private:
    int movieCount;
    int seatCount;
    string *movies;
    string **time;
    string *hall;
    double *prices;
    string **foodAndBeverageOptions;
    int ***seats;
    double ***payments;
    bool ***bookingStatus;
    string ***foodChoices;
    double **movieCharges;
    double **foodCharges;
    Queue *waitingLists;
};

#endif // CTS_H