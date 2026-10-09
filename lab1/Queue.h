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
        explicit Node(int d) : data(d), next(nullptr) {}
    };
    Node *head_;
    Node *tail_;
    int size_;

public:
    Queue(): head_(nullptr), tail_(nullptr), size_(0) {}

    Queue(const Queue& other) : head_(nullptr), tail_(nullptr), size_(0) {
        for (Node* curr = other.head_; curr != other.tail_; curr = curr->next)
            push(curr->data);
    }

    Queue& operator=(Queue other) {
        swap(other);
        return *this;
    }

    ~Queue() { clear(); }

    void push(int value);
    int pop();

    //вспомогательные методы
    void clear();
    void swap(Queue &other);

    bool isEmpty() const { return head_ == nullptr; }
    int getSize() const { return size_; }

};


#endif //LAB1_QUEUE_H
