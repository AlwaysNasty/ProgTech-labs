#ifndef LAB1_QUEUEPROTECTED_H
#define LAB1_QUEUEPROTECTED_H

#include "Queue.h"

class QueueProtected : protected Queue {
private:
    // создаёт наследника из объекта базового класса
    explicit QueueProtected(const Queue &base) : Queue(base) {}

public:
    // создаёт пустую очередь
    QueueProtected() {}

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
    QueueProtected copy() const { return QueueProtected(Queue::copy()); }
    // возвращает слияние двух очередей
    static QueueProtected merge(const QueueProtected &a, const QueueProtected &b) {
        return QueueProtected(Queue::merge(a, b));
    }
};

#endif
