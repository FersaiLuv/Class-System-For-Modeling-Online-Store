// Реализаия класса WarehouseWorker
#include "WarehouseWorker.h"

// Класс - кладовщик
WarehouseWorker::WarehouseWorker(std::string worker_name, Warehouse* wh) :
    name(worker_name), warehouse(wh) {
}

std::string WarehouseWorker::getName() const { return name; } // Получение имени

bool WarehouseWorker::releaseProduct(Order* order) // Отпустить товар со склада (на заказ) 
{
    Product* product = order->getProduct();

    if (warehouse->reduceCountProducts(product->getId(), 1)) {
        std::cout << "Кладовщик (" << name << ") отпустил товар для заказа №" << order->getId() << std::endl;
        order->setStatus("Готов к доставке");
        return true;
    }
    else {
        std::cout << "Ошибка: товар отсутствует на складе!" << std::endl;
        return false;
    }
}

void WarehouseWorker::receiveProduct(Product* product, int quantity) // Принять товар на склад
{
    // Поиск, есть ли такой товар уже на складе
    Product* existing_product = warehouse->findProduct(product->getId());

    if (existing_product) {
        // Товар есть - увеличиваем количество
        existing_product->setCount(existing_product->getCount() + quantity);
    }
    else {
        // Товара нет - добавляем новый
        product->setCount(quantity);
        warehouse->addProduct(product);
    }

    std::cout << "Кладовщик " << name << " принял " << quantity << " шт. товара на склад" << std::endl;
}