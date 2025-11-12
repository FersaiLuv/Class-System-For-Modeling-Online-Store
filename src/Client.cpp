// Определение класса Client
#include "Client.h"

Client::Client(unsigned int c_id, std::string c_name, std::string c_address, double c_distance) :
    id(c_id), name(c_name), address(c_address), distance(c_distance) {
}

// Геттеры
int Client::getId() const { return id; }
std::string Client::getName() const { return name; }
std::string Client::getAddress() const { return address; }
double Client::getDistance() const { return distance; }

// Метод вывода информации о клиенте
void Client::show_info()
{
    std::cout << "Клиент: " << name << " (ID: " << id << ")" << std::endl;
    std::cout << "Адрес: " << address << std::endl;
    std::cout << "Расстояние от склада: " << distance << " км" << std::endl;
}