#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>
 
 
#define size 40
#define sizeB 500
#define sizeC 45
#define sizeM 300
#define monkey_age 500
#define banana_age 100
#define croc_age 850
int size_zoo = size * size * size, kb = 0, kc = 0, km = 0, d_m_sa = 0, d_m_c = 0, d_c_sa = 0, d_c = 0;
char field[size][size] = { 0 };


typedef struct Monkey
{
    int x;
    int y;
    int age;
    int satiety;
}monkey;
typedef struct Crocodilo
{
    int x;
    int y;
    int age;
    int satiety;
}croc;
typedef struct Banan
{
    int x;
    int y;
    int age;
}banan;

banan* B;
croc* C;
monkey* M;


int findB(int x, int y)
{
    for (int i = 0; i < size_zoo; i++)
        if (B[i].x == x && B[i].y == y && B[i].age != -1)
            return i;
    return -1;
}
int findM(int x, int y)
{
    for (int i = 0; i < size_zoo; i++)
        if (M[i].x == x && M[i].y == y && M[i].age != -1)
            return i;
    return -1;
}
int findC(int x, int y)
{
    for (int i = 0; i < size_zoo; i++)
        if (C[i].x == x && C[i].y == y && C[i].age != -1)
            return i;
    return -1;
}

void delB(int id)
{
    B[id].age = -1;
    field[B[id].x][B[id].y] = ' ';
    B[id].y = -1;
    B[id].x = -1;

}
void delM(int id)
{
    M[id].age = -1;
    M[id].satiety = -1;
    field[M[id].x][M[id].y] = ' ';
    M[id].x = -1;
    M[id].y = -1;
}
void delC(int id)
{
    C[id].age = -1;
    C[id].satiety = -1;
    field[C[id].x][C[id].y] = ' ';
    C[id].x = -1;
    C[id].y = -1;
}
void start()
{
    B = (banan*)malloc(size_zoo * sizeof(banan));
    C = (croc*)malloc(size_zoo * sizeof(croc));
    M = (monkey*)malloc(size_zoo * sizeof(monkey));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            field[i][j] = ' ';
    for (int i = 0; i < size_zoo; i++)
    {
        B[i].age = -1; B[i].x = -1; B[i].y = -1;
        C[i].age = -1; C[i].x = -1; C[i].y = -1;
        M[i].age = -1; M[i].x = -1; M[i].y = -1;
        C[i].satiety = -1; M[i].satiety = -1;
    }
    for (int i = 0; i < sizeB; i++)
    {
        int x = rand() % size;
        int y = rand() % size;
        while (field[x][y] != ' ')
        {
            x = rand() % size;
            y = rand() % size;
        }
        field[x][y] = '(';// доделать
        B[i].x = x;
        B[i].y = y;
        B[i].age = rand() % banana_age;
    }
    for (int i = 0; i < sizeM; i++)
    {
        int x = rand() % size;
        int y = rand() % size;
        while (field[x][y] != ' ')
        {
            x = rand() % size;
            y = rand() % size;
        }
        field[x][y] = 'm';
        M[i].x = x;
        M[i].y = y;
        M[i].satiety = 10 + rand() % 20;
        M[i].age = rand() % monkey_age;
    }
    for (int i = 0; i < sizeC; i++)
    {
        int y = rand() % size;
        int x = rand() % size;
        while (field[x][y] != ' ')
        {
            x = rand() % size;
            y = rand() % size;
        }
        field[x][y] = 'c';
        C[i].x = x;
        C[i].y = y;
        C[i].satiety = 10 + rand() % 30;
        C[i].age = rand() % croc_age;
    }
}

//----print----
void print_field()
{
    for (int i = -1; i < size; i++)
        printf("%3d", i);
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%3d", i);
        for (int j = 0; j < size; j++)
        {
            /*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED);*/
            if (field[i][j] == '(')
                printf("\x1b[33m ( \x1b[0m");
            if (field[i][j] == 'm')
                printf("\x1b[35m m \x1b[0m");
            if (field[i][j] == 'c')
                printf("\x1b[32m c \x1b[0m");
            if (field[i][j] == ' ')
                printf("   ");
        }
        printf("\n");
    }
    printf("\n");
    printf("Monkey deaths\nCroc: %d    Satiety: %d\n", d_m_c, d_m_sa);
    printf("Croc deaths\nSatiety: %d\n", d_c_sa);
    //printf("kb =  %d; kc =  %d; km =  %d         %d\n", kb, kc, km , 1);
    //printf("\n");
}
void print_banan()
{
    printf("banana\n");
    for (int i = 0; i < size_zoo; i++)
    {
        if (B[i].age != -1 && B[i].x != -1 && B[i].y != -1)
            printf("x:%d y:%d age:%d\n", B[i].x, B[i].y, B[i].age);
    }
    printf("\n");
}
void print_croc()
{
    printf("croc\n");
    for (int i = 0; i < size_zoo; i++)
    {
        if (C[i].age != -1)
            printf("id:%d x:%d y:%d age:%d satiety:%d\n", i, C[i].x, C[i].y, C[i].age, C[i].satiety);
    }
    printf("\n");
}
void print_monkey()
{
    printf("monkey\n");
    for (int i = 0; i < size_zoo; i++)
    {
        if (M[i].age != -1 && M[i].x != -1 && M[i].y != -1)
            printf("id:%d x:%d y:%d age:%d satiety:%d\n", i, M[i].x, M[i].y, M[i].age, M[i].satiety);
    }
    printf("\n");
}

//---act-------


//--banana--
void dropbanana(int x, int y, int k)
{
    if (k == 0) return;
    for (int i = 0; i < 10; i++)
    {
        int newx = (x + (rand() % 2 ? 1 : -1) * (rand() % 5 + 2) + size) % size;
        int newy = (y + (rand() % 2 ? 1 : -1) * (rand() % 5 + 2) + size) % size;
        if (field[newx][newy] == ' ')
        {
            for (int i = 0; i < size_zoo; i++)
            {
                if (B[i].age == -1)
                {
                    B[i].age = 0;
                    B[i].x = newx;
                    B[i].y = newy;
                    field[newx][newy] = '(';
                    dropbanana(x, y, k - 1);
                    return;
                }
            }
            //   dropbanana(x, y, k - 1);

        }
    }
}
void banana_phase()
{
    for (int i = 0; i < size_zoo; i++)
    {
        if (B[i].age == -1)
            continue;
        if (B[i].age >= banana_age)
        {
            delB(i);
            continue;
        }
        B[i].age++;
    }
}
//----------


//--monkey--

bool run_monkey(int xm, int ym, int id)
{
    for (int _ = 0; _ < 20; _++)
    {
        int i = (rand() % 2 ? 1 : -1) * (rand() % 3);
        int j = (rand() % 2 ? 1 : -1) * (rand() % 3);
        int newx = (xm + i + size) % size;
        int newy = (ym + j + size) % size;
        if (field[newx][newy] == 'c')
        {
            int flagx = (xm - newx > 0 ? 1 : -1);
            int flagy = (ym - newy > 0 ? 1 : -1);
            for (int i = 0; i < 10; i++)
            {
                int tx = (xm + flagx * (rand() % 3) + size) % size;
                int ty = (ym + flagy * (rand() % 3) + size) % size;
                if (field[tx][ty] == ' ')
                {
                    M[id].x = tx;
                    M[id].y = ty;
                    field[xm][ym] = ' ';
                    field[tx][ty] = 'm';
                    return true;
                }
                else if (field[tx][ty] == '(')
                {
                    M[id].x = tx;
                    M[id].y = ty;
                    M[id].satiety += 2;// подумать
                    dropbanana(tx, ty, 1 + rand() % 3);
                    delB(findM(tx, ty));
                    field[xm][ym] = ' ';
                    field[tx][ty] = 'm';
                    return true;
                }
            }
        }
    }
    return false;
}
void rand_act_monkey(int xm, int ym, int id)
{
    field[xm][ym] = ' ';
    for (int i = 0; i < 10; i++)
    {
        int flagx = (rand() % 2 == 0 ? 1 : -1);
        int flagy = (rand() % 2 == 0 ? 1 : -1);
        int newx = (xm + flagx * (rand() % 3) + size) % size;
        int newy = (ym + flagy * (rand() % 3) + size) % size;
        if (field[newx][newy] == ' ')
        {
            field[newx][newy] = 'm';
            M[id].x = newx;
            M[id].y = newy;
            return;
        }
    }
    field[xm][ym] = 'm';
}
void rand_act_croc(int xc, int yc, int id)
{
    field[xc][yc] = ' ';
    for (int i = 0; i < 10; i++)
    {
        int flagx = (rand() % 2 == 0 ? 1 : -1);
        int flagy = (rand() % 2 == 0 ? 1 : -1);
        int newx = (xc + flagx * (rand() % 3) + size) % size;
        int newy = (yc + flagy * (rand() % 3) + size) % size;
        if (field[newx][newy] == ' ')
        {
            field[newx][newy] = 'c';
            C[id].x = newx;
            C[id].y = newy;
            return;
        }
    }
    field[xc][yc] = 'c';
}
bool eat_monkey(int xm, int ym, int id)
{
    field[xm][ym] = ' ';
    for (int _ = 0; _ < 20; _++)
    {
        int i = (rand() % 2 ? 1 : -1) * (rand() % 3);
        int j = (rand() % 2 ? 1 : -1) * (rand() % 3);
        int newx = (xm + i + size) % size;
        int newy = (ym + j + size) % size;
        if (field[newx][newy] == '(')
        {
            if (abs(xm - newx) <= 1 && abs(ym - newy) <= 1) // если вплотную
            {
                int ib = findB(newx, newy);
                dropbanana(newy, newy, 1 + rand() % 3);
                delB(ib);
                field[newx][newy] = 'm';
                M[id].x = newx;
                M[id].y = newy;
                M[id].satiety = 30; // ПОДУМАТЬ
                return true;
            }
            int flagx = (xm - newx > 0 ? -1 : 1);
            int flagy = (ym - newy > 0 ? -1 : 1);
            int tx, ty;
            for (int it = 1; it <= 5; it++)
            {
                tx = (xm + flagx * (rand() % 3) + size) % size;
                ty = (ym + flagy * (rand() % 3) + size) % size;
                if (field[tx][ty] == ' ')
                {
                    M[id].x = tx;
                    M[id].y = ty;
                    field[tx][ty] = 'm';
                    return true;
                }
                else if (field[tx][ty] == '(')
                {
                    dropbanana(tx, ty, 1 + rand() % 3);
                    int ib = findB(tx, ty);
                    delB(ib);
                    field[tx][ty] = 'm';
                    M[id].satiety = 30;
                    M[id].x = tx;
                    M[id].y = ty;
                    return true;
                }
            }
        }
    }
    field[xm][ym] = 'm';
    return false;
}
bool eat_croc(int xc, int yc, int id)
{
    field[xc][yc] = ' ';
    for (int _ = 0; _ < 20; _++)
    {
        int i = (rand() % 2 ? 1 : -1) * (rand() % 3);
        int j = (rand() % 2 ? 1 : -1) * (rand() % 3);
        int newx = (xc + i + size) % size;
        int newy = (yc + j + size) % size;
        if (field[newx][newy] == 'm')
        {
            if (abs(xc - newx) <= 1 && abs(yc - newy) <= 1)
            {
                int ib = findM(newx, newy);
                d_m_c++;
                delM(ib);
                field[newx][newy] = 'c';
                C[id].x = newx;
                C[id].y = newy;
                C[id].satiety = 50; // ПОДУМАТЬr
                return true;
            }
            int flagx = (xc - newx > 0 ? -1 : 1);
            int flagy = (yc - newy > 0 ? -1 : 1);
            int tx, ty;
            for (int it = 1; it <= 5; it++)
            {
                tx = (xc + flagx * (rand() % 3) + size) % size;
                ty = (yc + flagy * (rand() % 3) + size) % size;
                if (field[tx][ty] == ' ')
                {
                    C[id].x = tx;
                    C[id].y = ty;
                    field[tx][ty] = 'c';
                    return true;
                }
                else if (field[tx][ty] == 'm')
                {
                    int ib = findM(tx, ty);
                    d_m_c++;
                    delM(ib);
                    field[tx][ty] = 'c';
                    C[id].satiety = 50;
                    C[id].x = tx;
                    C[id].y = ty;
                    return true;
                }
            }
        }
    }
    field[xc][yc] = 'c';
    return false;
}
bool sex_monkey(int xm, int ym, int id)
{
    for (int _ = 0; _ < 20; _++)
    {
        int i = (rand() % 2 ? 1 : -1) * (rand() % 3);
        int j = (rand() % 2 ? 1 : -1) * (rand() % 3);
        int newx = (xm + i + size) % size;
        int newy = (ym + j + size) % size;
        if (field[newx][newy] == 'm' && newx != xm && newy != ym && M[findM(newy, newy)].age >= 200 && M[findM(newx, newy)].satiety > 10)
        {
            //  printf("first:%d,%d second:%d,%d\n",xm,ym,newx,newy);
            if (abs(xm - newx) <= 1 && abs(ym - newy) <= 1)
            {
                int ib = findM(newx, newy);
                for (int i = 0; i < 10; i++)
                {
                    // выкидываем ребенка
                    int flagx = (rand() % 2 == 0 ? 1 : -1);
                    int flagy = (rand() % 2 == 0 ? 1 : -1);
                    int nx = (xm + flagx * (rand() % 3) + size) % size;
                    int ny = (ym + flagy * (rand() % 3) + size) % size;
                    if (field[nx][ny] == ' ')
                    {
                        for (int i = 0; i < size_zoo; i++)
                        {
                            if (M[i].age == -1)
                            {
                                //printf("child:%d,%d\n",nx,ny);
                                field[nx][ny] = 'm';
                                M[i].age = 0;
                                M[i].satiety = 10;
                                M[id].satiety -= 2;
                                M[ib].satiety -= 2;
                                M[i].x = nx;
                                M[i].y = ny;
                                return true;
                            }
                        }
                    }
                    else if (field[nx][ny] == '(')
                    {
                        for (int i = 0; i < size_zoo; i++)
                        {
                            if (M[i].age == -1)
                            {
                                //printf("child:%d,%d\n",nx,ny);
                                delB(findB(nx, ny));
                                field[nx][ny] = 'm';
                                M[i].age = 0;
                                M[i].satiety = 9;
                                M[id].satiety -= 2;
                                M[ib].satiety -= 2;
                                M[i].x = nx;
                                M[i].y = ny;
                                return true;
                            }
                        }
                    }
                }
            }
            int flagx = (xm - newx > 0 ? -1 : 1);
            int flagy = (ym - newy > 0 ? -1 : 1);
            int tx, ty;
            for (int it = 1; it <= 5; it++)
            {
                tx = (xm + flagx * (rand() % 3) + size) % size;
                ty = (ym + flagy * (rand() % 3) + size) % size;
                if (field[tx][ty] == ' ')
                {
                    M[id].x = tx;
                    M[id].y = ty;
                    field[xm][ym] = ' ';
                    field[tx][ty] = 'm';
                    return true;
                }
                else if (field[tx][ty] == 'm')
                {
                    int ib = findM(tx, ty);
                    for (int i = 0; i < 10; i++)
                    {
                        int flagx = (rand() % 2 == 0 ? 1 : -1);
                        int flagy = (rand() % 2 == 0 ? 1 : -1);
                        int nx = (xm + flagx * (rand() % 3) + size) % size;
                        int ny = (ym + flagy * (rand() % 3) + size) % size;
                        if (field[nx][ny] == ' ')
                        {
                            for (int i = 0; i < size_zoo; i++)
                            {
                                if (M[i].age == -1)
                                {
                                    field[nx][ny] = 'm';
                                    M[i].age = 0;
                                    M[i].satiety = 9;
                                    M[id].satiety -= 2;
                                    M[ib].satiety -= 2;
                                    M[i].x = nx;
                                    M[i].y = ny;
                                    return true;
                                }
                            }
                        }
                        else if (field[nx][ny] == '(')
                        {
                            for (int i = 0; i < size_zoo; i++)
                            {
                                if (M[i].age == -1)
                                {
                                    //printf("child:%d,%d\n",nx,ny);
                                    delB(findB(nx, ny));
                                    field[nx][ny] = 'm';
                                    M[i].age = 0;
                                    M[i].satiety = 9;
                                    M[id].satiety -= 2;
                                    M[ib].satiety -= 2;
                                    M[i].x = nx;
                                    M[i].y = ny;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool sex_croc(int xc, int yc, int id)
{
    for (int _ = 0; _ < 40; _++)
    {
        int i = (rand() % 2 ? 1 : -1) * (rand() % 5);
        int j = (rand() % 2 ? 1 : -1) * (rand() % 5);
        int newx = (xc + i + size) % size;
        int newy = (yc + j + size) % size;
        if (field[newx][newy] == 'c' && newx != xc && newy != yc && C[findC(newy, newy)].age >= 600 &&
            C[findC(newy, newy)].satiety > 8)
        {
            //  printf("first:%d,%d second:%d,%d\n",xm,ym,newx,newy);
            if (abs(xc - newx) <= 1 && abs(yc - newy) <= 1)
            {
                int ib = findC(newx, newy);
                for (int i = 0; i < 10; i++)
                {
                    int flagx = (rand() % 2 == 0 ? 1 : -1);
                    int flagy = (rand() % 2 == 0 ? 1 : -1);
                    int nx = (xc + flagx * (rand() % 3) + size) % size;
                    int ny = (yc + flagy * (rand() % 3) + size) % size;
                    if (field[nx][ny] == ' ')
                    {
                        for (int i = 0; i < size_zoo; i++)
                        {
                            if (C[i].age == -1)
                            {
                                //printf("child:%d,%d\n",nx,ny);
                                field[nx][ny] = 'c';
                                C[i].age = 0;
                                C[i].satiety = 15;
                                C[id].satiety -= 5;
                                C[ib].satiety -= 5;
                                C[i].x = nx;
                                C[i].y = ny;
                                return true;
                            }
                        }
                    }
                    else if (field[nx][ny] == 'm')
                    {
                        for (int i = 0; i < size_zoo; i++)
                        {
                            if (C[i].age == -1)
                            {
                                //printf("child:%d,%d\n",nx,ny);
                                delM(findM(nx, ny));
                                field[nx][ny] = 'c';
                                C[i].age = 0;
                                C[i].satiety = 15;
                                C[id].satiety -= 5;
                                C[ib].satiety -= 5;
                                C[i].x = nx;
                                C[i].y = ny;
                                return true;
                            }
                        }
                    }
                    else if (field[nx][ny] == '(')
                    {
                        for (int i = 0; i < size_zoo; i++)
                        {
                            if (C[i].age == -1)
                            {
                                //printf("child:%d,%d\n",nx,ny);
                                delB(findB(nx, ny));
                                field[nx][ny] = 'c';
                                C[i].age = 0;
                                C[i].satiety = 15;
                                C[id].satiety -= 5;
                                C[ib].satiety -= 5;
                                C[i].x = nx;
                                C[i].y = ny;
                                return true;
                            }
                        }
                    }
                }
            }
            int flagx = (xc - newx > 0 ? -1 : 1);
            int flagy = (yc - newy > 0 ? -1 : 1);
            int tx, ty;
            for (int it = 1; it <= 5; it++)
            {
                tx = (xc + flagx * (rand() % 4) + size) % size;
                ty = (yc + flagy * (rand() % 4) + size) % size;
                if (field[tx][ty] == ' ')
                {
                    C[id].x = tx;
                    C[id].y = ty;
                    field[xc][yc] = ' ';
                    field[tx][ty] = 'c';
                    return true;
                }
                else if (field[tx][ty] == 'c')
                {
                    int ib = findC(tx, ty);
                    for (int i = 0; i < 10; i++)
                    {
                        int flagx = (rand() % 2 == 0 ? 1 : -1);
                        int flagy = (rand() % 2 == 0 ? 1 : -1);
                        int nx = (xc + flagx * (rand() % 3) + size) % size;
                        int ny = (yc + flagy * (rand() % 3) + size) % size;
                        if (field[nx][ny] == ' ')
                        {
                            for (int i = 0; i < size_zoo; i++)
                            {
                                if (C[i].age == -1)
                                {
                                    field[nx][ny] = 'c';
                                    C[i].age = 0;
                                    C[i].satiety = 15;
                                    C[id].satiety -= 5;
                                    C[ib].satiety -= 5;
                                    C[i].x = nx;
                                    C[i].y = ny;
                                    return true;
                                }
                            }
                        }
                        else if (field[nx][ny] == '(')
                        {
                            for (int i = 0; i < size_zoo; i++)
                            {
                                if (C[i].age == -1)
                                {
                                    //printf("child:%d,%d\n",nx,ny);
                                    delB(findB(nx, ny));
                                    field[nx][ny] = 'c';
                                    C[i].age = 0;
                                    C[i].satiety = 15;
                                    C[id].satiety -= 5;
                                    C[ib].satiety -= 5;
                                    C[i].x = nx;
                                    C[i].y = ny;
                                    return true;
                                }
                            }
                        }
                        else if (field[nx][ny] == 'm')
                        {
                            for (int i = 0; i < size_zoo; i++)
                            {
                                if (C[i].age == -1)
                                {
                                    //printf("child:%d,%d\n",nx,ny);
                                    delM(findM(nx, ny));
                                    field[nx][ny] = 'c';
                                    C[i].age = 0;
                                    C[i].satiety = 15;
                                    C[id].satiety -= 5;
                                    C[ib].satiety -= 5;
                                    C[i].x = nx;
                                    C[i].y = ny;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
void monkey_action(int im)
{
    // field[M[im].x][M[im].y] = ' ';
    int xm = M[im].x;
    int ym = M[im].y;
    if (run_monkey(xm, ym, im))
        return;
    if (M[im].satiety <= 10)
    {
        if (eat_monkey(xm, ym, im))
            return;
    }
    if (M[im].satiety > 15 && M[im].age >= 300)
    {
        if (sex_monkey(xm, ym, im))
            return;
    }
    rand_act_monkey(xm, ym, im);
}
void croc_action(int ic)
{
    // field[M[im].x][M[im].y] = ' ';
    int xc = C[ic].x;
    int yc = C[ic].y;
    if (C[ic].satiety <= 8)
    {
        if (eat_croc(xc, yc, ic))
            return;
    }
    if (C[ic].satiety > 8 && C[ic].age >= 600)
    {
        if (sex_croc(xc, yc, ic))
            return;
    }
    rand_act_croc(xc, yc, ic);
}
void monkey_phase()
{
    for (int i = 0; i < size_zoo; i++)
    {
        if (M[i].age == -1)
            continue;
        if (M[i].satiety <= 0 || M[i].age >= monkey_age)
        {
            d_m_sa += (M[i].satiety <= 0);
            delM(i);
            continue;
        }
        M[i].age++;
        M[i].satiety--;
        monkey_action(i);
    }
}
void croc_phase()
{
    for (int i = 0; i < size_zoo; i++)
    {
        if (C[i].age == -1)
            continue;
        if (C[i].satiety <= 0 || C[i].age >= croc_age)
        {
            d_c_sa += (C[i].satiety <= 0);
            delC(i);
            continue;
        }
        C[i].age++;
        C[i].satiety--;
        croc_action(i);
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "ะก");
    start();
    for (int i = 0; i < 10000; i++)
    {
        //Sleep(100);
        printf("ROUND:%d\n", i);
        print_field();
        monkey_phase();
        banana_phase();
        croc_phase();
        COORD position = { 0, 0 }; //позиция x и y
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsole, position);
    }
}