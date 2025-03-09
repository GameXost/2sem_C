cmake_minimum_required(VERSION 3.10)
project(StudentDatabase)

set(CMAKE_C_STANDARD 11)  # Используем стандарт C11
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")  # Флаги компиляции





# Добавляем исполняемые файлы
add_executable(getndump getndump.c)
add_executable(results results.c)
