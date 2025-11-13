#pragma once
// Заголовочный файл класса Manager
#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <iostream>
#include "Warehouse.h" // Склад
#include "Order.h" // Заказ
#include "DeliveryQueue.h" // Очередь

// Менеджер
class Manager {
private:
    std::string name; // Имя 
    Warehouse* warehouse; // Склад, с которым связан менеджер
    DeliveryQueue* delivery_queue; // Связь с очередью

public:
    Manager(std::string m_name, Warehouse* wh, DeliveryQueue* d_queue);

    std::string getName() const; // Получение имени
    bool processOrder(Order* order); // Обработка заказа от клиента
};

#endif