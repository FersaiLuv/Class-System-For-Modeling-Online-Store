#pragma once
// Заголовочный файл класса Client
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>

class Client {
private:
    unsigned int id; // Id клиента
    std::string name; // Имя клиента
    std::string address; // Адрес 
    double distance; // Расстояние от склада до клиента

public:
    Client(unsigned int c_id, std::string c_name, std::string c_address, double c_distance);

    // Геттеры
    int getId() const;
    std::string getName() const;
    std::string getAddress() const;
    double getDistance() const;

    // Метод вывода информации о клиенте
    void show_info();
};

#endif