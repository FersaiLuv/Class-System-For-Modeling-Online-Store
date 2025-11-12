#pragma once
// Заголовочный файл класса Order
#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <iostream>

// Подключение классов
#include "Product.h"
#include "Client.h"

class Order {
private:
    unsigned int id; // Id заказа
    // Ссылки (на товар, на клиента)
    Product* product;
    Client* client;
    // Дата заказа (DD.MM.YYYY)
    unsigned int day;
    unsigned int month;
    unsigned int year;
    std::string status; // Статус заказа
    bool is_finish; // Флаг "завершённости" заказа

public:
    Order(unsigned int o_id, Product* o_product, Client* o_client, unsigned int o_day, unsigned int o_month, unsigned int o_year);

    // Геттеры
    unsigned int getId() const;
    Client* getClient() const;
    Product* getProduct() const;
    std::string getDate() const;
    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;
    unsigned int getDateAsNumber() const;
    std::string getStatus() const;
    bool getIsFinish() const;
    double getDistance() const;

    // Сеттеры
    void setStatus(std::string new_status);
    void markCompleted();

    // Вывод информации о заказе
    void show_info();
};

#endif