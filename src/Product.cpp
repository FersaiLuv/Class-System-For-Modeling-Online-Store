// Определение класса Product
#include "product.h"

Product::Product(unsigned int p_id, std::string p_name, double p_price, unsigned int p_count) : // Конструктор
	id(p_id), name(p_name), price(p_price), count(p_count) {
}

// Геттеры
unsigned int Product::getId() const { return id; }
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
unsigned int Product::getCount() const { return count; }

// Сеттер
void Product::setCount(unsigned int new_count) {
	count = new_count;
}

// Метод вывода информации о товаре
void Product::show_info() {
	std::cout << "Товар: " << name << " (ID: " << id << ")" << std::endl;
	std::cout << "Цена: " << price << " руб." << std::endl;
	std::cout << "На складе: " << count << " шт." << std::endl;
}