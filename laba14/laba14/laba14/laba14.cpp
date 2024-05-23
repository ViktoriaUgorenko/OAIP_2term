#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // ��� ������� ������������
#include <ctime>   // ��� ��������� ���������� ����� seed
#include <chrono>  // ��� ��������� ������� ����������

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
    cout << "������� �� ������." << endl;
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
    srand(time(nullptr)); // ������������� seed ��� ��������� ��������� �����

    size_t table_size;
    cout << "������� ������ ���-�������: ";
    cin >> table_size;

    vector<vector<Node*>> hashTable(table_size);

    int choice;
    while (true) {
        cout << "\n�������� ��������:\n";
        cout << "1. �������� �������\n";
        cout << "2. ������� �������\n";
        cout << "3. ����� �������\n";
        cout << "4. ������� �������\n";
        cout << "5. �����\n";
        cout << "�����: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string email;
            int year;
            cout << "������� ����� ������: ";
            cin.ignore(); // ������� �������� ������
            getline(cin, email); // ���������� getline ��� ����� ������ � ���������
            cout << "������� ���-�� ���������: ";
            cin >> year;
            add(hashTable, email, year, table_size);
            break;
        }

        case 2: {
            int year;
            cout << "������� ���-�� ��������� �������� ��� ��������: ";
            cin >> year;
            remove(hashTable, year, table_size);
            break;
        }
        case 3: {
            int year;
            cout << "������� ���-�� ��������� �������� ��� ������: ";
            cin >> year;

            auto start = chrono::high_resolution_clock::now(); // ������ ��������� �������

            Node* result = search(hashTable, year, table_size);

            auto end = chrono::high_resolution_clock::now(); // ����� ��������� �������
            chrono::duration<double> elapsed = end - start;  // ������� �������

            if (result) {
                cout << "������: " << result->email << ", " << result->year << endl;
            }
            else {
                cout << "������� �� ������." << endl;
            }
            cout << "����� ������: " << elapsed.count() << " ������" << endl;
            break;
        }

        case 4:
            cout << "���-�������:" << endl;
            print(hashTable, table_size);
            break;
        case 5:
            // ����������� ���������� ������
            for (vector<Node*>& bucket : hashTable) {
                for (Node* node : bucket) {
                    delete node;
                }
            }
            return 0;
        default:
            cout << "�������� �����. ���������� �����." << endl;
            break;
        }
    }

    return 0;
}
