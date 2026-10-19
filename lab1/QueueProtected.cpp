#include "QueueProtected.h"
#include <iostream>

// идёт от конца очереди к началу, первый элемент меньше среднего и есть искомый
bool QueueProtected::findLastBelowAverage(int &result) const {
    if (isEmpty()) return false;
    const double avg = average();

    for (int i = getSize() - 1; i >= 0; --i) {
        const int value = elementAt(i);
        if (value < avg) {
            result = value;
            return true;
        }
    }
    return false;
}

// выводит среднее арифметическое и результат поиска
void QueueProtected::showLastBelowAverage() const {
    if (isEmpty()) {
        std::cout << "Очередь пуста, расчёт невозможен.\n";
        return;
    }
    std::cout << "Среднее арифметическое: " << average() << "\n";
    int result;
    if (findLastBelowAverage(result))
        std::cout << "Последний элемент, меньший среднего: " << result << "\n";
    else
        std::cout << "Элементов, меньших среднего арифметического, нет.\n";
}
