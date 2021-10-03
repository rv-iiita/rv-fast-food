// Author : Rituvendra Singh
// A Food order management system using C

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct node *headc = NULL, *newnode, *tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;

void adminmenu()
{
    printf("\n\t\t\t\t\t\t\t1. View total sales\n");
    printf("\t\t\t\t\t\t\t2. Add new items in the order menu\n");
    printf("\t\t\t\t\t\t\t3. Delete items from the order menu\n");
    printf("\t\t\t\t\t\t\t4. Display order menu\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

void customermenu()
{
    printf("\n\t\t\t\t\t\t\t1. Place your order\n");
    printf("\t\t\t\t\t\t\t2. View your ordered items\n");
    printf("\t\t\t\t\t\t\t3. Delete an item from order\n");
    printf("\t\t\t\t\t\t\t4. Display final bill\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

struct node* createadmin(struct node *head, int data, char foodname[25], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->foodname, foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;

    if (temp == NULL)
        heada = taila = newnode;
    else
    {
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newnode;
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}

struct node* createcustomer(struct node *head, int data, int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));

    struct node *temp1 = heada;
    int flag = 0;
    while (temp1 != NULL)
    {
        if (temp1->data == data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if (flag == 1)
    {
        newnode->data = data;
        newnode->price = quantity * (temp1->price);
        newnode-> quantity = quantity;
        strcpy(newnode->foodname, temp1->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if (temp == NULL)
            headc = tailc = newnode;
        else
        {
                        while (temp->next != NULL)
                temp = temp->next;

            temp->next = newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }


    }
    else
    {
        printf("\n\t\t\t\t\t\t\tThis item is not present in the menu!\n");
    }
    return headc;
}

void displayList(struct node *head)
{
    struct node *temp1 = head;
    if (temp1 == NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
    }
    else
    {
        printf("\n");
        while (temp1 != NULL)
        {
            if (temp1->quantity == 0)
                printf("\t\t\t\t\t\t\t%d\t%s\t%0.2f\n", temp1->data, temp1->foodname, temp1->price);
            else
            {
                printf("\t\t\t\t\t\t\t%d\t%s\t%d\t%0.2f\n", temp1->data, temp1->foodname, temp1->quantity, temp1->price);
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }

}

struct node* totalsales(int data, int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = heada;
    while (temp1->data != data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity * (temp1->price);
    newnode-> quantity = quantity;
    strcpy(newnode->foodname, temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if (temp == NULL)
        head_s = newnode;
    else
    {
        while (temp->next != NULL)
        {
            if (temp->data == data)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 1)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next = newnode;
        }
    }

    return head_s;
}

void calculatetotsales()
{
    struct node *temp = headc;
    while (temp != NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp = temp->next;
    }
}

struct node* delete(int data, struct node *head, struct node* tail)
{
    if (head == NULL)
    {
        printf("\n\t\t\t\t\t\t\tList is empty\n");
    }
    else
    {
        struct node* temp;
        if (data == head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if (data == tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while (data != temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}
