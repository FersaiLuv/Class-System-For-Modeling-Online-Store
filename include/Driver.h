#pragma once
// Заголовочный файл класса Driver
#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <iostream>
#include "DeliveryQueue.h" // Очередь
#include "Order.h" // Заказ

// Класс - водитель (экспедитор/доставщик)
class Driver {
private:
    std::string name; // Имя
    DeliveryQueue* delivery_queue; // Очередь заказов
    unsigned int delivered_orders; // Кол-во доставленных заказов (опционально)

public:
    Driver(std::string driver_name, DeliveryQueue* queue);

    std::string getName() const; // Получение имени
    bool deliverNextOrder(); // Доставка заказа
    void show_queue(); // Показать очередь заказов
};

#endif