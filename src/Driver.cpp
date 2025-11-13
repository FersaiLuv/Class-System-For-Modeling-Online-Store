// Определение класса Driver

#include "Driver.h"

Driver::Driver(std::string driver_name, DeliveryQueue* queue) :
    name(driver_name), delivery_queue(queue), delivered_orders(0) {
}

std::string Driver::getName() const { return name; } // Получение имени

bool Driver::deliverNextOrder() // Доставка заказа
{
    Order* order = delivery_queue->getNextOrder(); // Берем заказ из очереди

    if (order != nullptr) {
        std::cout << "Водитель (" << name << ") доставляет заказ №" << order->getId() << std::endl;
        order->markCompleted();
        std::cout << "Заказ №" << order->getId() << " доставлен!" << std::endl;
        return true;
    }
    else {
        std::cout << "Нет заказов для доставки" << std::endl;
        return false;
    }
}

void Driver::show_queue() // Показать очередь заказов
{
    delivery_queue->show_all_orders();
}