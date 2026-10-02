//
// Created by Artem Zhitomirskiy on 02.10.2026.
//

#ifndef LAB1_QUEUE_H
#define LAB1_QUEUE_H

class Queue {
private:
    struct Node {
        int data;
        Node *next;
    };
    Node *head;
    Node *tail;

public:
    Queue();
    ~Queue();

    void clear();
    int front();
    bool empty() const;

    void push(int value);
    void pop();


};


#endif //LAB1_QUEUE_H
