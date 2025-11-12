// Определение класса Order
#include "Order.h"

Order::Order(unsigned int o_id, Product* o_product, Client* o_client, unsigned int o_day, unsigned int o_month, unsigned int o_year) :
    id(o_id), product(o_product), client(o_client), day(o_day), month(o_month), year(o_year), status("Новый"), is_finish(false) {
}

// Геттеры
unsigned int Order::getId() const { return id; }
Client* Order::getClient() const { return client; }
Product* Order::getProduct() const { return  product; }

// Метод вывода даты (в формате строки DD.MM.YYYY)
std::string Order::getDate() const
{
    // Преобразование даты в строку через функцию-метод to_string()
    std::string dayStr = (day < 10) ? "0" + std::to_string(day) : std::to_string(day);
    std::string monthStr = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);

    return dayStr + "." + monthStr + "." + std::to_string(year);
}
unsigned int Order::getDay() const { return day; }
unsigned int Order::getMonth() const { return month; }
unsigned int Order::getYear() const { return  year; }

// Метод преобразования даты в число
unsigned int Order::getDateAsNumber() const
{
    return year * 10000 + month * 100 + day; // Преобразование даты в число (чтобы сравнивать даты для сортировки) 
}
std::string Order::getStatus() const { return status; }
bool Order::getIsFinish() const { return is_finish; }
double Order::getDistance() const { return client->getDistance(); }

// Сеттеры
void Order::setStatus(std::string new_status) { status = new_status; }
void Order::markCompleted()
{
    is_finish = true;
    status = "Доставлен";
}

// Вывод информации о заказе
void Order::show_info() {
    std::cout << "=== Заказ №" << id << " ===" << std::endl;
    std::cout << "Дата: " << getDate() << std::endl;
    std::cout << "Статус: " << status << std::endl;
    std::cout << "Завершен: " << (is_finish ? "да" : "нет") << std::endl;
    client->show_info();
    product->show_info();
}
