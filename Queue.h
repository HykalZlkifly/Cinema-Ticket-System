#ifndef QUEUE_H
#define QUEUE_H
using namespace std;

#include <string>

class Queue {
public:
    Queue();
    Queue(int QueueSize);
    ~Queue();
    void Insert(std::string Value);
    string Remove();
    string First();
    void Clear();
    void Display();
    int getCount() const;

private:
    string *Array;
    int ArraySize;
    int Front;
    int Rear;
    int Count;
};

#endif // QUEUE_H