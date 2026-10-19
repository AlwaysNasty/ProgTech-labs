#ifndef LAB1_QUEUEPRIVATE_H
#define LAB1_QUEUEPRIVATE_H

#include "Queue.h"

class QueuePrivate : private Queue {
private:
    // создаёт наследника из объекта базового класса
    explicit QueuePrivate(const Queue &base) : Queue(base) {}

public:
    // создаёт пустую очередь
    QueuePrivate() {}

    // открываем унаследованные методы для использования снаружи
    using Queue::push;
    using Queue::pop;
    using Queue::clear;
    using Queue::print;
    using Queue::isEmpty;
    using Queue::getSize;

    // ищет последний элемент, меньший среднего арифметического
    bool findLastBelowAverage(int &result) const;
    // выводит среднее и найденный элемент на экран
    void showLastBelowAverage() const;

    // возвращает копию очереди
    QueuePrivate copy() const { return QueuePrivate(Queue::copy()); }
    // возвращает слияние двух очередей
    static QueuePrivate merge(const QueuePrivate &a, const QueuePrivate &b) {
        return QueuePrivate(Queue::merge(a, b));
    }
};

#endif
