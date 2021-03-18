#include <iostream>

using namespace std;

struct Node {
    int value;
    struct Node* next;
};


/*Создаём массив для тестирования*/
Node* first = NULL;

void In(Node** first) {
    *first = new Node;
    (*first)->value = rand() % 10 + 1;
    (*first)->next = NULL;

    Node* end = *first;
    for (int i = 0; i < 9; i++)
    {
        end->next = new Node;
        end = end->next;
        end->value = rand() % 10 + 1;
        end->next = NULL;
    }
}
void Print(Node* b) {

    Node* print = b;

    while (print) {
        cout << print->value << ' ';
        print = print->next;

    }
    cout << '\n';
}
/*-------------*/


void push_left(Node** head, int value) /*Первая функция*/
{
    Node* a = (Node*)malloc(sizeof(Node));
    a->value = value;
    a->next = *head;
    *head = a;
}


void clear_list(Node** head) /*Вторая функция*/
{
    while ((*head)->next != NULL)
    {
        Node* i = *head;
        (*head) = (*head)->next;
        free(i);
    }
    free(*head);
    *head = NULL;
}


int pop(Node** head, int index) /*Третья функция*/
{
    if (index == 0)
    {
        int a = (*head)->value;
        Node* i = (*head);
        (*head) = (*head)->next;
        free(i);
        return a;
    }

    if (index != 0)
    {
        Node* ind_i = *head;
        for (int i = 0; i < index; ++i)
        {
            if (ind_i->next != NULL)
            {
                if (i == index - 1)
                {
                    int num = (ind_i->next)->value;
                    Node* a = ind_i->next;
                    ind_i->next = ind_i->next->next;
                    free(a);
                    return num;
                }
                ind_i = ind_i->next;
            }
        }
    }
}


void remove(Node** head, int value) /*Четвёртая функция*/
{
    Node* ind_i = *head;
    if ((*head)->value == value)
    {
        Node* a = *head;
        *head = (*head)->next;
        free(a);
    }
    else
    {
        while (ind_i->next != NULL)
        {
            if ((ind_i->next)->value == value)
            {
                Node *a = ind_i->next;
                ind_i->next = ind_i->next->next;
                free(a);
                break;
            }
            ind_i = ind_i->next;
        }
    }
}

void remove_all(Node** head, int value) /*Пятая функция*/
{
    if ((*head)->value == value)
    {
        Node* a = *head;
        *head = (*head)->next;
        free(a);
    }

    Node* ind_i = *head;
    while (ind_i->next != NULL)
    {
        if ((ind_i->next)->value == value)
        {
            Node* a = ind_i->next;
            ind_i->next = ind_i->next->next;
            free(a);
        }
        else
        {
            ind_i = ind_i->next;
        }
    }
}

void replace_all(Node* head, int old_value, int new_value) /*Шестая функция*/
{
    Node* ind_i = head;
    while (ind_i != NULL)
    {
        if (ind_i->value == old_value)
        {
            ind_i->value = new_value;
        }
        ind_i = ind_i->next;
    }
}

bool unique_check(Node* head, int value)
{
    Node* ind_i = head;
    while (ind_i != NULL)
    {
        if (ind_i->value == value)
        {
            return false;
        }
        ind_i = ind_i->next;
    }
    return true;
}

int unique(Node* head) /*Седьмая функция*/
{
    int count = 0;
    Node* first = (Node*)malloc(sizeof(Node));
    first->value = head->value;
    first->next = NULL;
    Node* ind_i = head->next;
    free(head);

    while (ind_i != NULL)
    {
        if (unique_check(first, ind_i->value))
        {
            push_left(&first, ind_i->value);
        }
        Node* a = ind_i;
        ind_i = ind_i->next;
        free(a);
    }

    ind_i = first;
    while (ind_i != NULL)
    {
        ind_i = ind_i->next;
        count += 1;
    }
    return count;
}

void reverse(Node** head) /*Восьмая функция*/
{
    Node* first = (Node*)malloc(sizeof(Node));
    first->value = (*head)->value;
    first->next = NULL;
    Node* ind_i = (*head)->next;
    free(*head);

    while (ind_i != NULL)
    {
        push_left(&first, ind_i->value);
        Node* a = ind_i;
        ind_i = ind_i->next;
        free(a);
    }
    *head = first;
}

int main()
{
    /*Создаём массив для тестирования*/
    setlocale(LC_ALL, "rus");
    Node* current = first;
    In(&first);
    Print(first);
    /*-------------*/

    push_left(&first, 150); /*Первая функция*/
    Print(first);
    cout << '\n';

    clear_list(&first); /*Вторая функция*/
    Print(first);
    cout << '\n';

    /*Создаём массив для тестирования*/
    In(&first);
    Print(first);
    /*-------------*/

    cout << pop(&first, 10) << '\n'; /*Третья функция*/
    Print(first);
    cout << '\n';

    /*Создаём массив для тестирования*/
    In(&first);
    Print(first);
    /*-------------*/

    remove(&first, 3); /*Четвёртая функция*/
    Print(first);
    cout << '\n';

    /*Создаём массив для тестирования*/
    In(&first);
    Print(first);
    /*-------------*/

    remove_all(&first, 8); /*Пятая функция*/
    Print(first);
    cout << '\n';

    /*Создаём массив для тестирования*/
    In(&first);
    Print(first);
    /*-------------*/

    replace_all(first, 2, 228); /*Шестая функция*/
    Print(first);
    cout << '\n';

    /*Создаём массив для тестирования*/
    In(&first);
    Print(first);
    /*-------------*/

    cout << unique(first) << '\n'; /*Седьмая функция*/

    cout << '\n';
    /*Создаём массив для тестирования*/
    In(&first);
    Print(first);
    /*-------------*/

    reverse(&first); /*Восьмая функция*/
    Print(first);

    return 0;
}
