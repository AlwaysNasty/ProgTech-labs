//
// Created by Artem Zhitomirskiy on 02.10.2026.
//

#include "Queue.h"
#include <stdexcept>

void Queue::swap(Queue& other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

void Queue::push(const int value) {
    Node *node = new Node(value);
    if (tail_ == nullptr) head_ = node;
    else tail_->next = node;
    tail_ = node;
    ++size_;
}

int Queue::pop() {
    if (isEmpty())
        throw std::underflow_error("Queue is empty!");

    Node *old = head_;
    int value = old->data;
    head_ = head_->next;

    if (head_ == nullptr)
        tail_ = nullptr;

    delete old;
    --size_;
    return value;
}

void Queue::clear() {
    while (head_ != nullptr) {
        Node* next = head_->next;
        delete head_;
        head_ = next;
    }
    tail_ = nullptr;
    size_ = 0;
}