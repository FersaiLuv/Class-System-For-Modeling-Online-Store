cmake_minimum_required(VERSION 3.10)
project(OnlineStore)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем все предупреждения
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# Добавляем исполняемый файл
add_executable(online_store
    src/main.cpp
    src/OnlineStore.cpp
    src/Client.cpp
    src/Order.cpp
    src/Product.cpp
    src/Warehouse.cpp
    src/DeliveryQueue.cpp
    src/Manager.cpp
    src/Driver.cpp
    src/WarehouseWorker.cpp
    src/SortStrategy.cpp
)

# Указываем пути к заголовочным файлам
target_include_directories(online_store PRIVATE include)