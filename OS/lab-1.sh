#!/bin/bash

# Проверка наличия аргументов
if [ $# -lt 2 ]; then
echo "Ошибка: Необходимо указать префикс логина и количество создаваемых пользователей."
echo "Использование: $0 <префикс-логина> <количество-пользователей>"
exit 1
fi

# Получение аргументов
login_prefix=$1
user_count=$2

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
