#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10
#define M 6

typedef struct Node
{
    char surname[20];
    char name[10];
    int  day, month, year;
    int m1, m2, m3, m4, m5, m6;
    double rank;
    struct Node* next;
} Student;


// додає студента в кінець списку
void add_to_end(Student** pphead, Student* pNewElement)
{
    Student* ptemp = *pphead;
    if (ptemp == NULL)
    {
        ptemp = pNewElement;
        *pphead = ptemp;
        ptemp->next = NULL;

    }
    else {
        while (ptemp->next != NULL)
        {
            ptemp = ptemp->next;
        }
        Student* pNewtemp = pNewElement;
        ptemp->next = pNewtemp;
        pNewtemp->next = NULL;

    }
}

// додає студента на конкретну позицію
int add_n(Student** pphead, Student* pNewElement, int pos)
{
    Student* pTemp = *pphead;

    int size = 0;

    while (pTemp != NULL) {
        pTemp = pTemp->next;
        size++;
    }
    pTemp = *pphead;

    if (*pphead != NULL) {
        if (pos < 0 || pos > size) {
            pos = size;
        }
        if (pos == 0) {
            Student* pNewtemp = pNewElement;
            pNewtemp->next = *pphead;
            *pphead = pNewtemp;
        }
        else {
            for (int i = 1; i < pos; i++) {
                pTemp = pTemp->next;
            }

            Student* pNewtemp = pNewElement;
            pNewtemp->next = pTemp->next;
            pTemp->next = pNewtemp;
        }
    }
    else {
        add_to_end(pphead, pNewElement);
    }
    return 0;
}

// видаляє студента з конкретної позиції
int delete_n(Student** pphead, int pos)
{
    Student* ptemp = *pphead;
    Student* pDeltemp;

    int size = 0;

    while (ptemp != NULL)
    {
        ptemp = ptemp->next;
        size++;
    }
    ptemp = *pphead;


    if (pos < 0 || pos >= size)
    {
        return -1;
    }
    if (pos == 0)
    {
        pDeltemp = *pphead;
        *pphead = pDeltemp->next;
        free(pDeltemp);
    }
    else {
        for (int i = 1; i < pos; i++)
        {
            ptemp = ptemp->next;
        }

        pDeltemp = ptemp->next;
        ptemp->next = pDeltemp->next;
        free(pDeltemp);
    }
    return 0;
}

// зчитує з файлу(.txt) дані про студентів
int read_students(const char* filename, Student** pphead)
{
    Student* ptemp = (Student*)malloc(sizeof(Student));
    ptemp->next = NULL;

    FILE* file = fopen(filename, "r");
    int i = 0;
    while (fscanf(file, "%s %s %d.%d.%d %d,%d,%d,%d,%d,%d",

        ptemp->surname,
        ptemp->name,
        &ptemp->day,
        &ptemp->month,
        &ptemp->year,
        &ptemp->m1,
        &ptemp->m2,
        &ptemp->m3,
        &ptemp->m4,
        &ptemp->m5,
        &ptemp->m6) == 11)
    {
        ptemp->rank = (double)(ptemp->m1 + ptemp->m2 + ptemp->m3 + ptemp->m4 +
            ptemp->m5 + ptemp->m6) / M;
        add_to_end(pphead, ptemp);
        ptemp = (Student*)malloc(sizeof(Student));
        ++i;
    }
    fclose(file);
    return i;
}

// друкує список студентів
void print_students(Student* phead)
{
    Student* ptemp = phead;

    printf("List of students:\n");
    printf("|  surname   |  name   |   birth   |    marks    | rank |\n");
    while (ptemp != NULL)
    {
        printf("| %-10s | %-7s | %d.%d.%d | %d,%d,%d,%d,%d,%d | %.2lf |\n",
            ptemp->surname, ptemp->name, ptemp->day,
            ptemp->month, ptemp->year,
            ptemp->m1, ptemp->m2, ptemp->m3,
            ptemp->m4, ptemp->m5, ptemp->m6, ptemp->rank);

        ptemp = ptemp->next;
    }
    printf("\n");

}

// шукає у списку студентів тих, хто має дві 2
int find_2(Student** ppHead)
{
    int pos = 0;
    int count = 0;
    Student* pTemp = *ppHead;

    while (pTemp != NULL) {
        if (pTemp->m1 == 2)
            count++;
        if (pTemp->m2 == 2)
            count++;
        if (pTemp->m3 == 2)
            count++;
        if (pTemp->m4 == 2)
            count++;
        if (pTemp->m5 == 2)
            count++;
        if (pTemp->m6 == 2)
            count++;

        if (count == 2)    return pos;
        pTemp = pTemp->next;
        pos++;
    }

    return -1;
}

// вилучає студентів з двома оцінками 2
void remove_2(Student** ppHead)
{
    int pos = find_2(ppHead);
    while (pos != -1)
    {
        delete_n(ppHead, pos);
        pos = find_2(ppHead);
    }
}

int main()
{
    Student* phead = NULL;
    read_students("students.txt", &phead);
    print_students(phead);
    remove_2(&phead);
    print_students(phead);
   

    return 0;
}