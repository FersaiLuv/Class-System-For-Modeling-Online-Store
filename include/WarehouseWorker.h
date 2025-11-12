#pragma once
// Заголовочный файл класса WarehouseWorker (Кладовщик)
#ifndef WAREHOUSE_WORKER_H
#define WAREHOUSE_WORKER_H

#include <string>
#include <iostream>
#include "Warehouse.h" // Склад
#include "Order.h" // Заказ

// Класс - кладовщик
class WarehouseWorker {
private:
    std::string name; // Имя 
    Warehouse* warehouse; // Связанный склад

public:
    WarehouseWorker(std::string worker_name, Warehouse* wh);

    std::string getName() const; // Получение имени
    bool releaseProduct(Order* order); // Отпустить товар со склада (на заказ) 
    void receiveProduct(Product* product, int quantity); // Принять товар на склад
};

#endif