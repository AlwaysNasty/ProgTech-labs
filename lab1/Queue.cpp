//
// Created by Artem Zhitomirskiy on 02.10.2026.
//

#include "Queue.h"
#include <iostream>
#include <stdexcept>
#include <utility>

// копирует все элементы другой очереди в новую
Queue::Queue(const Queue &other) : head_(nullptr), tail_(nullptr), size_(0) {
    appendAll(other);
}

// меняет местами указатели и размер двух очередей
void Queue::swap(Queue &other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

// создаёт элемент и связывает его с прежним концом очереди
void Queue::push(const int value) {
    Node *node = new Node(value);
    node->prev = tail_;
    if (tail_ == nullptr) head_ = node;
    tail_ = node;
    ++size_;
}

// удаляет первый элемент; новое начало ищется от конца по ссылкам prev
int Queue::pop() {
    if (isEmpty())
        throw std::underflow_error("Очередь пуста!");

    Node *old = head_;
    int value = old->data;

    if (head_ == tail_) {
        head_ = tail_ = nullptr;
    } else {
        Node *n = tail_;
        while (n->prev != old) n = n->prev;
        n->prev = nullptr;
        head_ = n;
    }

    delete old;
    --size_;
    return value;
}

// удаляет элементы от конца к началу
void Queue::clear() {
    while (tail_ != nullptr) {
        Node *prev = tail_->prev;
        delete tail_;
        tail_ = prev;
    }
    head_ = nullptr;
    size_ = 0;
}

// обходит очередь от конца к началу и заполняет массив с конца
void Queue::fillArray(int *out) const {
    int i = size_;
    for (Node *n = tail_; n != nullptr; n = n->prev)
        out[--i] = n->data;
}

// сначала копирует значения во временный массив, затем добавляет их в конец
void Queue::appendAll(const Queue &other) {
    int *buf = new int[other.size_];
    other.fillArray(buf);
    const int n = other.size_;
    try {
        for (int i = 0; i < n; ++i) push(buf[i]);
    } catch (...) {
        delete[] buf;
        throw;
    }
    delete[] buf;
}

// печатает элементы от начала к концу
void Queue::print() const {
    if (isEmpty()) {
        std::cout << "(очередь пуста)\n";
        return;
    }
    int *buf = new int[size_];
    fillArray(buf);
    std::cout << "[начало] ";
    for (int i = 0; i < size_; ++i) std::cout << buf[i] << ' ';
    std::cout << "[конец]\n";
    delete[] buf;
}

// идёт от конца очереди назад до нужного номера
int Queue::elementAt(const int index) const {
    if (index < 0 || index >= size_)
        throw std::out_of_range("Неверный номер элемента очереди");
    Node *n = tail_;
    for (int steps = size_ - 1 - index; steps > 0; --steps) n = n->prev;
    return n->data;
}

// суммирует элементы и делит на их количество
double Queue::average() const {
    if (isEmpty()) return 0.0;
    double sum = 0;
    for (Node *n = tail_; n != nullptr; n = n->prev) sum += n->data;
    return sum / size_;
}

// создаёт копию через конструктор копирования
Queue Queue::copy() const {
    return Queue(*this);
}

// копия a, к которой дописаны элементы b
Queue Queue::merge(const Queue &a, const Queue &b) {
    Queue result(a);
    result.appendAll(b);
    return result;
}
