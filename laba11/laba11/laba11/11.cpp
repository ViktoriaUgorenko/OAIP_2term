#include <iostream>
#include <Windows.h>
#include <cstring>  // ��� strcpy_s

using namespace std;

struct Tree
{
    int key;
    char text[100];
    Tree* Left, * Right;
};

Tree* makeTree(Tree* Root);
Tree* list(int i, char* s);
Tree* insertElem(Tree* Root, int key, char* s, int level);
Tree* search(Tree* n, int key);
Tree* delet(Tree* Root, int key);
void view(Tree* t, int level);
void delAll(Tree* t);
int depth(Tree* t);
int sumAtLevel(Tree* t, int level);
Tree* Root = NULL;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int key, choice;
    Tree* rc;
    char s[100];
    bool exit = false;
    while (!exit)
    {
        cout << "1-�������� ������\n2-���������� ��������\n3-����� �� �����\n4-�������� ��������\n5-����� ������\n6-������� ������\n7-����� �������� ������, ����������� �� ���� ������\n8-�����\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            Root = makeTree(Root);
            break;

        case 2:
            cout << "������� ����" << endl;
            cin >> key;
            cout << endl;
            cout << "������� �����" << endl;
            cin >> s;
            Root = insertElem(Root, key, s, 0);
            break;

        case 3:
            cout << "������� ����" << endl;
            cin >> key;
            rc = search(Root, key);
            if (rc != NULL)
                cout << "�����, ������� ��, ��� ���� �������, �������� " << rc->text << endl;
            break;

        case 4:
            cout << "������� ���� ��� ��������" << endl;
            cin >> key;
            Root = delet(Root, key);
            break;

        case 5:
            if (Root != NULL)
            {
                cout << "������ ��������� �� 90 ����. �����" << endl;
                view(Root, 0);
            }
            else
                cout << "������ �����!" << endl;
            break;

        case 6:
            delAll(Root);
            Root = NULL;
            break;

        case 7:
            int level;
            cout << "������� �������: ";
            cin >> level;
            int treeDepth;
            treeDepth = depth(Root);
            if (level >= treeDepth)
            {
                cout << "��������� ��� �� ������ " << level << endl;
            }
            else
            {
                cout << "����� �������� �� ������ " << level << " ����� " << sumAtLevel(Root, level) << endl;
            }
            break;

        case 8:
            exit = true;
            break;

        default:
            cout << "�������� �����. ���������� ��� ���." << endl;
        }
    }
    return 0;
}

Tree* makeTree(Tree* Root)
{
    int key;
    char s[100];
    cout << "����� �����-������������� �����\n\n";
    if (Root == NULL)
    {
        cout << "������� ����: ";
        cin >> key;
        cout << "������� �����: ";
        cin >> s;
        Root = list(key, s);
    }
    while (1)
    {
        cout << "\n������� ����: ";
        cin >> key;
        if (key < 0) break;
        cout << "������� �����: ";
        cin >> s;
        Root = insertElem(Root, key, s, 0);
    }
    return Root;
}

Tree* list(int i, char* s)
{
    Tree* t = new Tree;
    t->key = i;
    strcpy_s(t->text, s);
    t->Left = t->Right = NULL;
    return t;
}

Tree* insertElem(Tree* t, int key, char* s, int level)
{
    if (level >= 11) // ��������� ������� ���������
    {
        cout << "������� ������ ��������� 10 �������. ������� �� ����� ���� ��������." << endl;
        return t;
    }

    if (t == NULL)
    {
        return list(key, s);
    }
    if (key == t->key)
    {
        cout << "����� ���� ��� ����! " << endl;
        return t;
    }
    else if (key < t->key)
        t->Left = insertElem(t->Left, key, s, level + 1);
    else
        t->Right = insertElem(t->Right, key, s, level + 1);

    return t;
}

Tree* delet(Tree* Root, int key)
{
    Tree* Del, * Prev_Del, * R, * Prev_R;
    Del = Root;
    Prev_Del = NULL;
    while (Del != NULL && Del->key != key)
    {
        Prev_Del = Del;
        if (Del->key > key)
            Del = Del->Left;
        else
            Del = Del->Right;
    }
    if (Del == NULL)
    {
        cout << "\n���� ���� �� ������" << endl;
        return Root;
    }
    if (Del->Right == NULL)
        R = Del->Left;
    else
        if (Del->Left == NULL)
            R = Del->Right;
        else
        {
            Prev_R = Del;
            R = Del->Left;
            while (R->Right != NULL)
            {
                Prev_R = R;
                R = R->Right;
            }
            if (Prev_R == Del)
                R->Right = Del->Right;
            else
            {
                R->Right = Del->Right;
                Prev_R->Right = R->Left;
                R->Left = Prev_R;
            }
        }
    if (Del == Root)
        Root = R;
    else
        if (Del->key < Prev_Del->key)
            Prev_Del->Left = R;
        else
            Prev_Del->Right = R;
    int tmp = Del->key;
    cout << "\n����� ������� � ������ " << tmp << endl;
    delete Del;
    return Root;
}

Tree* search(Tree* n, int key)
{
    Tree* rc = n;
    if (rc != NULL)
    {
        if (key < n->key)
            rc = search(n->Left, key);
        else if (key > n->key)
            rc = search(n->Right, key);
    }
    else
        cout << "������ �������� �� ����������\n";
    return rc;
}

void view(Tree* t, int level)
{
    if (t)
    {
        view(t->Right, level + 1);
        for (int i = 0; i < level; i++)
            cout << "   ";
        int tm = t->key;
        cout << tm << ' ';
        cout << t->text << endl;
        view(t->Left, level + 1);
    }
}

void delAll(Tree* t)
{
    if (t != NULL)
    {
        delAll(t->Left);
        delAll(t->Right);
        delete t;
    }
}

int depth(Tree* t)
{
    if (t)
    {
        int leftDepth = depth(t->Left);
        int rightDepth = depth(t->Right);
        return max(leftDepth, rightDepth) + 1;
    }
    return 0;
}

int sumAtLevel(Tree* t, int level)
{
    if (t == NULL)
        return 0;
    if (level == 0)
        return t->key;
    return sumAtLevel(t->Left, level - 1) + sumAtLevel(t->Right, level - 1);
}
