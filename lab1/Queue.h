//
// Created by Artem Zhitomirskiy on 02.10.2026.
//

#ifndef LAB1_QUEUE_H
#define LAB1_QUEUE_H

class Queue {
private:
    struct Node {
        int data;
        Node *prev;
        explicit Node(const int d) : data(d), prev(nullptr) {}
    };
    Node *head_;
    Node *tail_;
    int size_;

    // обмен содержимым двух очередей
    void swap(Queue &other);
    // записывает элементы от начала к концу в массив out
    void fillArray(int *out) const;
    // добавляет в конец копии всех элементов другой очереди
    void appendAll(const Queue &other);

protected:
    // возвращает элемент по номеру от начала очереди (с нуля)
    int elementAt(int index) const;
    // возвращает среднее арифметическое элементов
    double average() const;

public:
    // создаёт пустую очередь
    Queue() : head_(nullptr), tail_(nullptr), size_(0) {}
    // конструктор копирования
    Queue(const Queue &other);
    // присваивание через обмен с копией
    Queue &operator=(Queue other) {
        swap(other);
        return *this;
    }
    // деструктор, освобождает память
    ~Queue() { clear(); }

    // добавляет элемент в конец очереди
    void push(int value);
    // извлекает элемент из начала очереди и возвращает его
    int pop();
    // удаляет все элементы
    void clear();
    // выводит очередь на экран
    void print() const;

    // возвращает новую очередь с копиями элементов
    Queue copy() const;
    // возвращает очередь из элементов a, затем элементов b
    static Queue merge(const Queue &a, const Queue &b);

    // проверяет, пуста ли очередь
    bool isEmpty() const { return head_ == nullptr; }
    // возвращает число элементов
    int getSize() const { return size_; }
};

#endif
