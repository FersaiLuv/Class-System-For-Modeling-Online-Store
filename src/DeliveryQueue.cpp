// Определние класса DeliveryQueue Очередь FIFO
#include "DeliveryQueue.h"

// Конструктор структуры QueueNode
QueueNode::QueueNode(Order* ord) : order(ord), next(nullptr) {}


DeliveryQueue::DeliveryQueue() : head(nullptr), tail(nullptr), order_count(0) {}

// Методы
void DeliveryQueue::addOrder(Order* order) // добавить заказ
{
	// Выделение памяти под блок с заказом
	QueueNode* new_node = new QueueNode(order);

	// Проверка: если очередь пуста, то созданный блок становится головой и концом, а следующий уже концом
	if (tail == nullptr) {
		head = new_node;
		tail = new_node;
	}
	else {
		tail->next = new_node;
		tail = new_node;
	}

	order_count++;
	std::cout << "Заказ № " << order->getId() << " добавлен в очередь" << std::endl;
}

Order* DeliveryQueue::getNextOrder() // Взятие заказа из очереди
{
	if (head == nullptr) {
		std::cout << "Очередь пуста" << std::endl;
		return nullptr;
	}

	// Запоминаем блок (берем первый заказ)
	QueueNode* first_node = head;
	Order* first_order = first_node->order;

	// Далее перемещаем голову из очереди на следующий заказ
	head = head->next;

	// Если голова стала указывать на пустоту, значит очередь опустела
	if (head == nullptr) {
		tail = nullptr;
	}

	// Очищаем очередь (Берем первый заказ из очереди)
	delete first_node;
	order_count--;

	std::cout << "Заказ №" << first_order->getId() << " взят из очереди" << std::endl;
	return first_order;
}

void DeliveryQueue::show_all_orders() // Показать все заказы
{
	if (head == nullptr) {
		std::cout << "Очередь пуста" << std::endl;
		return;
	}

	std::cout << "=== ОЧЕРЕДЬ ДОСТАВКИ (" << order_count << " заказов) ===" << std::endl;

	QueueNode* current = head;  // Начинаем с головы
	int position = 1;

	while (current != nullptr) {
		std::cout << position << ". Заказ №" << current->order->getId();
		std::cout << " | " << current->order->getDistance() << " км";
		std::cout << " | " << current->order->getDate() << std::endl;

		current = current->next;  // Переходим к следующему блоку
		position++;
	}
}

// Методы для стратегий
void DeliveryQueue::getOrdersForSorting(Order* orders[], unsigned int& count) // Метод выгрузки всех заказов из очереди во временный массив для сортировки
{
	QueueNode* current = head; // Текущий заказ
	count = 0; // Обнуляем кол-во заказов (пересчитываться будет заново)

	while (current != nullptr && count < MAX_ORDERS) { // Пока есть заказы загружаем их в массив

		orders[count] = current->order;
		current = current->next;
		count++; // считаем заказы
	}
}

void DeliveryQueue::updateQueueAfterSorting(Order* orders[], unsigned int count) // Метод выгрузки отсортированных заказов из массива в очередь
{
	// Отчистка текущей очереди
	while (head != nullptr) {
		QueueNode* tmp = head;
		head = head->next;
		delete tmp;
	}

	// Перстройка очереди
	head = nullptr;
	tail = nullptr;
	order_count = 0;

	// Добавляем заказы из массива в чередь
	for (int i = 0; i < count; i++) {
		addOrder(orders[i]);
	}
}

void DeliveryQueue::applyStrategy(SortStrategy* strategy) // Установка и применение стратегии сортировки 
{
	if (strategy != nullptr) {
		strategy->sortQueue(this);
	}
}

DeliveryQueue::~DeliveryQueue() // Деструктор
{
	while (head != nullptr) {
		QueueNode* temp = head;   // Запоминаем текущий блок
		head = head->next;        // Переходим к следующему
		delete temp;              // Удаляем запомненный блок
	}
}