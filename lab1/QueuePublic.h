#ifndef LAB1_QUEUEPUBLIC_H
#define LAB1_QUEUEPUBLIC_H

#include "Queue.h"

class QueuePublic : public Queue {
private:
    // создаёт наследника из объекта базового класса
    explicit QueuePublic(const Queue &base) : Queue(base) {}

public:
    // создаёт пустую очередь
    QueuePublic() {}

    // ищет последний элемент, меньший среднего арифметического
    bool findLastBelowAverage(int &result) const;
    // выводит среднее и найденный элемент на экран
    void showLastBelowAverage() const;

    // возвращает копию очереди
    QueuePublic copy() const { return QueuePublic(Queue::copy()); }
    // возвращает слияние двух очередей
    static QueuePublic merge(const QueuePublic &a, const QueuePublic &b) {
        return QueuePublic(Queue::merge(a, b));
    }
};

#endif
