// Определние класса Warehouse
#include "Warehouse.h"

Warehouse::Warehouse(std::string w_address) : address(w_address), product_count(0) {
    // Начальная инициализация нулями в конструкторе 
    for (int i = 0; i < MAX_PRODUCTS; i++) {
        products[i] = nullptr;
    }
}

// Геттеры
std::string Warehouse::getLocation() const { return address; }
unsigned int Warehouse::getProductCount() const { return product_count; }

// Методы
int Warehouse::addProduct(Product* product) // Добавление товара
{
    if (product_count >= MAX_PRODUCTS) {
        std::cout << "Ошибка: склад переполнен" << std::endl;
        return -1;
    }

    products[product_count] = product;
    product_count++;
    return 1;
}

bool Warehouse::checkProduct(unsigned int p_id) // Косвенная проверка наличия товара на складе
{
    for (int i = 0; i < product_count; i++) {
        if (products[i]->getId() == p_id) {
            //std::cout << "Товар " << products[i]->getName() << " есть в наличи!" << std::endl;
            //std::cout << "Кол-во на складе: " << products[i]->getCount() << std::endl;
            return true;
        }
    }
    std::cout << "Товар отсутствует на складе" << std::endl;
    return false;
}

// Реализация продажи товаров (вычитка кол-ва из склада) 
// 1) Найти товар по ID
Product* Warehouse::findProduct(unsigned int p_id) // Поиск товара на складе по ID 
{
    for (int i = 0; i < product_count; i++) {

        if (products[i]->getId() == p_id) {
            //std::cout << "Товар (" << products[i]->getId() << ") найден" << std::endl;
            return products[i];
        }
    }

    std::cout << "Товар не найден" << std::endl;
    return nullptr;
}

// 2) Уменьшение кол-ва товара из склада (для вычитки из склада)
bool Warehouse::reduceCountProducts(unsigned int p_id, unsigned int count)
{
    Product* product = findProduct(p_id); // Находим товар
    // Проверяем нашли ли товар и достаточно ли его
    if (product && product->getCount() >= count) {
        product->setCount(product->getCount() - count);
        return true;
    }

    return false;
}

void Warehouse::show_all_products() // Вывод все хтоваров на складе
{
    std::cout << "=== ТОВАРЫ НА СКЛАДЕ (" << product_count << " шт.) ===" << std::endl;
    for (int i = 0; i < product_count; i++) {
        products[i]->show_info();
        std::cout << "---" << std::endl;
    }
}