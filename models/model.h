struct Node
{
    char name[255];
    int day;
    int month;
    int year;
    Node *prev, *next;
} * head, *tail, *curr;
