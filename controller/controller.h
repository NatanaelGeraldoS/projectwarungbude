#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../models/model.h"

Node *createNode(int day, int bulan, int tahun, char *name)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->day = day;
    temp->month = bulan;
    temp->year = tahun;
    strcpy(temp->name, name);
    temp->next = temp->prev = NULL;
    return temp;
}
void push(int day, int bulan, int tahun, char *name)
{
    Node *temp = createNode(day, bulan, tahun, name);

    if (!head)
    {
        head = temp;
        tail = temp;
    }
    else if (tahun < head->year)
    {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
    else if (tahun == head->year)
    {
        if (bulan > head->month)
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
        else if (bulan == head->month)
        {
            if (day > head->day)
            {
                temp->next = head;
                head->prev = temp;
                head = temp;
            }
        }
    }
    else if (tahun > tail->year)
    {
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }
    else if (tahun == tail->year)
    {
        if (bulan < head->month)
        {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
        else if (bulan == head->month)
        {
            if (day < head->day)
            {
                temp->prev = tail;
                tail->next = temp;
                tail = temp;
            }
        }
    }
    else
    {
        Node *curr = head;
        while (curr && ((curr->next->year < temp->year) || (curr->next->year == temp->year && curr->next->month > temp->month) || (curr->next->year == temp->year && curr->next->month == temp->month && curr->next->day > temp->day)))
        {
            curr = curr->next;
        }

        curr->next->prev = temp;
        temp->next = curr->next;
        curr->next = temp;
        temp->prev = curr;
    }
}

void popHead()
{
    if (head && head == tail)
    {
        head = tail = NULL;
        free(head);
    }
    else
    {
        Node *newHead = head->next;
        head->next = newHead->prev = NULL;
        free(head);
        head = newHead;
    }
}