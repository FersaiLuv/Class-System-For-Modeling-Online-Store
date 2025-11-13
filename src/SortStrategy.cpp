// Реализация стратегий сортировки

#include "SortStrategy.h"
#include "DeliveryQueue.h"
#include <iostream>

// Определение и реализация сортировки по дате
void DateStrategy::sortQueue(DeliveryQueue* queue)
{
	std::cout << "|СОРТИРОВКА ПО ДАТЕ|" << std::endl;

	Order* orders[MAX_ORDERS]; // Хранилище заказов (будут браться из очереди)
	unsigned int count; // Подсчёт заказов
	queue->getOrdersForSorting(orders, count); // Выгрузка заказов из очереди в массив

	if (count <= 1) {
		std::cout << "Мало заказов для сортировки" << std::endl;
		return;
	}

	// Алгоритм сортировки методом пузырька
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (orders[j]->getDateAsNumber() > orders[j + 1]->getDateAsNumber()) {
				Order* tmp = orders[j];
				orders[j] = orders[j + 1];
				orders[j + 1] = tmp;
			}
		}
	}

	// Выгрузка отсортированных заказов в очередь
	queue->updateQueueAfterSorting(orders, count);
	std::cout << "Очередь отсортирована по дате (" << count << " заказов)" << std::endl;
}

// Определение и реализация сортировки по расстоянию (аналогия с предыдущим методом)
void DistanceStrategy::sortQueue(DeliveryQueue* queue)
{
	std::cout << "|СОРТИРОВКА ПО РАССТОЯНИЮ|" << std::endl;

	Order* orders[MAX_ORDERS];
	unsigned int count;
	queue->getOrdersForSorting(orders, count);

	if (count <= 1) {
		std::cout << "Мало заказов для сортировки" << std::endl;
		return;
	}

	// Алгоритм сортировки методом пузырька
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (orders[j]->getDistance() > orders[j + 1]->getDistance()) {
				Order* tmp = orders[j];
				orders[j] = orders[j + 1];
				orders[j + 1] = tmp;
			}
		}
	}

	// Выгрузка отсортированных заказов в очередь
	queue->updateQueueAfterSorting(orders, count);
	std::cout << "Очередь отсортирована по расстоянию (" << count << " заказов)" << std::endl;
}