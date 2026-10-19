#include <iostream>
#include <limits>
#include <stdexcept>
#include "QueuePublic.h"
#include "QueueProtected.h"
#include "QueuePrivate.h"

// читает целое число, повторяя запрос при неверном вводе
static int readInt(const char *prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) return value;
        if (std::cin.eof()) throw std::runtime_error("Ввод завершён");
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Нужно ввести целое число.\n";
    }
}

// запрашивает количество элементов (не меньше нуля)
static int readCount() {
    int n;
    do {
        n = readInt("Сколько элементов ввести: ");
    } while (n < 0);
    return n;
}

// выводит пункты меню
static void printMenu() {
    std::cout << "\n1 - Добавление элемента\n"
                 "2 - Извлечение элемента\n"
                 "3 - Вывод очереди на экран\n"
                 "4 - Вывести последний элемент, меньший среднего арифметического\n"
                 "5 - Создание копии очереди\n"
                 "6 - Слияние очереди с копией\n"
                 "7 - Выход из программы\n";
}

// меню для очереди-наследника QueuePublic
static void runQueuePublic() {
    QueuePublic queue;
    QueuePublic savedCopy;
    bool hasCopy = false;
    while (true) {
        printMenu();
        int choice = readInt("Ваш выбор: ");
        switch (choice) {
            case 1:
                queue.push(readInt("Значение: "));
                break;
            case 2:
                if (queue.isEmpty()) std::cout << "Очередь пуста!\n";
                else std::cout << "Извлечён элемент: " << queue.pop() << "\n";
                break;
            case 3:
                queue.print();
                break;
            case 4:
                queue.showLastBelowAverage();
                break;
            case 5:
                savedCopy = queue.copy();
                hasCopy = true;
                std::cout << "Исходная очередь: ";
                queue.print();
                std::cout << "Копия сохранена:  ";
                savedCopy.print();
                break;
            case 6: {
                QueuePublic second;
                if (hasCopy) {
                    second = savedCopy;
                    std::cout << "Сливаем текущую очередь с сохранённой копией.\n";
                } else {
                    std::cout << "Копии нет (пункт 5), заполните вторую очередь.\n";
                    int n = readCount();
                    for (int i = 1; i <= n; ++i) {
                        std::cout << "Элемент " << i << ": ";
                        second.push(readInt(""));
                    }
                }
                QueuePublic merged = QueuePublic::merge(queue, second);
                std::cout << "Первая:    ";
                queue.print();
                std::cout << "Вторая:    ";
                second.print();
                std::cout << "Результат: ";
                merged.print();
                break;
            }
            case 7:
                return;
            default:
                std::cout << "Нет такого пункта меню.\n";
        }
    }
}

// меню для очереди-наследника QueueProtected
static void runQueueProtected() {
    QueueProtected queue;
    QueueProtected savedCopy;
    bool hasCopy = false;
    while (true) {
        printMenu();
        int choice = readInt("Ваш выбор: ");
        switch (choice) {
            case 1:
                queue.push(readInt("Значение: "));
                break;
            case 2:
                if (queue.isEmpty()) std::cout << "Очередь пуста!\n";
                else std::cout << "Извлечён элемент: " << queue.pop() << "\n";
                break;
            case 3:
                queue.print();
                break;
            case 4:
                queue.showLastBelowAverage();
                break;
            case 5:
                savedCopy = queue.copy();
                hasCopy = true;
                std::cout << "Исходная очередь: ";
                queue.print();
                std::cout << "Копия сохранена:  ";
                savedCopy.print();
                break;
            case 6: {
                QueueProtected second;
                if (hasCopy) {
                    second = savedCopy;
                    std::cout << "Сливаем текущую очередь с сохранённой копией.\n";
                } else {
                    std::cout << "Копии нет (пункт 5), заполните вторую очередь.\n";
                    int n = readCount();
                    for (int i = 1; i <= n; ++i) {
                        std::cout << "Элемент " << i << ": ";
                        second.push(readInt(""));
                    }
                }
                QueueProtected merged = QueueProtected::merge(queue, second);
                std::cout << "Первая:    ";
                queue.print();
                std::cout << "Вторая:    ";
                second.print();
                std::cout << "Результат: ";
                merged.print();
                break;
            }
            case 7:
                return;
            default:
                std::cout << "Нет такого пункта меню.\n";
        }
    }
}

// меню для очереди-наследника QueuePrivate
static void runQueuePrivate() {
    QueuePrivate queue;
    QueuePrivate savedCopy;
    bool hasCopy = false;
    while (true) {
        printMenu();
        int choice = readInt("Ваш выбор: ");
        switch (choice) {
            case 1:
                queue.push(readInt("Значение: "));
                break;
            case 2:
                if (queue.isEmpty()) std::cout << "Очередь пуста!\n";
                else std::cout << "Извлечён элемент: " << queue.pop() << "\n";
                break;
            case 3:
                queue.print();
                break;
            case 4:
                queue.showLastBelowAverage();
                break;
            case 5:
                savedCopy = queue.copy();
                hasCopy = true;
                std::cout << "Исходная очередь: ";
                queue.print();
                std::cout << "Копия сохранена:  ";
                savedCopy.print();
                break;
            case 6: {
                QueuePrivate second;
                if (hasCopy) {
                    second = savedCopy;
                    std::cout << "Сливаем текущую очередь с сохранённой копией.\n";
                } else {
                    std::cout << "Копии нет (пункт 5), заполните вторую очередь.\n";
                    int n = readCount();
                    for (int i = 1; i <= n; ++i) {
                        std::cout << "Элемент " << i << ": ";
                        second.push(readInt(""));
                    }
                }
                QueuePrivate merged = QueuePrivate::merge(queue, second);
                std::cout << "Первая:    ";
                queue.print();
                std::cout << "Вторая:    ";
                second.print();
                std::cout << "Результат: ";
                merged.print();
                break;
            }
            case 7:
                return;
            default:
                std::cout << "Нет такого пункта меню.\n";
        }
    }
}

// выбор типа наследника и запуск меню для него
int main() {
    try {
        std::cout << "С каким наследником работать?\n"
                     "1 - public\n"
                     "2 - protected\n"
                     "3 - private\n";
        switch (readInt("Ваш выбор: ")) {
            case 1: runQueuePublic(); break;
            case 2: runQueueProtected(); break;
            case 3: runQueuePrivate(); break;
            default: std::cout << "Нет такого варианта.\n";
        }
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
