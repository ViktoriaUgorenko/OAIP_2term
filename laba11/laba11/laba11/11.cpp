#include <iostream>
#include <Windows.h>
#include <cstring>  // для strcpy_s

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
        cout << "1-создание дерева\n2-добавление элемента\n3-поиск по ключу\n4-удаление элемента\n5-вывод дерева\n6-очистка дерева\n7-сумма значений вершин, находящихся на этом уровне\n8-выход\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            Root = makeTree(Root);
            break;

        case 2:
            cout << "введите ключ" << endl;
            cin >> key;
            cout << endl;
            cout << "введите слово" << endl;
            cin >> s;
            Root = insertElem(Root, key, s, 0);
            break;

        case 3:
            cout << "введите ключ" << endl;
            cin >> key;
            rc = search(Root, key);
            if (rc != NULL)
                cout << "Слово, которое то, что было найдено, является " << rc->text << endl;
            break;

        case 4:
            cout << "Введите ключ для удаления" << endl;
            cin >> key;
            Root = delet(Root, key);
            break;

        case 5:
            if (Root != NULL)
            {
                cout << "Дерево повернуто на 90 град. влево" << endl;
                view(Root, 0);
            }
            else
                cout << "Дерево пусто!" << endl;
            break;

        case 6:
            delAll(Root);
            Root = NULL;
            break;

        case 7:
            int level;
            cout << "Введите уровень: ";
            cin >> level;
            int treeDepth;
            treeDepth = depth(Root);
            if (level >= treeDepth)
            {
                cout << "Элементов нет на уровне " << level << endl;
            }
            else
            {
                cout << "Сумма значений на уровне " << level << " равна " << sumAtLevel(Root, level) << endl;
            }
            break;

        case 8:
            exit = true;
            break;

        default:
            cout << "Неверный выбор. Попробуйте еще раз." << endl;
        }
    }
    return 0;
}

Tree* makeTree(Tree* Root)
{
    int key;
    char s[100];
    cout << "Конец входа-отрицательное число\n\n";
    if (Root == NULL)
    {
        cout << "Введите ключ: ";
        cin >> key;
        cout << "Введите слово: ";
        cin >> s;
        Root = list(key, s);
    }
    while (1)
    {
        cout << "\nВведите ключ: ";
        cin >> key;
        if (key < 0) break;
        cout << "Введите слово: ";
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
    if (level >= 11) // Проверяем глубину поддерева
    {
        cout << "Глубина дерева превышает 10 уровней. Элемент не может быть добавлен." << endl;
        return t;
    }

    if (t == NULL)
    {
        return list(key, s);
    }
    if (key == t->key)
    {
        cout << "Такой ключ уже есть! " << endl;
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
        cout << "\nЭтот ключ не найден" << endl;
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
    cout << "\nУдалён элемент с ключом " << tmp << endl;
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
        cout << "Такого элемента не существует\n";
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
