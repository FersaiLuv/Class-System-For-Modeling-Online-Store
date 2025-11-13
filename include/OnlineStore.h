#pragma once
// Заголовочный файл главного класса OnlineStore
#ifndef ONLINE_STORE_H
#define ONLINE_STORE_H

#define MAX_ORDERS 1000
#define MAX_PRODUCTS 200

#include <string>
#include <iostream>
#include "Warehouse.h" // Склад
#include "DeliveryQueue.h" // Очередь
#include "Manager.h" // Менеджер
#include "WarehouseWorker.h" // Кладовщик
#include "Driver.h" // Водитель 
#include "SortStrategy.h" // Стратегия сортировки 

// Класс - онлайн магазин (управляющий класс)
class OnlineStore {
private:
    Warehouse* warehouse;
    DeliveryQueue* delivery_queue;
    Manager* manager;
    WarehouseWorker* worker;
    Driver* driver;
    SortStrategy* current_strategy; // текущая стратегия сортировки очереди

public:
    OnlineStore(std::string warehouse_address); // Адрес магазина (склада) в параметрах конструктора 

    void applySortingStrategy(SortStrategy* strategy); // Установка и применение стратегии
    void addProductToWarehouse(Product* product, unsigned int initial_quantity); // Добавить товар на склад
    void processNewOrder(unsigned int order_id, Product* product, Client* client, unsigned int day, unsigned int month, unsigned int year); // Создать и обработать заказ
    void deliverOrders(unsigned int orders_count); // Доставить несколько заказов
    void showDeliveryQueue(); // Показать текущую очередь доставки
    void showWarehouseStatus(); // Показать остатки на складе
    void exportActiveOrdersInRadius(double radius_km, const std::string& filename); // Выгрузка данных в файл

    ~OnlineStore(); // Деструктор
};

#endif