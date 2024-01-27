#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#define CODE_SIZE 100
 
char Input[100];
char Encoded[100];
char Decoded[100];
int freq[1000] = { 0 };
char codehuff[3000][5000]={0};
char s[1000] = { 0 };
 
typedef struct NODE
{
    unsigned char symb;
    bool isSymb;
    unsigned int freq;
    char code[CODE_SIZE];
    struct NODE* left, * right, * next;
}NODE;
 
NODE* head = 0;
void add2list(NODE** pphead, int val, unsigned char symb, bool isSymb)
{
    NODE** pp = pphead, * pnew;
    while (*pp)
    {
        if (val < (*pp)->freq)
            break;
        else
            pp = &((*pp)->next);
    }
    pnew = (NODE*)malloc(sizeof(NODE));
    pnew->freq = val;
    pnew->symb = symb;
    strcpy(pnew->code, "");
    pnew->next = *pp;
    pnew->isSymb = isSymb;
    pnew->left = NULL;
    pnew->right = NULL;
    *pp = pnew;
}
 
void Add2list(NODE** pphead, NODE* pnew)
{
    NODE** pp = pphead;
    while (*pp)
    {
        if (pnew->freq < (*pp)->freq)
            break;
        else
            pp = &((*pp)->next);
    }
    pnew->next = *pp;
    *pp = pnew;
}
 
void InputFile()
{
    FILE* input = fopen(Input, "rb");
    if (!input)
    {
        printf("Error!");
        return;
    }
    fseek(input, 0L, SEEK_END);
    long length = ftell(input);
    fseek(input, 0, SEEK_SET);
    for (int i = 0; i < length; ++i)
    {
        freq[(int)fgetc(input)]++;
    }
    for (int i = 0; i < 1000; i++)
    {
        if (freq[i] != 0)
            add2list(&head, freq[i], (unsigned char)i, 1);
    }
    fclose(input);
}
 
NODE* MakeNodeFromNode(NODE* left,NODE* right)
{
    NODE* res = (NODE*)malloc(sizeof(NODE));
    res->freq = left->freq + right->freq;
    res->isSymb = 0;
    res->symb = 0;
    res->left = left;
    res->right = right;
    res->next = 0;
    return res;
}
 
NODE* MakeTreeFromList(NODE* head)
{
    while (head && head->next)
    {
        NODE* left = head;
        NODE* right = head->next;
        Add2list(&(head->next->next), MakeNodeFromNode(left, right));
        head = head->next->next;
    }
    return head;
}
 
void MakeHuffTree(NODE* head)
{
    //printf("%s\n", head->code);
    if (head->isSymb)
    {
        for (int i = 0; i < strlen(head->code); i++)
            codehuff[head->symb][i] = head->code[i];
        return;
    }
    if (head->left)
    {
        strcpy(head->left->code, head->code);
        strcat(head->left->code, "0");
        MakeHuffTree(head->left);
    }
    if (head->right)
    {
        strcpy(head->right->code, head->code);
        strcat(head->right->code, "1");
        MakeHuffTree(head->right);
    }
}
 
void Encode()
{
 
    FILE* input = fopen(Input, "rb");
    FILE* output = fopen(Encoded, "wb");
    fseek(input, 0L, SEEK_END);
    long length = ftell(input);
    fseek(input, 0, SEEK_SET);
    char str[1000] = { 0 };
    char o[1000] = { 0 };
    int j = 0;
    for (int ii = 0; ii < length; ii++)
    {
        char jj[1000] = { 0 };
        strcpy(jj, codehuff[fgetc(input)]);
        // printf("%s", jj);
        for (int i = 0; i < strlen(jj); i++)
        {
            // printf("%s",jj);
            str[j++] = jj[i];
            if (j == 8)
            {
                fprintf(output, "%c", strtol(str, NULL, 2));
                j = 0;
            }
        }
    }
    if (j > 0)
    {
        for (int i = 0; i <= j; i++)
        {
            o[i] = str[i];
        }
        for (int i = j + 1; j < 8; j++)
            o[i] = 0;
    }
    fprintf(output, "%c", strtol(str, NULL, 2));
    fclose(input);
    fclose(output);
}
 
void Decode(NODE* root)
{
    FILE* input = fopen(Encoded, "rb");
    FILE* decode = fopen(Decoded, "wb");
    fseek(input, 0L, SEEK_END);
    long length = ftell(input);
    fseek(input, 0, SEEK_SET);
    char c = 0, bit;
    char mask = 1 << 7;
    head = root;
    for (int i = 0; i < length; i++)
    {
        c = fgetc(input);
        for (int i = 0; i < 8; i++)
        {
 
            bit = c & mask;
            c = c << 1;
            if (bit == 0)
            {
                head = head->left;
            }
            else
            {
                head = head->right;
            }
            if (head->left == NULL && head->right == NULL)
            {
                fprintf(decode, "%c", head->symb);
                head = root;
            }
        }
    }
    fclose(decode);
    fclose(input);
}
 
void print(NODE* phead)
{
    NODE* p = head;
    while (p)
    {
        printf("%d %c\n", p->freq, p->symb);
        p = p->next;
    }
}
 
int main()
{
    printf("Input filename to encode - ");
    scanf("%s", Input);
    printf("Input filename to write encoded file - ");
    scanf("%s", Encoded);
    printf("Input filename to write decoded file - ");
    scanf("%s", Decoded);
    InputFile();
    head = MakeTreeFromList(head);
    strcpy(head->code, "`");
    MakeHuffTree(head);
    for (int i = 0; i < 255; i++)
    {
        if (strlen(codehuff[i]) >= 1)
            printf("%c - %s\n", i, codehuff[i]);
    }
    Encode();
    Decode(head);
    return 0;
}