// Заголовочный файл родительского класса SortStrategy и его потомков
#ifndef SORT_STRATEGY_H
#define SORT_STRATEGY_H

#define MAX_ORDERS 1000 // Макс. кол-во заказов в очереди

// Чтобы избежать циклическую зависимость, нужно прописать объявление класса очереди, чтобы программа знала что он уже есть и с ним можно работать
// Класс очереди - это центральное звено, через которое проходят все заказы в программе, а стратегия сортировки сортирует эту очередь
class DeliveryQueue;

// Класс стратегии сортировки - родитель
class SortStrategy {
public:
    virtual void sortQueue(DeliveryQueue* queue) = 0; // Виртуальный метод - для потомков
    virtual ~SortStrategy() {} // Виртуальный диструктор - та же песня
};

// Потомок класса стратегии сортировки - класс сортировки по дате
class DateStrategy : public SortStrategy {
public:
    void sortQueue(DeliveryQueue* queue) override; // Явно указываем, что переопределяем функцию 
};

// Потомок класса стратегии сортировки - класс сортировки по расстоянию
class DistanceStrategy : public SortStrategy {
public:
    void sortQueue(DeliveryQueue* queue) override; // Явно указываем, что переопределяем функцию 
};

#endif