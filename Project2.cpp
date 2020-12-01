#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const char *detectOS()
{
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Other";
#endif
};

//struct
int jlmdish = 0;

struct Menu
{
    char nama[255];
    int qty;
    int price;
    Menu *next, *previous;
} * head, *tail, *curr;

const int MAX_ELEMENT = 25;
const int MAX_ORDER = 150;
struct Order
{
    char nama[255];
    int qty;
    int price;
    Order *next, *previous;
} * newOrder, *currOrder, *delOrder;

struct Node
{
    char name[255];
    Order *headOrder, *tailOrder;
    Node *next;
} * headNode[MAX_ELEMENT], *tailNode[MAX_ELEMENT];

//declare function
void menu(), exitProgram(), addDish(), removeDish();
void addCustomer(), viewWarteg(), searchCustomer(), order(), payment();
int main()
{
    menu();
    return 0;
}

void menu()
{
    time_t t;
    struct tm *area;
    tzset();
    t = time(NULL);
    area = localtime(&t);

    int pilihmenu;
    system("cls");
    printf("%s\n", detectOS());
    printf("%s\n", asctime(area));
    printf("1. Add Dish\n");
    printf("2. Remove dish\n");
    printf("3. Add Customer\n");
    printf("4. Search Customer\n");
    printf("5. View Warteg\n");
    printf("6. Order\n");
    printf("7. Payment\n");
    printf("8. Exit Warteg\n");
    do
    {
        printf(">>");
        scanf("%d", &pilihmenu);
        getchar();
    } while (pilihmenu <= 0 || pilihmenu > 8);
    switch (pilihmenu)
    {
    case 1:
        addDish();
        break;
    case 2:
        removeDish();
        break;
    case 3:
        addCustomer();
        break;
    case 4:
        searchCustomer();
        break;
    case 5:
        viewWarteg();
        break;
    case 6:
        order();
        break;
    case 7:
        payment();
        break;
    case 8:
        exitProgram();
        break;
    }
}
Menu *createMenu(char *nama, int price, int qty)
{
    Menu *temp = (Menu *)malloc(sizeof(Menu));
    strcpy(temp->nama, nama);
    temp->price = price;
    temp->qty = qty;
    temp->next = temp->previous = NULL;
    return temp;
}

void addMenu(char *nama, int price, int qty)
{
    Menu *temp = createMenu(nama, price, qty);
    if (!head) //node=0
    {
        head = tail = temp;
    }
    else
    {
        tail->next = temp;
        temp->previous = tail;
        tail = temp;
    }
}
void printing()
{
    curr = head;
    while (curr)
    {
        printf("nama : %s\n", curr->nama);
        printf("price : %d\n", curr->price);
        printf("QTY : %d\n", curr->qty);
        curr = curr->next;
    }
}
void addDish()
{
    char nama[255];
    int qty;
    int price;
    int lower;
    system("cls");
    do
    {
        lower = 0;
        printf("Insert the name of the dish[Lowercase letters]: ");
        scanf("%[^\n]", nama);
        getchar();
        for (int i = 0; nama[i] != '\0'; i++)
        {
            if ((nama[i] >= 'a' && nama[i] <= 'z') || nama[i] == ' ')
            {
                lower++;
            }
        }
    } while (strlen(nama) != lower);
    do
    {
        printf("Insert the price of the dish[1000...50000]: ");
        scanf("%d", &price);
        getchar();
    } while (price < 1000 || price > 50000);

    do
    {
        printf("Insert the quantity of the dish[1...999]: ");
        scanf("%d", &qty);
        getchar();
    } while (qty < 1 || qty > 999);
    addMenu(nama, price, qty);
    printf("The dish has been added!\n");
    printf("Press enter to continue...");
    getchar();
    jlmdish++;
    menu();
}

int search(char *nama)
{
    curr = head;
    while (curr && strcmp(curr->nama, nama) != 0)
    {
        curr = curr->next;
    }
    if (!curr)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void popHead(char *nama)
{
    if (head && head == tail)
    {
        head = tail = NULL;
        free(head);
    }
    else
    {
        Menu *newHead = head->next;
        head->next = newHead->previous = NULL;
        free(head);
        head = newHead;
    }
}
void popTail(char *nama)
{
    if (head && head == tail)
    {
        head = tail = NULL;
        free(head);
    }
    else
    {
        Menu *newTail = tail->previous;
        tail->previous = newTail->next = NULL;
        free(tail);
        tail = newTail;
    }
}
void popMid(char *nama)
{
    //10 20 30 40 50, mau hapus 30
    if (!head)
    {
        return;
    }
    else if (strcmp(head->nama, nama) == 0)
    {
        popHead(nama);
    }
    else if (strcmp(tail->nama, nama) == 0)
    {
        popTail(nama);
    }
    else
    {
        curr = head;
        while (curr && strcmp(curr->nama, nama) != 0)
        {
            curr = curr->next;
        }
        curr->previous->next = curr->next;
        curr->next->previous = curr->previous;
        curr->next = curr->previous = NULL;
        free(curr);
    }
}

void removeDish()
{
    curr = head;
    int number = 1;
    char nama[255];
    int check;
    system("cls");
    printf("        Bude's Menu\n");
    printf("==============================\n");
    printf("No.     Name    Quantity Price\n");
    while (curr)
    {
        printf("%d. ", number);
        printf("%s ", curr->nama);
        printf("%03d ", curr->qty);
        printf("Rp%d\n", curr->price);
        curr = curr->next;
        number++;
    }
    printf("==============================\n");
    if (head)
    {
        do
        {
            printf("Insert dish's name to be deleted: ");
            scanf("%[^\n]", nama);
            getchar();
            check = search(nama);
        } while (check == 0);
        jlmdish--;
        popMid(nama);
        printf("The dish has been removed!\n");
    }
    printf("Press enter to continue...");
    getchar();
    menu();
}

Node *createNode(char *name)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    strcpy(temp->name, name);
    temp->next = NULL;
    temp->headOrder = temp->tailOrder = NULL;
    return temp;
}
unsigned long DJB2(char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % MAX_ELEMENT;
}
void insert(char *str)
{
    int index = DJB2(str);

    if (headNode[index])
    { // cek apakah dia sudah terisi
        Node *temp = createNode(str);
        tailNode[index]->next = temp;
        tailNode[index] = temp;
    }
    else
    { // cek apakah dia belum terisi
        headNode[index] = tailNode[index] = createNode(str);
    }
}

void addCustomer()
{
    char pembeli[255];
    int space = 1;
    system("cls");
    do
    {
        space = 1;
        printf("Insert the customer's name[without space]: ");
        scanf("%[^\n]", pembeli);
        getchar();
        for (int i = 0; pembeli[i] != '\0'; i++)
        {
            if (pembeli[i] == ' ')
            {
                space = 0;
                break;
            }
        }
    } while (space == 0);

    insert(pembeli);
    printf("Customer has been added!\n");
    printf("Press enter to continue...");
    getchar();
    menu();
}

int ceknama(char *nama)
{
    int index = DJB2(nama);
    if (headNode[index])
    {
        Node *curr = headNode[index];
        while (curr && strcmp(curr->name, nama) != 0)
        {
            curr = curr->next;
        }
        if (!curr)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

void searchCustomer()
{
    char nama[255];
    int flag, space;
    system("cls");
    do
    {
        printf("Insert the customer's name to be searched: ");
        scanf("%[^\n]", nama);
        getchar();
        for (int i = 0; nama[i] != '\0'; i++)
        {
            if (nama[i] == ' ')
            {
                space = 0;
                break;
            }
        }
    } while (space == 0);

    flag = ceknama(nama);
    if (flag == 0)
    {
        printf("%s is not present\n", nama);
    }
    else
    {
        printf("%s is present\n", nama);
    }
    printf("Press enter to continue...");
    getchar();
    menu();
}

void viewWarteg()
{
    printf("Customer's List\n");

    for (int i = 0; i < MAX_ELEMENT; i++)
    {
        if (headNode[i])
        {
            Node *curr = headNode[i];
            while (curr)
            {
                printf("%d. ", i);
                printf("%s\n", curr->name);
                curr = curr->next;
            }
        }
    }
    printf("Press enter to continue...");
    getchar();
    menu();
}

int searchnnc(char *nama, int count)
{
    curr = head;
    while (curr && strcmp(curr->nama, nama) != 0)
    {
        curr = curr->next;
    }
    if (!curr || curr->qty < count)
    {
        return 0;
    }
    else
    {
        curr->qty -= count;
        return curr->price;
    }
}

Order *createorder(char *nama, int total, int harga)
{
    Order *temp = (Order *)malloc(sizeof(Order));
    strcpy(temp->nama, nama);
    temp->qty = total;
    temp->price = total * harga;
    temp->next = temp->previous = NULL;
    return temp;
}

void input(char *pembeli, char *nama, int total, int harga)
{
    int index = DJB2(pembeli);
    Node *curr1 = headNode[index];
    while (curr1 && strcmp(curr1->name, pembeli) != 0)
    {
        curr1 = curr1->next;
    }
    Order *temp3 = createorder(nama, total, harga);
    Order *posisi = curr1->headOrder;
    if (!posisi)
    {
        curr1->headOrder = curr1->tailOrder = temp3;
    }
    else
    {
        curr1->tailOrder->next = temp3;
        temp3->previous = curr1->tailOrder;
        curr1->tailOrder = temp3;
    }
}
void order()
{
    char nama[255];
    int inlist = 0;
    int dish = 0;
    char namadish[255];
    int indish = 0;
    int total = 0;
    int inpesan = 0;
    do
    {
        printf("Insert the customer's name: ");
        scanf("%[^\n]", nama);
        getchar();
        inlist = ceknama(nama);

    } while (inlist == 0);
    do
    {
        printf("Insert the amount of dish: ");
        scanf("%d", &dish);
        getchar();
    } while (dish < 1 || dish > jlmdish);
    for (int i = 0; i < dish; i++)
    {
        indish = 1;
        do
        {
            indish = 1;
            printf("[%d] Insert the dish's name and quantity: ", i + 1);
            scanf("%[^\n]", namadish);
            getchar();
            for (int i = strlen(namadish) - 1; i >= 0; i--)
            {
                if (namadish[i] == 'x' && namadish[i + 1] >= '0' && namadish[i + 1] <= '9')
                {
                    int index = i + 1;
                    total = 0;
                    while (index < strlen(namadish))
                    {
                        if (namadish[index] >= '0' && namadish[index] <= '9')
                        {
                            total = total * 10 + (namadish[index] - '0');
                            index++;
                        }
                        else
                        {
                            indish = 0;
                            break;
                        }
                    }
                    namadish[i - 1] = '\0';
                    break;
                }
            }
            if (indish != 0)
            {
                indish = searchnnc(namadish, total);
            }
        } while (indish == 0);
        input(nama, namadish, total, indish);
    }
    printf("Order Success!\n");
    printf("Press enter to continue...\n");
    getchar();
    menu();
}
void printingorder(int menu)
{
    Node *curr1 = headNode[menu];
    if (curr)
    {
        int jlm = 1;
        Order *posisi = curr1->headOrder;
        printf("%s\n", curr1->name);
        int total = 0;
        while (posisi)
        {
            printf("[%d] ", jlm);
            printf("%s", posisi->nama);
            printf(" x%d\n", posisi->qty);
            total += posisi->price;
            posisi = posisi->next;
            jlm++;
        }
        printf("Total: Rp%d\n", total);
    }
    else
    {
        return;
    }
}

int check(int menu)
{
    Node *curr1 = headNode[menu];
    if (curr1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void remove(int menu)
{
    Node *curr1 = headNode[menu];
    if (curr1->next)
    {
        headNode[menu] = curr1->next;
        curr1 = NULL;
        free(curr1);
    }
    else
    {
        headNode[menu] = NULL;
        curr1 = NULL;
        free(curr1);
    }
}

void payment()
{
    int menu1 = 0;
    int found;
    do
    {
        printf("Insert the customer's index: ");
        scanf("%d", &menu1);
        getchar();
        found = check(menu1);
    } while (found == 0);
    printingorder(menu1);
    remove(menu1);
    printf("Press enter to continue...");
    getchar();
    menu();
}

void exitProgram()
{
    FILE *fp = fopen("splash-screen.txt", "r");
    char type[500];
    system("cls");
    while (fscanf(fp, "%[^\n]\n", type) != EOF)
    {
        printf("%s\n", type);
    }
    fclose(fp);
    printf("Please expand your terminal to full screen!\n");
    printf("Press enter to continue...\n");
    getchar();
    return;
}