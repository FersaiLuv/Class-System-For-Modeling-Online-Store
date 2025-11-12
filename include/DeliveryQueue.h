#pragma once
// Заголовочный файл класса DeliveryQueue
#ifndef DELIVERY_QUEUE_H
#define DELIVERY_QUEUE_H

#define MAX_ORDERS 1000 // Макс. кол-во заказов в очереди

#include "Order.h" // Заказ
#include "SortStrategy.h"  // Известные стратегии

// Структура с неким блоком заказа. Каждый блок хранит сам заказ и указатель на следующий в очереде
struct QueueNode {
    Order* order;
    QueueNode* next;
    QueueNode(Order* ord); // Конструктор блока
};

// Класс Очередь
class DeliveryQueue {
private:
    QueueNode* head; // Указатель на  блок заказа в очереди
    QueueNode* tail; // Указатель на последний блок заказа в очереди 
    unsigned int order_count; // Счётчик заказов

public:
    DeliveryQueue(); // Конструктор без параметров

    // Основные методы
    void addOrder(Order* order); // добавить заказ
    Order* getNextOrder(); // Взять заказ
    void show_all_orders(); // Показать все заказы

    // Методы для стратегий
    void getOrdersForSorting(Order* orders[], unsigned int& count); // Отдать заказы из очереди на сортировку (в массив)
    void updateQueueAfterSorting(Order* orders[], unsigned int count); // Взять отсортированные заказы
    void applyStrategy(SortStrategy* strategy); // Установить и применить стратегию сортировки

    ~DeliveryQueue(); // Деструктор 
};

#endif