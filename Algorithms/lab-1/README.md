# Первая лабораторная работа по алгоритмам
## Информация о проекте
Лабораторная выполнена на с++20, компилятор g++ 13.1.0.  
Запуск:
```powershell
cd "...\lab_1\" ; #вместо ... указываем путь до папки с файлом
if ($?) { g++ lab_1.cpp -o lab_1 } ; 
if ($?) { .\lab_1 }
```
# Код
## Генерация данных
### Первый способ
![image](https://github.com/tutatitu/study_projects/assets/135254365/c47097f3-04f1-42e6-98fd-14e63abaadaf)
### Второй способ
![image](https://github.com/tutatitu/study_projects/assets/135254365/bdb9f0ff-458b-4966-a277-63cdaf07fdb4)
## Алгоритмы
### Бинарный поиск по определенной строке
![image](https://github.com/tutatitu/study_projects/assets/135254365/10705024-2eae-4185-a04f-3713ad2c929e)
### Бинарный поиск по всей матрице
![image](https://github.com/tutatitu/study_projects/assets/135254365/b3713bde-946f-4ff2-9668-22f6917b1666)
### Поиск лестницей
![image](https://github.com/tutatitu/study_projects/assets/135254365/be319904-d46d-42ca-9174-de0350578cc5)
### Экспоненциальный поиск
![image](https://github.com/tutatitu/study_projects/assets/135254365/06f017cc-02b0-42e4-91f3-fe7b63d040c8)
## Время работы
### Подсчет
![image](https://github.com/tutatitu/study_projects/assets/135254365/38d9bbc9-0c51-4b60-898a-ebafcb39aeb0)
### Вывод
![image](https://github.com/tutatitu/study_projects/assets/135254365/05c5cd88-8424-40af-8194-340ad0f9e2dd)
# Визуализация и анализ
## Продолжительность работы алгоритмов
Время в нс, 10000 тестов
### Первый тип генерации
Таблица:  
  
![image](https://github.com/tutatitu/study_projects/assets/135254365/8526ce23-d53e-4a8f-8b4a-9f0a601ad4a1)
Приведу обычный и логарифмический графики:  

![image](https://github.com/tutatitu/study_projects/assets/135254365/3a4fda18-4157-432a-aa6c-c331bcbd6100)

![image](https://github.com/tutatitu/study_projects/assets/135254365/aed5d601-c430-4249-ac9b-f3eaadff2c70)
### Второй тип генерации
Таблица:

![image](https://github.com/tutatitu/study_projects/assets/135254365/51eb4082-db0b-468c-a22c-78f8aa3bb047)
Снова приведу два типа графиков:

![image](https://github.com/tutatitu/study_projects/assets/135254365/ba71d2d0-951c-4638-9466-79aa751a288a)

![image](https://github.com/tutatitu/study_projects/assets/135254365/e5118565-731e-4fd7-b5f9-1f797cc51b7f)
### Отношение времени для первого способа генерации ко второму
![image](https://github.com/tutatitu/study_projects/assets/135254365/c0ea4290-7b61-417f-ac11-8143baa2fc32)
## Выводы/Тезисы/Мысли
На обоих типах генерации и небольших размерах бинарный и экспоненциальный поиск работают быстрее поиска лестницей. С увеличением размера бинарный поиск демонстрирует стремительный рост времени, в то время как 2 других алгоритма меняются не так сильно.  
На 1 типе генерации при больших размерах поиск лестницей работает быстрее других алгоритмов.  
На 2 типе генерации экспоненциальный поиск является самым быстрым алгоритмом на всех рассмотренных размерах.
### Сравнение типов генерации
Бинарный поиск работает быстрее на большинстве размеров 2 типа генерации.  
Поиск лестницей в среднем работает одинаково на обоих типах генерации.  
Экспоненциальный поиск работает быстрее на 2 типе генерации при любых размерах.
