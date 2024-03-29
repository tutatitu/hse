#!/bin/bash

# Проверка установки утилиты pwgen
if ! command -v pwgen &> /dev/null; then
	echo "Утилита pwgen не установлена"
	exit 1
fi

# Функция для вывода справочной информации
show_help() {
	echo 
	echo "--------------------------------------------Помощь-------------------------------------------"
	echo "Использование: $0 [ПАРАМЕТР]"
	echo "Параметры:"
	echo " <user_count>  Создать файл users.csv с заданным количеством пользователей и префиксом логина"
	echo " -h, --help    Показать справочную информацию" 
	echo "---------------------------------------------------------------------------------------------"
	echo 
}

# Проверка количества параметров
if [[ $# -ne 1 ]]; then
	echo "Неверное количество параметров: $#"
	show_help
	exit 1
fi

# Проверка правильности парметров
if [[ "$1" = "-h" || "$1" = "--help" ]]; then
	show_help
	exit 0
elif [[ "$1" =~ ^[0-9]+$ ]]; then
	user_count=$1
else
	echo "Неверный параметр: $1"
	show_help
	exit 1
fi

# Запрос префикса логина
read -p "Введите префикс логина пользователя: " login_prefix

# Проверка наличия введенного префикса
if [[ -z "$login_prefix" ]]; then
	echo "Префикс логина не может быть пустым"
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
