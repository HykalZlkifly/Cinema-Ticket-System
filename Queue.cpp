#include "Queue.h"
#include <iostream>
using namespace std;

Queue::Queue() {
    Array = new std::string[6];
    ArraySize = 6;
    Front = 0;
    Rear = ArraySize - 1;
    Count = 0;
}

Queue::Queue(int QueueSize) {
    Array = new std::string[QueueSize];
    ArraySize = QueueSize;
    Front = 0;
    Rear = ArraySize - 1;
    Count = 0;
}

Queue::~Queue() {
    delete[] Array;
    cout << "Queue destructed\n" << std::endl;
}

void Queue::Insert(std::string Value) {
    if (Count > ArraySize - 1) {
        cout << "Queue is Full!\n" << std::endl;
        return;
    }
    if (Rear == ArraySize - 1)
        Rear = 0;
    else
        Rear++;

    Array[Rear] = Value;
    Count = Count + 1;
}

string Queue::Remove() {
    if (Count == 0) {
        std::cout << "Queue underflow or empty\n" << std::endl;
        return "";
    }
    string Result = Array[Front];

    if (Front == ArraySize - 1)
        Front = 0;
    else
        Front++;
    Count--;
    return Result;
}

string Queue::First() {
    if (Count == 0) {
        cout << "Queue is empty\n" << std::endl;
        return "";
    }
    return Array[Front];
}

void Queue::Clear() {
    Front = 0;
    Rear = ArraySize - 1;
    Count = 0;
}

void Queue::Display() {
    for (int i = 0; i < ArraySize; i++)
        cout << Array[i] << endl;
}

int Queue::getCount() const {
    return Count;
}