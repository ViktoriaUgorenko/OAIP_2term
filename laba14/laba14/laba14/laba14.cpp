#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Для функций рандомизации
#include <ctime>   // Для генерации случайного числа seed
#include <chrono>  // Для измерения времени выполнения

using namespace std;

struct Node {
    string email;
    int year;

    Node(const string& e, int y) : email(e), year(y) {}
};

int hashFunction(int key, size_t length) {
    return key % length;
}

void add(vector<vector<Node*>>& table, const string& email, int year, size_t length) {
    int hash_val = hashFunction(year, length);
    table[hash_val].push_back(new Node(email, year));
}

void remove(vector<vector<Node*>>& table, int year, size_t length) {
    int hash_val = hashFunction(year, length);
    vector<Node*>& bucket = table[hash_val];
    for (size_t i = 0; i < bucket.size(); ++i) {
        if (bucket[i]->year == year) {
            delete bucket[i];
            bucket.erase(bucket.begin() + i);
            return;
        }
    }
    cout << "Элемент не найден." << endl;
}

Node* search(const vector<vector<Node*>>& table, int year, size_t length) {
    int hash_val = hashFunction(year, length);
    const vector<Node*>& bucket = table[hash_val];
    for (Node* node : bucket) {
        if (node->year == year) {
            return node;
        }
    }
    return nullptr;
}

void print(const vector<vector<Node*>>& table, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        cout << "Bucket " << i << ": ";
        for (Node* node : table[i]) {
            cout << "(" << node->email << ", " << node->year << ") ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(0, "");
    srand(time(nullptr)); // Устанавливаем seed для генерации случайных чисел

    size_t table_size;
    cout << "Введите размер хеш-таблицы: ";
    cin >> table_size;

    vector<vector<Node*>> hashTable(table_size);

    int choice;
    while (true) {
        cout << "\nВыберите действие:\n";
        cout << "1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Найти элемент\n";
        cout << "4. Вывести таблицу\n";
        cout << "5. Выйти\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string email;
            int year;
            cout << "Введите номер группы: ";
            cin.ignore(); // Очистка входного потока
            getline(cin, email); // Используем getline для ввода строки с пробелами
            cout << "Введите кол-во студентов: ";
            cin >> year;
            add(hashTable, email, year, table_size);
            break;
        }

        case 2: {
            int year;
            cout << "Введите кол-во студентов элемента для удаления: ";
            cin >> year;
            remove(hashTable, year, table_size);
            break;
        }
        case 3: {
            int year;
            cout << "Введите кол-во студентов элемента для поиска: ";
            cin >> year;

            auto start = chrono::high_resolution_clock::now(); // Начало измерения времени

            Node* result = search(hashTable, year, table_size);

            auto end = chrono::high_resolution_clock::now(); // Конец измерения времени
            chrono::duration<double> elapsed = end - start;  // Подсчет времени

            if (result) {
                cout << "Найден: " << result->email << ", " << result->year << endl;
            }
            else {
                cout << "Элемент не найден." << endl;
            }
            cout << "Время поиска: " << elapsed.count() << " секунд" << endl;
            break;
        }

        case 4:
            cout << "Хеш-таблица:" << endl;
            print(hashTable, table_size);
            break;
        case 5:
            // Освобождаем выделенную память
            for (vector<Node*>& bucket : hashTable) {
                for (Node* node : bucket) {
                    delete node;
                }
            }
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
    }

    return 0;
}
