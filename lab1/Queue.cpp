//
// Created by Artem Zhitomirskiy on 02.10.2026.
//

#include "Queue.h"

#include <stdexcept>

Queue::Queue() {
    head = nullptr;
    tail = nullptr;
}

void Queue::clear() {
    while (head != nullptr) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

Queue::~Queue() {
    clear();
}

bool Queue::empty() const {
    return head == nullptr;
}

int Queue::front() {
    if (empty())
        throw std::underflow_error("Queue is empty!");
    return head->data;
}

void Queue::push(const int value) {
    Node *temp = new Node;
    temp->data = value;
    temp->next = nullptr;

    if (tail == nullptr) {
        head = temp;
        tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

void Queue::pop() {
    if (empty())
        throw std::underflow_error("Queue is empty!");

    Node *temp = head;
    head = head->next;
    delete temp;

    if (empty())
        tail = nullptr;
}