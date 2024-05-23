#include "zag.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <regex>
#include <unordered_set>

using namespace std;
regex checknum("[\\-]?[0-9]+");
heap::CMP cmpAAA(void* a1, void* a2)  // Функция сравнения
{
#define A1 ((AAA*)a1)
#define A2 ((AAA*)a2)
    heap::CMP
        rc = heap::EQUAL;
    if (A1->x > A2->x)
        rc = heap::GREAT;
    else
        if (A2->x > A1->x)
            rc = heap::LESS;
    return rc;
#undef A2
#undef A1 
}

//-------------------------------
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int k, choice;
    string b;
    heap::Heap h1 = heap::create(100, cmpAAA);
    unordered_set<int> keys; // To keep track of inserted keys

    for (;;)
    {
        cout << "1 - вывод кучи на экран\n";
        cout << "2 - добавить элемент\n";
        cout << "3 - удалить максимальный элемент\n";
        cout << "4 - удалить минимальный элемент\n";
        cout << "5 - удалить элемент по номеру\n";
        cout << "6 - создать дополнительную кучу и объединить с основной\n";
        cout << "0 - выход\n";
        cout << "сделайте выбор\n";
        getline(cin, b);
        while (b.length() != 1) {
            cout << "Некорректный ввод\n";
            getline(cin, b);
        }
        choice = b[0];
        switch (choice)
        {
        case '0':  exit(0);
        case '1': {
            h1.scan(0);
            break;
        }
        case '2': { AAA* a = new AAA;
            cout << "введите ключ\n";
            getline(cin, b);
            while (!regex_match(b, checknum)) {
                cout << "Некорректный ввод\n";
                getline(cin, b);
            }
            k = stoi(b);
            if (keys.find(k) != keys.end()) {
                cout << "Ключ уже существует\n";
                delete a;
                break;
            }
            a->x = k;
            h1.insert(a, k);
            keys.insert(k); // Add key to set
            break;
        }
        case '3': {
            void* maxElem = h1.extractMax();
            if (maxElem) {
                AAA* a = (AAA*)maxElem;
                keys.erase(a->x); // Remove key from set
                delete a;
            }
            break;
        }
        case '4': {
            heap::Heap h3 = heap::create(100, cmpAAA);
            h1.extractMin(h3, h1);
            h1 = h3;
            break;
        }
        case '5': {
            int n;
            cout << "Введите номер элемента, который хотите удалить\n";
            getline(cin, b);
            while (!regex_match(b, checknum)) {
                cout << "Некорректный ввод\n";
                getline(cin, b);
            }
            n = stoi(b);
            void* elem = h1.extractI(n);
            if (elem) {
                AAA* a = (AAA*)elem;
                keys.erase(a->x); // Remove key from set
                delete a;
            }
            break;
        }
        case '6': {
            cout << "Вы выбрали опцию объединения двух куч. Для начала нужно создать дополнительную кучу\n";
            int choice2;
            heap::Heap h2 = heap::create(30, cmpAAA);
            unordered_set<int> keys2; // To keep track of keys in the second heap

            for (;;)
            {
                cout << "1 - вывод кучи на экран\n";
                cout << "2 - добавить элемент\n";
                cout << "3 - удалить максимальный элемент\n";
                cout << "4 - удалить минимальный элемент\n";
                cout << "5 - удалить элемент по номеру\n";
                cout << "6 - объединить кучи и вернуться в главное меню\n";
                cout << "сделайте выбор\n";
                getline(cin, b);
                while (b.length() != 1) {
                    cout << "Некорректный ввод\n";
                    getline(cin, b);
                }
                choice2 = b[0];
                switch (choice2)
                {
                case '1': {
                    h2.scan(0);
                    break;
                }
                case '2': { AAA* a = new AAA;
                    cout << "введите ключ\n";
                    getline(cin, b);
                    while (!regex_match(b, checknum)) {
                        cout << "Некорректный ввод\n";
                        getline(cin, b);
                    }
                    k = stoi(b);
                    if (keys.find(k) != keys.end() || keys2.find(k) != keys2.end()) {
                        cout << "Ключ уже существует\n";
                        delete a;
                        break;
                    }
                    a->x = k;
                    h2.insert(a, k);
                    keys2.insert(k); // Add key to set
                    break;
                }
                case '3': {
                    void* maxElem = h2.extractMax();
                    if (maxElem) {
                        AAA* a = (AAA*)maxElem;
                        keys2.erase(a->x); // Remove key from set
                        delete a;
                    }
                    break;
                }
                case '4': {
                    heap::Heap h3 = heap::create(100, cmpAAA);
                    h2.extractMin(h3, h2);
                    h2 = h3;
                    break;
                }
                case '5': {
                    int n;
                    cout << "Введите номер элемента, который хотите удалить\n";
                    getline(cin, b);
                    while (!regex_match(b, checknum)) {
                        cout << "Некорректный ввод\n";
                        getline(cin, b);
                    }
                    n = stoi(b);
                    void* elem = h2.extractI(n);
                    if (elem) {
                        AAA* a = (AAA*)elem;
                        keys2.erase(a->x); // Remove key from set
                        delete a;
                    }
                    break;
                }
                case '6': {
                    h1.unionHeap(h2, h1);
                    keys.insert(keys2.begin(), keys2.end()); // Merge keys
                    break;
                }
                default: {
                    cout << "Некорректный ввод\n";
                }
                }
                if (choice2 == '6') {
                    break;
                }
            }
            break;
        }
        default:  cout << "\nВведена неверная команда!\n";
        }
    }
    return 0;
}