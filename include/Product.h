#pragma once
// Заголовочный файл класса Product
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

class Product {
private:
	unsigned int id; // Id товара
	std::string name; // Название
	double price; // Цена
	unsigned int count; // Кол-во на складе

public:
	Product(unsigned int p_id, std::string p_name, double p_price, unsigned int p_count); // Конструктор

	// Геттеры
	unsigned int getId() const;
	std::string getName() const;
	double getPrice() const;
	unsigned int getCount() const;

	// Сеттер
	void setCount(unsigned int new_count);

	// Метод вывода информации о товаре
	void show_info();
};

#endif