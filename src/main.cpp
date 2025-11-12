/*
Объектно Ориентированное Программирование. КМПО РАНХиГС
Студент группы: 403ИС - 22 Петров Алексей
Решение предоставлено 11.11.2025
Преподаватель: Гусятинер Леонид Борисович
Задание 20.
1. Универсальный язык моделирования UML.Диаграмма классов

2. Спроектировать систему классов для моделирования онлайн магазина.«Компания по продаже товаров онлайн,
также производит доставку этих товаров по принципу очереди.Очередь на отправку формируется
по дате заказа и расстоянию от склада.Заявки с интернета попадают менеджеру.
Для имеющихся на складе товаров менеджер формирует заказ на склад, и заявку на машину для развоза.
Кладовщик отпускает товар экспедитору.Если товара на складе нет, менеджер по заявкам обращается в отдел снабжения, который,
в свою очередь, делает заказ поставщику.После поступления товара на склад кладовщик ставит его в базу.
После развоза делается пометка о выполнении заказа».Построить диаграмму классов

3. Разработать программу для демонстрации онлайн - магазина.Программа должна
выдавать в текстовый файл список заказов в работе, то есть принятых, но еще не
выполненных, от клиентов, находящихся в радиусе N км от склада(N – параметр).
Поведенческие паттерны проектирования.Стратегия(Strategy)
*/

// Демонстрация работы разработанной системы онлайн-магазина
#include <iostream>
#include <string>
#include "OnlineStore.h"
#include "SortStrategy.h"

int main() {
    setlocale(LC_ALL, "RU");

    std::cout << "==============================" << std::endl;
    std::cout << "ЗАПУСК СИСТЕМЫ ОНЛАЙН-МАГАЗИНА" << std::endl;
    std::cout << "==============================" << std::endl;

    // 1. СОЗДАЕМ МАГАЗИН
    OnlineStore store("Москва, ул. Складская, д. 15");

    // 2. ДОБАВЛЯЕМ ТОВАРЫ НА СКЛАД
    std::cout << "\nЗАГРУЗКА ТОВАРОВ НА СКЛАД:" << std::endl;
    std::cout << "----------------------------" << std::endl;

    Product laptop(1, "Ноутбук Lenovo", 75000, 0); // Ноутбук
    Product phone(2, "iPhone 15 Pro", 120000, 0); // Смартфон
    Product tablet(3, "iPad Air", 65000, 0); // Планшет
    Product headphones(4, "Наушники Sony", 25000, 0); // Наушники

    store.addProductToWarehouse(&laptop, 15);      // 15 ноутбуков
    store.addProductToWarehouse(&phone, 8);        // 8 айфонов
    store.addProductToWarehouse(&tablet, 12);      // 12 планшетов
    store.addProductToWarehouse(&headphones, 25);  // 25 наушников

    // 3. СОЗДАЕМ КЛИЕНТОВ (с РАЗНЫМИ расстояниями)
    std::cout << "\nРЕГИСТРАЦИЯ КЛИЕНТОВ:" << std::endl;
    std::cout << "-----------------------" << std::endl;

    Client client1(1, "Иван Божьев", "Москва, ул. Тверская, д. 10", 5.2);
    Client client2(2, "Оксана Спирина", "Москва, ул. Арбат, д. 25", 3.8);
    Client client3(3, "Сергей Белинский", "Химки, ул. Московская, д. 15", 18.5);
    Client client4(4, "Анна Смирнова", "Москва, ул. Пушкина, д. 8", 7.3);
    Client client5(5, "Дмитрий Рябов", "Подольск, ул. Ленина, д. 42", 32.7);
    Client client6(6, "Мария Новикова", "Москва, ул. Ленинградская, д. 33", 22.2);

    // 4. СОЗДАЕМ ЗАКАЗЫ (с РАЗНЫМИ датами)
    std::cout << "\nФОРМИРОВАНИЕ ЗАКАЗОВ:" << std::endl;
    std::cout << "-----------------------" << std::endl;

    // Заказы с разными датами для тестирования сортировки
    store.processNewOrder(101, &laptop, &client1, 5, 11, 2025);    // Старый заказ
    store.processNewOrder(102, &phone, &client2, 10, 11, 2025);     // Новый заказ
    store.processNewOrder(103, &tablet, &client3, 8, 11, 2025);    // "Ожидающий" заказ
    store.processNewOrder(104, &headphones, &client4, 9, 11, 2025); // "Ожидающий" заказ
    store.processNewOrder(105, &laptop, &client5, 12, 11, 2025);    // Самый новый
    store.processNewOrder(106, &phone, &client6, 6, 11, 2025);     // Старый заказ

    // 5. ТЕСТИРУЕМ СТРАТЕГИИ СОРТИРОВКИ
    std::cout << "\nТЕСТИРОВАНИЕ СТРАТЕГИЙ СОРТИРОВКИ:" << std::endl;
    std::cout << "====================================" << std::endl;

    // Создаем стратегии
    DateStrategy dateStrategy;
    DistanceStrategy distanceStrategy;

    // 5.1 Исходная очередь (порядок добавления)
    std::cout << "\n--- ИСХОДНАЯ ОЧЕРЕДЬ (порядок создания) ---" << std::endl;
    store.showDeliveryQueue();

    // 5.2 Сортировка по ДАТЕ (старые заказы первыми)
    std::cout << "\n--- ПРИМЕНЯЕМ СТРАТЕГИЮ: СОРТИРОВКА ПО ДАТЕ ---" << std::endl;
    store.applySortingStrategy(&dateStrategy);
    store.showDeliveryQueue();

    // 5.3 Сортировка по РАССТОЯНИЮ (ближние заказы первыми)
    std::cout << "\n--- ПРИМЕНЯЕМ СТРАТЕГИЮ: СОРТИРОВКА ПО РАССТОЯНИЮ ---" << std::endl;
    store.applySortingStrategy(&distanceStrategy);
    store.showDeliveryQueue();

    // 6. ДОСТАВКА ЗАКАЗОВ
    std::cout << "\nПРОЦЕСС ДОСТАВКИ:" << std::endl;
    std::cout << "===================" << std::endl;

    // Доставляем 3 ближних заказа (после сортировки по расстоянию)
    store.deliverOrders(3);

    // 6.1 СОЗДАЕМ ЕЩЁ ЗАКАЗЫ
    std::cout << "\nФОРМИРОВАНИЕ НОВЫХ ЗАКАЗОВ:" << std::endl;
    std::cout << "----------------------------" << std::endl;

    // Создадим новые товары
    Product keyboard(5, "Клавиатура NuPhy", 12300, 7);
    Product screen(6, "Монитор Asus", 34900, 4);
    Product microphone(7, "Микрофон Bloody", 7120, 11);
    store.addProductToWarehouse(&keyboard, 7);
    store.addProductToWarehouse(&screen, 4);
    store.addProductToWarehouse(&microphone, 11);

    // Создадим новых клиентов
    Client client7(7, "Андрей Грачёв", "Москва, ул. Ленина, д. 14", 9.9);
    Client client8(8, "Алина Крилина", "Москва, ул. Разбитых Фонарей, д. 99", 30.3);

    store.processNewOrder(106, &keyboard, &client7, 12, 11, 2025);
    store.processNewOrder(107, &microphone, &client8, 12, 11, 2025);
    store.processNewOrder(108, &screen, &client7, 12, 11, 2025);

    std::cout << "\n|---ТЕКУЩАЯ ОЧЕРЕДЬ---|" << std::endl;
    std::cout << "-----------------------" << std::endl;
    store.showDeliveryQueue();
    std::cout << "\nСОРТИРУЕМ ПО РАССТОЯНИЮ:" << std::endl;
    std::cout << "-------------------------\n" << std::endl;
    store.applySortingStrategy(&distanceStrategy);
    store.showDeliveryQueue();

    // 7. ВЫВОД В ФАЙЛ
    std::cout << "\nЭКСПОРТ ДАННЫХ В ФАЙЛ:" << std::endl;
    std::cout << "========================" << std::endl;

    // 7.1 Заказы в радиусе 10 км
    store.exportActiveOrdersInRadius(10.0, "active_orders_10km.txt");

    // 7.2 Заказы в радиусе 20 км (больше заказов)
    store.exportActiveOrdersInRadius(20.0, "active_orders_20km.txt");

    // 8. ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ
    std::cout << "\nДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ:" << std::endl;
    std::cout << "======================" << std::endl;

    // 8.1 Показываем остатки на складе
    store.showWarehouseStatus();

    // 8.2 Показываем оставшуюся очередь
    std::cout << "\n--- ОСТАВШАЯСЯ ОЧЕРЕДЬ ПОСЛЕ ДОСТАВКИ ---" << std::endl;
    store.showDeliveryQueue();

    // 8.3 Снова сортируем по дате (для демонстрации)
    std::cout << "\n--- ПОВТОРНАЯ СОРТИРОВКА ПО ДАТЕ ---" << std::endl;
    store.applySortingStrategy(&dateStrategy);
    store.showDeliveryQueue();

    // 9. ЗАВЕРШЕНИЕ
    std::cout << "\n=====================================" << std::endl;
    std::cout << "СИСТЕМА УСПЕШНО ПРОТЕСТИРОВАНА!" << std::endl;
    std::cout << "Файлы созданы: active_orders_10km.txt, active_orders_20km.txt" << std::endl;
    std::cout << "Стратегии сортировки работают корректно" << std::endl;
    std::cout << "=======================================" << std::endl;

    return 0;
}