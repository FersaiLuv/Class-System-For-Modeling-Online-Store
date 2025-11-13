// Определение класса Manager
#include "Manager.h"

Manager::Manager(std::string m_name, Warehouse* wh, DeliveryQueue* d_queue) :
    name(m_name), warehouse(wh), delivery_queue(d_queue) {
}

std::string Manager::getName() const { return name; } // Получение имени

bool Manager::processOrder(Order* order) // Обработка заказа от клиента
{
    std::cout << "Менеджер " << "(" << name << ")" << " обрабатывает заказ №" << order->getId() << std::endl;
    Product* product = order->getProduct();

    if (warehouse->checkProduct(product->getId())) {
        order->setStatus("Принят");
        std::cout << "Товар есть на складе. Заказ принят!" << std::endl;
        delivery_queue->addOrder(order);
        return true;
    }
    else {
        order->setStatus("ожидает поставки");
        std::cout << "Товара нет на складе. Передано в отдел снабжения." << std::endl;
        return false;
    }
}