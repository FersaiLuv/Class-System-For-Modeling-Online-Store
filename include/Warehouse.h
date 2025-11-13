#pragma once
// Заголовочный файл класса Warehouse
#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#define MAX_PRODUCTS 200 // Максимальное кол-во разных товаров (видов/наименований)

#include <iostream>
#include "Product.h" // Продукт

// Класс Склад
class Warehouse {
private:
    Product* products[MAX_PRODUCTS]; // Массив указателей на товары
    unsigned int product_count; // Общее кол-во товаров на складе
    std::string address; // Расположение склада (адрес)

public:
    Warehouse(std::string w_address);

    // Геттеры
    std::string getLocation() const;
    unsigned int getProductCount() const;

    // Методы
    int addProduct(Product* product); // Добавление товара
    bool checkProduct(unsigned int p_id); // Косвенная проверка наличия товара на складе
    Product* findProduct(unsigned int p_id); // Поиск товара на складе по ID (для вычитки из склада)
    bool reduceCountProducts(unsigned int p_id, unsigned int count); // Уменьшение кол-ва товара из склада (для вычитки из склада)
    void show_all_products(); // Вывод все хтоваров на складе
};

#endif