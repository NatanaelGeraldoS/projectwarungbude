#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../controller/controller.h"
char arr[15][25] = {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "desember"};
void printlinkedlist()
{
    curr = head;
    while (curr)
    {
        printf("%d %s %d - %s\n", curr->day, arr[curr->month - 1], curr->year, curr->name);
        curr = curr->next;
    }
}
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int temp = n;
    while (n--)
    {
        int day;
        char bulan[25];
        int tahun;
        char name[255];
        int gantibulan;

        scanf("%d %s %d - %[^\n]", &day, bulan, &tahun, name);
        getchar();
        for (int i = 0; i < 12; i++)
        {
            if (strcmp(arr[i], bulan) == 0)
            {
                gantibulan = i + 1;
                break;
            }
        }
        push(day, gantibulan, tahun, name);
    }
    for (int i = 0; i < m; i++)
    {
        popHead();
    }
    printf("Need %d more cure\n", temp - m);
    printlinkedlist();
}