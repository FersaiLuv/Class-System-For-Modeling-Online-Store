// Определение управляющего класса OnlineStore

#include <fstream>
#include "OnlineStore.h"


OnlineStore::OnlineStore(std::string warehouse_address)  // Адрес магазина (склада) в параметрах конструктора 
{
    std::cout << "СОЗДАНИЕ ОНЛАЙН-МАГАЗИНА" << std::endl;

    warehouse = new Warehouse(warehouse_address);
    delivery_queue = new DeliveryQueue();
    manager = new Manager("Евгений", warehouse, delivery_queue);
    worker = new WarehouseWorker("Анатолий", warehouse);
    driver = new Driver("Максим", delivery_queue);
    current_strategy = nullptr;

    std::cout << "Система готова к работе!" << std::endl;
}

// Установка и применение стратегии
void OnlineStore::applySortingStrategy(SortStrategy* strategy)
{
    current_strategy = strategy;
    if (current_strategy != nullptr) {
        delivery_queue->applyStrategy(current_strategy);
    }
}

// Добавить товар на склад
void OnlineStore::addProductToWarehouse(Product* product, unsigned int initial_quantity)
{
    std::cout << "ДОБАВЛЕНИЕ ТОВАРА НА СКЛАД:" << std::endl;
    std::cout << "Товар: " << product->getName() << std::endl;
    std::cout << "Количество: " << initial_quantity << " шт." << std::endl;

    product->setCount(initial_quantity);
    warehouse->addProduct(product);
}

// Создать и обработать заказ
void OnlineStore::processNewOrder(unsigned int order_id, Product* product, Client* client, unsigned int day, unsigned int month, unsigned int year)
{
    std::cout << "ОБРАБОТКА НОВОГО ЗАКАЗА №" << order_id << std::endl;

    // Создание заказ
    Order* order = new Order(order_id, product, client, day, month, year);
    // Обработка через менеджера
    if (manager->processOrder(order)) {
        worker->releaseProduct(order);
        std::cout << "Заказ №" << order_id << " готов к доставке!" << std::endl;
    }
    else {
        std::cout << "Заказ №" << order_id << " ожидает поставки товара" << std::endl;
    }
}

// Доставить несколько заказов
void OnlineStore::deliverOrders(unsigned int orders_count)
{
    std::cout << "ГОТОВИМ ДОСТАВКУ " << orders_count << " ЗАКАЗА(ОВ)" << std::endl;

    for (int i = 0; i < orders_count; i++) {
        std::cout << "--- Доставка " << (i + 1) << " ---" << std::endl;

        if (!driver->deliverNextOrder()) {
            std::cout << "Доставка прервана: заказы закончились" << std::endl;
            break;
        }
    }
}

// Показать текущую очередь доставки
void OnlineStore::showDeliveryQueue()
{
    std::cout << "ТЕКУЩАЯ ОЧЕРЕДЬ ДОСТАВКИ:" << std::endl;
    delivery_queue->show_all_orders();
}

// Показать остатки на складе
void OnlineStore::showWarehouseStatus()
{
    std::cout << "СОСТОЯНИЕ СКЛАДА:" << std::endl;
    warehouse->show_all_products();
}

// Обработка данных и выгрузка в файл
void OnlineStore::exportActiveOrdersInRadius(double radius_km, const std::string& filename)
{
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cout << "Ошибка: невозможно открыть файл " << filename << std::endl;
        return;
    }

    std::cout << "Сохранение активных заказов в радиусе " << radius_km << " км в файл: " << filename << std::endl;
    outFile << "СПИСОК АКТИВНЫХ ЗАКАЗОВ В РАДИУСЕ " << radius_km << " Км\n";
    outFile << "==========================================\n";
    outFile << "Название груза | Количество стеллажей\n";
    outFile << "------------------------------------------\n";

    // Создание временного массива для заказов
    Order* total_orders[MAX_ORDERS];
    unsigned int count_orders;
    delivery_queue->getOrdersForSorting(total_orders, count_orders); // Берем заказы из очереди

    struct ProductCount {
        std::string name;
        unsigned int count;
    };

    ProductCount product_stats[MAX_PRODUCTS];
    unsigned int stat_count = 0;

    for (int i = 0; i < count_orders; i++) {
        Order* order = total_orders[i];

        // првоерка, подходит ли заказ под условия
        if ((order->getStatus() == "Принят" || order->getStatus() == "Готов к доставке") && !order->getIsFinish()
            && order->getDistance() <= radius_km) {

            std::string product_name = order->getProduct()->getName();

            // Ищем товар заказа уже по собранной статистике склада
            bool is_found = false;
            for (int j = 0; j < stat_count; j++) { // наш stat_cout будет расти с каждой внешней итерацией цикла (на первой итерации всё по нулям)

                // Сравнение с существующими товарам (на первой итерации их нет, поэтому и цикла нет)
                if (product_stats[j].name == product_name) {
                    product_stats[j].count++; // Нашли - увеличили счетчик
                    is_found = true;
                    break;
                }
            }

            // На начальном этапе product_stats пустой, поэтому заполняем его элементами, которые не найдет врехний цикл
            if (!is_found && stat_count < MAX_PRODUCTS) {
                // Кол-во добавленного товара = 1
                product_stats[stat_count].name = product_name;
                product_stats[stat_count].count = 1;
                stat_count++; // Общий счётик товаров +1
            }
        }
    }

    // Записываем статистику в файл
    for (int i = 0; i < stat_count; i++) {
        outFile << product_stats[i].name << " | " << product_stats[i].count << "\n";
    }

    delivery_queue->updateQueueAfterSorting(total_orders, count_orders); // Восстанавливаем очередь
    outFile.close();

    std::cout << "Успешно сохранено " << stat_count << " товаров в " << filename << std::endl;

}

// Деструктор
OnlineStore::~OnlineStore()
{
    std::cout << "|--ЗАВЕРШЕНИЕ РАБОТЫ СИСТЕМЫ--|" << std::endl;

    delete driver;
    delete worker;
    delete manager;
    delete delivery_queue;
    delete warehouse;

    std::cout << "Память очищена, система завершила работу" << std::endl;
}

