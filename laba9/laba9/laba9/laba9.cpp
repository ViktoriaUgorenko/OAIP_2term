#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
using namespace std;

const unsigned int NAME_SIZE = 256;
const unsigned int CITY_SIZE = 256;

struct Address
{
    string name;
    string city;
    Address* next;
    Address* prev;
    Address(string name, string city) : name(name), city(city), next(nullptr), prev(nullptr) {}
};

void insert(Address* e, Address** phead, Address** plast);
Address* setElement();
void outputList(Address** phead, Address** plast);
void delet(string name, Address** phead, Address** plast);
void find(string name, Address** phead);
void writeToFile(Address** phead);
void readFromFile(Address** phead, Address** plast);
void addLBegin(Address** head, Address** plast, Address* L);
void createListL(Address** Lhead, Address** Llast);

int main()
{
    string s;
    int c;
    string dname;
    string fname;
    setlocale(LC_CTYPE, "Rus");
    Address* head = nullptr;
    Address* last = nullptr;
    Address* Lhead = nullptr;
    Address* Llast = nullptr;
    short choose = 0;

    while (choose != 8)
    {
        cout << "\n�������� ��������:\n1 � ���� ��������;\n2 � ����� ������;\n3 � �������� ��������;\n4 � ����� ��������;"
            "\n5 � ������ � ����;\n6 � ����� �� �����;\n7 � ������� ���������� � ������ ������ ���� ��������� ���������� ������ L;\n8 � ����� �� ���������.\n";
        do
        {
            getline(cin, s);
        } while (s.find_first_not_of("12345678") != string::npos);

        c = stoi(s);

        switch (c)
        {
        case 1:
            insert(setElement(), &head, &last);
            break;
        case 2:
            outputList(&head, &last);
            break;
        case 3:
            cout << "������� ���: ";
            getline(cin, dname);
            delet(dname, &head, &last);
            break;
        case 4:
            cout << "������� ���: ";
            getline(cin, fname);
            find(fname, &head);
            break;
        case 5:
            writeToFile(&head);
            break;
        case 6:
            readFromFile(&head, &last);
            break;
        case 7:
            createListL(&Lhead, &Llast);
            addLBegin(&head, &last, Lhead);
            break;
        case 8:
            cout << "�� ��������!\n";
            exit(0);
        }
    }

    return 0;
}

void insert(Address* e, Address** phead, Address** plast)
{
    if (*plast == nullptr)
    {
        *plast = e;
        *phead = e;
    }
    else
    {
        (*plast)->next = e;
        e->prev = *plast;
        *plast = e;
    }
}

Address* setElement()
{
    string cho1, cho2;
    cout << "������� ���: ";
    getline(cin, cho1);
    cout << "������� �����: ";
    getline(cin, cho2);

    return new Address(cho1, cho2);
}

void outputList(Address** phead, Address** plast)
{
    Address* t = *phead;
    while (t)
    {
        cout << "���: " << t->name << ", �����: " << t->city << endl;
        t = t->next;
    }
}

void delet(string name, Address** phead, Address** plast)
{
    Address* t = *phead;
    while (t)
    {
        if (name == t->name)
        {
            // ���� ��������� ������� ������ � ������
            if (*phead == t)
            {
                *phead = t->next;
                if (*phead)
                    (*phead)->prev = nullptr;
                else
                    *plast = nullptr;
            }
            else
            {
                t->prev->next = t->next;
                if (t->next)
                    t->next->prev = t->prev;
                else
                    *plast = t->prev;
            }
            Address* temp = t;
            t = t->next;
            delete temp;
        }
        else
        {
            t = t->next;
        }
    }
    cout << "��� �������� � ������ " << name << " �������." << endl;
}

void find(string name, Address** phead)
{
    Address* t = *phead;
    while (t)
    {
        if (name == t->name)
            cout << "���: " << t->name << ", �����: " << t->city << endl;
        t = t->next;
    }
}

void writeToFile(Address** phead)
{
    Address* t = *phead;
    ofstream file1("output.txt");
    if (!file1)
    {
        cerr << "������ �������� �����" << endl;
        return;
    }
    cout << "���������� � ����" << endl;
    while (t)
    {
        file1 << t->name << "\t" << t->city << endl;
        t = t->next;
    }
    file1.close();
}

void readFromFile(Address** phead, Address** plast)
{
    while (*phead)
    {
        *plast = (*phead)->next;
        delete* phead;
        *phead = *plast;
    }
    *phead = *plast = nullptr;

    string name, city;
    ifstream file1("output.txt");
    if (!file1)
    {
        cerr << "������ �������� �����" << endl;
        return;
    }
    cout << "������ �� �����" << endl;
    while (file1 >> name >> city)
    {
        insert(new Address(name, city), phead, plast);
    }
    file1.close();
}

void addLBegin(Address** head, Address** plast, Address* L)
{
    if (L == nullptr)
    {
        cout << "������ L ����." << endl;
        return;
    }

    Address* lastL = L;
    while (lastL->next)
        lastL = lastL->next;

    if (*head == nullptr)
    {
        *head = L;
        *plast = lastL;
    }
    else
    {
        lastL->next = *head;
        (*head)->prev = lastL;
        *head = L;
    }

    cout << "�������� ������ L ��������� � ������ ������." << endl;
}

void createListL(Address** Lhead, Address** Llast)
{
    string cho1, cho2;
    cout << "�������� ������ L.\n";
    cout << "������� ���������� ��������� � ������ L: ";
    int n;
    cin >> n;
    cin.ignore(); // ������� ����� �����
    for (int i = 0; i < n; ++i)
    {
        cout << "������� ��� �������� " << i + 1 << ": ";
        getline(cin, cho1);
        cout << "������� ����� �������� " << i + 1 << ": ";
        getline(cin, cho2);
        insert(new Address(cho1, cho2), Lhead, Llast);
    }
    cout << "������ ������ L.\n";
}
