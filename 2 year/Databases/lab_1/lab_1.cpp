#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <random>
#include <regex>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <time.h> 
#include <stack> 
#include <deque> 
#include <locale.h>
#include <locale>
#include <cstdlib>
#include <cctype>
#include <Windows.h>
using namespace std;
typedef pair<int, int> pii;
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
void fastio()
{
	ios_base::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
}
class student
{
public:
    explicit student(string name = "", string surname = "",string patronymic = "") : name(name), surname(surname), patronymic(patronymic){}
    string name, surname, patronymic;
};
unordered_map<int, string> variants;
unordered_map<int, int> testing_table,mark;
unordered_map <int,student> students;
vector<int> students_id, variants_id;
int students_size = 0;
int variants_size = 5;
string database = "",backup = "";
ifstream in;
ofstream out;
void students_init()
{	
    in.open("names.txt");
	string name, surname, patronymic;
    while(in >> surname >> name >> patronymic)
	{	
		students[students_size] = student(name, surname, patronymic);
		students_id.push_back(students_size++);
	}
    in.close();
}
int search_student(string _name, string _surname, string _patronymic)
{
	for (int id : students_id)
	{
		//cout << id << " "<< students[id].name<<" "<<students[id].surname<<" "<<students[id].patronymic<<endl;
		if (students[id].name == _name && students[id].surname == _surname && students[id].patronymic == _patronymic)
        {
           return id;
        }
	}
	return -1;
}
void add_student(string _name, string _surname, string _patronymic)
{
	if (search_student(_name, _surname, _patronymic) != -1)
	{
		cout << "We already have this student"<<endl<<endl;
		return;
	}
	//cout << search_student(_name, _surname, _patronymic) << endl;
	testing_table[students_size] = rand() % variants_size;
	students[students_size] = student(_name, _surname, _patronymic);
	//mark[students_size]=rand() % 10 + 1;
	students_id.push_back(students_size++);
}
void delete_student(string _name, string _surname, string _patronymic)
{
	int id = search_student(_name, _surname, _patronymic);
	if (id == -1)
	{
		cout << "We can't delete non-existent student"<<endl<<endl;
		return;
	}
    //cout<<id<<endl;
	students_id.erase(find(students_id.begin(), students_id.end(), id));
}
void edit_student(string _name, string _surname, string _patronymic, string _new_name, string _new_surname, string _new_patronymic,int variant,int m)
{
	if (search_student(_name, _surname, _patronymic) == -1)
	{
		cout << "We can't edit non-existent student"<<endl<<endl;
		return;
	}
	if (search_student(_new_name, _new_surname, _new_patronymic) != -1 && _new_name != _name && _new_surname != _surname && _new_patronymic != _patronymic)
	{
		cout << "We already have this student"<<endl<<endl;
		return;
	}
	int id = search_student(_name, _surname, _patronymic);
	students[id].name = _new_name; students[id].surname = _new_surname;
	students[id].patronymic = _new_patronymic;
	mark[id] = m;
	testing_table[id] = variant;
}
void show_id(int id)
{
	if(id>=students_size || search_student(students[id].name,students[id].surname, students[id].patronymic) == -1)
	{
		cout<<"This student doesn't exist"<<endl;
		return;
	}
	cout << "id          full_name			" << "path_to_file	" << "mark"<<endl;
	cout << id <<"    "<< students[id].surname << " " << students[id].name << " " << students[id].patronymic;
	int size = students[id].name.size() + students[id].surname.size() + students[id].patronymic.size();
	for (int j = 0; j < 37 - size; j++)
		cout << ' ';
	cout << variants[testing_table[id]] << "	 ";
	if(mark[id] == 0)
		cout<< "NULL" << endl;
	else
		cout<<mark[id]<<endl;
		cout<<endl;
}
void show_student(string _name, string _surname, string _patronymic)
{
	int id = search_student(_name, _surname, _patronymic);
	if(id == -1)
	{
		cout<<"This student doesn't exist"<<endl;
		return;
	}
	cout << "id          full_name			" << "path_to_file	" << "mark"<<endl;
	cout << id <<"    "<< students[id].surname << " " << students[id].name << " " << students[id].patronymic;
	int size = students[id].name.size() + students[id].surname.size() + students[id].patronymic.size();
	for (int j = 0; j < 37 - size; j++)
		cout << ' ';
	cout << variants[testing_table[id]] << "	 ";
	if(mark[id] == 0)
		cout<< "NULL" << endl;
	else
		cout<<mark[id]<<endl;
		cout<<endl;

}
void variants_init()
{
	ifstream in("variants.txt");
	string variant;
	for (int i = 0; i <= variants_size; i++)
	{
		in >> variant;
		variants[i] = variant;
		variants_id.push_back(i);
	}
    in.close();
}
void print_testing_table()
{
	cout << "id          full_name			" << "path_to_file	" << "mark"<<endl;
	for (int i : students_id)
	{	
		cout << i <<"    "<< students[i].surname << " " << students[i].name << " " << students[i].patronymic;
		int size = students[i].name.size() + students[i].surname.size() + students[i].patronymic.size();
		for (int j = 0; j < 37 - size; j++)
			cout << ' ';
		cout << variants[testing_table[i]] << "	 ";
		if(mark[i] == 0)
			cout<< "NULL" << endl;
		else
			cout<<mark[i]<<endl;
			cout<<endl;
	}
}
void testing_table_init()
{
	for (int i = 0; i < students_size; i++)
	{
		testing_table[i] = rand() % variants_size + 1;
		//mark[i] = rand() % 10 + 1;
	}
	print_testing_table();
}
void show_commands_1()
{
	cout<<endl<<"----------------------------MENU------------------------------"<<endl;
	cout<<"add surname name patronymic"<<endl;
	cout<<"delete surname name patronymic"<<endl;
	cout<<"edit old_surname old_name old_patronymic new_surname new_name new_patronymic"<<endl;
	cout<<"show_id id_student"<<endl;
	cout<<"show_student surname name patronymic"<<endl;
	cout<<"show_all"<<endl;
	cout<<"open_group"<<endl;
	cout<<"menu"<<endl;
	cout<<"exit"<<endl<<endl;
}
void show_commands()
{
	cout<<endl<<"----------------------------MENU------------------------------"<<endl;
	cout<<"----------------------------add-------------------------------"<<endl;
	cout<<"---------------------------delete-----------------------------"<<endl;
	cout<<"----------------------------edit------------------------------"<<endl;
	cout<<"----------------------------show------------------------------"<<endl;
	cout<<"----------------------------load------------------------------"<<endl;
    cout<<"---------------------------create-------------------------------"<<endl;
	cout<<"----------------------------menu------------------------------"<<endl;
	cout<<"----------------------------exit------------------------------"<<endl<<endl;
}
void menu()
{
	show_commands();
	string command;
	while(cin>>command)
	{
		cout<<endl;
		if(command == "exit")
        {
                        // сохраняем
            out.open(database + ".txt");
            for (int i : students_id)
            {
                out<<i<<" "<< students[i].surname << " " << students[i].name << " " << students[i].patronymic <<" "<< testing_table[i] << " "<<mark[i]<<endl;
            }
            return;
        }
		else if(command == "menu")
			show_commands();
		else if(command == "add")
		{
			cout<<"Type student name to add in the format: surname name patronymic"<<endl;
			string name,surname,patronymic;
			cin>>surname>>name>>patronymic; // ФИО
			//cout<<surname<<name<<patronymic<<endl;
			add_student(name,surname,patronymic);
		}
		else if(command == "delete")
		{
			cout<<"Type student name to delete in the format: surname name patronymic"<<endl;
			string name,surname,patronymic;
			cin>>surname>>name>>patronymic; // ФИО
			delete_student(name,surname,patronymic);
		}
		else if(command == "edit")
		{
			int variant,mark;
			string name,surname,patronymic,new_name,new_surname,new_patronymic;
			cout<<"Type student name to edit in the format: surname name patronymic"<<endl;
			cin>>surname>>name>>patronymic;
			cout<<"Type new data in the format: surname name patronymic variant mark"<<endl;
			cin>>new_surname>>new_name>>new_patronymic>>variant>>mark; // ФИО
			edit_student(name,surname,patronymic,new_name,new_surname,new_patronymic,variant,mark);
		}
		else if(command == "show")
		{
			//cout<<"What are you want to show:"<<endl;
			cout<<"id - show student by id"<<endl;
			cout<<"name - show student by name"<<endl;
			cout<<"all - show all students"<<endl;
			string atribute;
			cin>>atribute;
			if(atribute == "id")
			{
				cout<<"Type student id"<<endl;
				int id;
				cin>>id;
				show_id(id);
			}
			else if(atribute == "name")
			{
				cout<<"Type student name to show in the format: surname name patronymic"<<endl;
				string name,surname,patronymic;
				cin>>surname>>name>>patronymic; // ФИО
				show_student(name,surname,patronymic);
			}
			else
				print_testing_table();
		}
		else if(command == "load")
		{
            // сохраняем
            //ofstream out;
            out.open(database + ".txt");
            for (int i : students_id)
            {
                out<< i <<" "<< students[i].surname << " " << students[i].name << " " << students[i].patronymic <<" "<< testing_table[i] << " "<<mark[i]<<endl;
            }
            // очищаем
            out.close();
			students_id.clear();
            for(int i = 0;i<students_size;i++)
            {
                testing_table[i]=0;
                mark[i]=0;
				//students[i] = student("","","");
            }
            students_size = 0;

            // cout<<"Type what you want to load:"<<endl;
			// cout<<"databse"<<endl;
			// cout<<"backup"<<endl;
            // string atribute;
            // cin>>atribute;
            cout<<"Name of file:"<<endl;
            cin >> database;
            in.open(database + ".txt");
            int id,var, m;
            string name, surname, patronymic;
            while(in >> id >> surname >> name >> patronymic >> var >> m)
            {
                students[id] = student(name, surname, patronymic);
                testing_table[id] = var;
                mark[id] = m;
                students_id.push_back(id);
				students_size++;
				cout<< id <<" "<< surname << " " << name << " " << patronymic <<" "<< testing_table[id] << " "<<mark[id]<<endl;
            }
            in.close();
		}
        else if(command == "create")
        {
            cout<<"Type what you want to create:"<<endl;
			cout<<"database"<<endl;
			cout<<"backup"<<endl;
            string atribute;
            cin>>atribute;
            if(atribute == "database")
            {
                if(database != "")
                {
                    // сохраняем
                    out.open(database + ".txt");
                    for (int i : students_id)
                    {
                        out<< i<<" "<<students[i].surname << " " << students[i].name << " " << students[i].patronymic <<" "<< testing_table[i] << " "<<mark[i]<<endl;
                    }
                    // очищаем
                    out.close();                   
                    students_id.clear();
                    for(int i = 0;i<students_size;i++)
                    {
                        testing_table[i]=0;
                        mark[i]=0;
						//students[i] = student("","","");
                    }
                    students_size = 0;
                }
                cout<<"Type name of new database:"<<endl;
                cin>>database;
                students_init();
                testing_table_init();
            }
            else
            {
                cout<<"Type name of new backup:"<<endl;
                cin>>backup;
                out.open(backup + ".txt");
                for (int i : students_id)
                {
                    out<<i<<" "<< students[i].surname << " " << students[i].name << " " << students[i].patronymic <<" "<< testing_table[i] << " "<<mark[i]<<endl;
                }
                out.close();
            }
        }
		else
		{
			cout<<"Wrong command format"<<endl;
		}
		cout<<endl;
	}
} 
int main()
{
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
	fastio();
	variants_init();
	menu();
	return 0;
}