#!/bin/bash

if [ $# -lt 1]; then
echo "Ошибка: Необходимо указать количество создаваемых пользователей."
echo "Использование: $0 <количество-пользователей>"
exit 1
fi

# Получение аргументов
user_count=$1

# Запрос префикса логина
read -p "Введите префикс логина пользователя: " login_prefix

# Проверка наличия введенного префикса
if [ -z "$login_prefix" ]; then
echo "Ошибка: Префикс логина не может быть пустым."
exit 1
fi

# Проверка установки утилиты pwgen
if ! command -v pwgen &> /dev/null; then
echo "Ошибка: Утилита pwgen не установлена. Установите её перед выполнением скрипта."
exit 1
fi

# Создание файла users.csv
output_file="users.csv"
echo "Префикс логина,Пароль" > "$output_file"

# Цикл по созданию пользователей
for ((i=1; i<=$user_count; i++)); do
# Генерация пароля с использованием pwgen
password=$(pwgen -1)

# Форматирование порядкового номера с ведущими нулями
user_number=$(printf "%04d" $i)

# Формирование строки для записи в файл
user_line="${login_prefix}_${user_number},${password}_${user_number}"

# Добавление строки в файл
echo "$user_line" >> "$output_file"
done

# Успешное завершение скрипта
echo "Создан файл $output_file с пользователями."
exit 0
