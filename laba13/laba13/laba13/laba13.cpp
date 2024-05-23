#include <iostream>
#include <Windows.h>
#include <string>
#include <cmath>
#include <chrono> // Include chrono for timing

using namespace std;
using namespace chrono; // For convenience

const int DEL = -1; // Константа для пометки удаленных элементов

class Object {
private:
    int size;
    int N;
    void** data;
    int (*getKey)(void*);
    int (*hashFunction)(int, int, int);
    struct AAA {
        int key;
        string mas;

        AAA(int k, string z) : key(k), mas(z) {}

        AAA() {}
    };

public:
    Object(int size, int (*getkey)(void*), int (*hashFunction)(int, int, int))
        : size(size), N(0), getKey(getkey), hashFunction(hashFunction) {
        data = new void* [size]();
    }

    ~Object() {
        for (int i = 0; i < size; i++) {
            if (data[i] != nullptr && data[i] != reinterpret_cast<void*>(DEL)) {
                delete reinterpret_cast<AAA*>(data[i]);
            }
        }
        delete[] data;
    }

    bool insert(void* d) {
        if (N == size) return false;
        int t = getKey(d);
        for (int i = 0, j = hashFunction(t, size, 0); i < size; j = hashFunction(t, size, ++i)) {
            if (data[j] == nullptr || data[j] == reinterpret_cast<void*>(DEL)) {
                data[j] = d;
                N++;
                return true;
            }
        }
        return false;
    }

    int searchInd(int key) {
        for (int i = 0, j = hashFunction(key, size, 0); data[j] != nullptr; j = hashFunction(key, size, ++i)) {
            if (data[j] != reinterpret_cast<void*>(DEL) && getKey(data[j]) == key) {
                return j;
            }
        }
        return -1;
    }

    void* search(int key) {
        int index = searchInd(key);
        return (index >= 0) ? data[index] : nullptr;
    }

    void* deleteByKey(int key) {
        int index = searchInd(key);
        if (index >= 0) {
            void* deletedItem = data[index];
            data[index] = reinterpret_cast<void*>(DEL);
            N--;
            return deletedItem;
        }
        return nullptr;
    }

    void scan(void(*f)(void*)) {
        for (int i = 0; i < size; i++) {
            cout << " Элемент " << i;
            if (data[i] == nullptr)
                cout << "  пусто" << endl;
            else if (data[i] == reinterpret_cast<void*>(DEL))
                cout << "  удален" << endl;
            else
                f(data[i]);
        }
    }

    int countCollisions() {
        int collisions = 0;
        for (int i = 0; i < size; ++i) {
            if (data[i] != nullptr && data[i] != reinterpret_cast<void*>(DEL)) {
                int key = getKey(data[i]);
                int j = hashFunction(key, size, 0);
                if (j != i) {
                    ++collisions;
                }
            }
        }
        return collisions;
    }
};

// мультипликативная 
int MultiplicativeHashFunction(int key, int size, int p) {
    double A = 0.6180339887499;
    return static_cast<int>(size * fmod(key * A, 1.0)) + p;
}

// модульная 
int ModularHashFunction(int key, int size, int p) {
    return (key + 5 * p + 3 * p * p) % size;
}

struct AAA {
    int key;
    string mas;

    AAA(int k, string z) : key(k), mas(z) {}

    AAA() {}
};

int key(void* d) {
    AAA* f = reinterpret_cast<AAA*>(d);
    return f->key;
}

void AAA_print(void* d) {
    cout << " ключ " << reinterpret_cast<AAA*>(d)->key << " - " << reinterpret_cast<AAA*>(d)->mas << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    int size;
    cout << "Введите размер хеш-таблицы: ";
    cin >> size;

    Object modTable(size, key, ModularHashFunction);
    Object multTable(size, key, MultiplicativeHashFunction);

    for (;;) {
        int choice;
        cout << "1 - вывод модульной хеш-таблицы" << endl;
        cout << "2 - вывод мультипликативной хеш-таблицы" << endl;
        cout << "3 - добавление элемента" << endl;
        cout << "4 - удаление элемента" << endl;
        cout << "5 - поиск элемента" << endl;
        cout << "6 - количество коллизий в модульной хеш-таблице" << endl;
        cout << "7 - количество коллизий в мультипликативной хеш-таблице" << endl;
        cout << "0 - выход" << endl;
        cout << "Сделайте выбор: ";
        cin >> choice;
        switch (choice) {
        case 0:
            exit(0);
        case 1:
            cout << "Модульная хеш-таблица:" << endl;
            modTable.scan(AAA_print);
            break;
        case 2:
            cout << "Мультипликативная хеш-таблица:" << endl;
            multTable.scan(AAA_print);
            break;
        case 3: {
            int k;
            cout << "Введите ключ: ";
            cin >> k;
            string str;
            cout << "Введите строку: ";
            cin.ignore(); // Очищаем буфер после cin
            getline(cin, str); // Считываем всю строку
            AAA* a = new AAA(k, str);
            if (!modTable.insert(a))
                cout << "Модульная хеш-таблица заполнена" << endl;
            if (!multTable.insert(a))
                cout << "Мультипликативная хеш-таблица заполнена" << endl;
            break;
        }
        case 4: {
            int k;
            cout << "Введите ключ для удаления: ";
            cin >> k;
            modTable.deleteByKey(k);
            multTable.deleteByKey(k);
            break;
        }
        case 5: {
            int k;
            cout << "Введите ключ для поиска: ";
            cin >> k;

            // Measure search time in modular hash table
            auto start_mod = high_resolution_clock::now();
            void* result_mod = modTable.search(k);
            auto end_mod = high_resolution_clock::now();
            auto duration_mod = duration_cast<microseconds>(end_mod - start_mod);

            cout << "Поиск в модульной хеш-таблице (" << duration_mod.count() << " мкс):" << endl;
            if (result_mod == nullptr)
                cout << "Элемент не найден" << endl;
            else
                AAA_print(result_mod);

            // Measure search time in multiplicative hash table
            auto start_mult = high_resolution_clock::now();
            void* result_mult = multTable.search(k);
            auto end_mult = high_resolution_clock::now();
            auto duration_mult = duration_cast<microseconds>(end_mult - start_mult);

            cout << "Поиск в мультипликативной хеш-таблице (" << duration_mult.count() << " мкс):" << endl;
            if (result_mult == nullptr)
                cout << "Элемент не найден" << endl;
            else
                AAA_print(result_mult);

            break;
        }
        case 6:
            cout << "Количество коллизий в модульной хеш-таблице: " << modTable.countCollisions() << endl;
            break;
        case 7:
            cout << "Количество коллизий в мультипликативной хеш-таблице: " << multTable.countCollisions() << endl;
            break;
        }
    }
    return 0;
}
