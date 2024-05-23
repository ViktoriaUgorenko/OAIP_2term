#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
using namespace std;

const int SIZE = 30;
int current_size = 0;

union forstruct {
    char str[50];
    long int numb;
    float fnumb;
};

struct Notebook {
    forstruct name;
    forstruct capital;
    forstruct surname;
    forstruct population;
    forstruct area;
} governments[SIZE];

// ���������� �������
void writeToFile(const string& filename);
void readFromFile(const string& filename);
void addNew();
void display();
void search();

bool containsDigits(const char* str) {
    while (*str) {
        if (std::isdigit(*str)) {
            return true;
        }
        str++;
    }
    return false;
}

bool containsLetters(const char* str) {
    while (*str) {
        if (std::isalpha(*str)) {
            return true;
        }
        str++;
    }
    return false;
}

bool containsSpaces(const char* str) {
    while (*str) {
        if (*str == ' ') {
            return true;
        }
        str++;
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "rus");
    int choose;
    string filename = "government_data.txt";

    do {
        cout << "\n�������:\n1 - ��� ����� ����� ������;\n2 - ��� ����������� ����������;\n3 - ��� ������;\n4 - ��� ������ � ����;\n5 - ��� ������ �� �����;\n6 - ��� ������." << endl;
        cin >> choose;
        switch (choose) {
        case 1: addNew(); break;
        case 2: display(); break;
        case 3: search(); break;
        case 4: writeToFile(filename); break;
        case 5: readFromFile(filename); break;
        }
    } while (choose != 6);

    return 0;
}

void addNew() {
    cout << "���������� �� ������������" << endl;
    cout << "������  " << current_size + 1 << endl;
    if (current_size < SIZE) {
        cin.ignore();
        bool validName = false;
        while (!validName) {
            cout << "������������: ";
            cin.getline(governments[current_size].name.str, 50);
            if (containsDigits(governments[current_size].name.str) || containsSpaces(governments[current_size].name.str)) {
                cout << "������: ������������ �� ������ ��������� ����� ��� �������, ���������� ��� ���:)" << endl;
            }
            else {
                validName = true;
            }
        }


        bool validCapital = false;
        while (!validCapital) {
            cout << "�������: ";
            cin.getline(governments[current_size].capital.str, 50);
            if (containsDigits(governments[current_size].capital.str) || containsSpaces(governments[current_size].capital.str)) {
                cout << "������: ������� ������ ��������� ������ ����� � �� ������ ��������� �������, ���������� ��� ���:)" << endl;
            }
            else {
                validCapital = true;
            }
        }
        while (true) {
            cout << "����������� ���������: ";
            cin >> governments[current_size].population.fnumb;

            if (cin.fail() || cin.peek() != '\n') {
                cout << "������: ����������� ��������� ������ ���� ������, ���������� ��� ���:)" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "������� (� ���. ��. ��): ";
            cin >> governments[current_size].area.numb;

            if (cin.fail() || cin.peek() != '\n') {
                cout << "������: ������� ������ ���� ������ ,���������� ��� ���:)" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }
        cin.ignore();
        bool validSurname = false;
        while (!validSurname) {
            cout << "������� ����������: ";
            cin.getline(governments[current_size].surname.str, 50);
            if (containsDigits(governments[current_size].surname.str) || containsSpaces(governments[current_size].surname.str)) {
                cout << "������: ������� ���������� ������ ��������� ������ ����� � �� ������ ��������� �������, ���������� ��� ���:)" << endl;
            }
            else {
                validSurname = true;
            }
        }

        current_size++;
    }
    else {
        cout << "������ ������� ������� ������ ����������" << endl;
    }
}

void displayOneStructure(Notebook oneProduct) {
    cout << endl;
    cout << "������������: " << oneProduct.name.str << endl;
    cout << "�������: " << oneProduct.capital.str << endl;
    cout << "����������� ���������: " << oneProduct.population.fnumb << endl;
    cout << "������� (� ���. ��. ��): " << oneProduct.area.numb << endl;
    cout << "������� ����������: " << oneProduct.surname.str << endl;
}

void display() {
    int ch, num;
    cout << "1 - ��� ����������� ����� ������" << endl;
    cout << "2 - ��� ����������� ���� �������" << endl;
    cin >> ch;
    if (ch == 1) {
        cout << "������� ����� ������ ��� �����������" << endl;
        cin >> num;
        if (num > current_size or num < 1)
            cout << "�������� ����";
        cout << endl;
        displayOneStructure(governments[num - 1]);
    }
    else if (ch == 2) {
        for (int i = 0; i < current_size; i++) {
            displayOneStructure(governments[i]);
            cout << endl;
        }
    }
    else
        cout << "�������� ����";
}

void search() {
    string nedded_government_name;
    cout << "������� �������� ������������� ��� ������: ";
    cin.ignore();
    getline(cin, nedded_government_name);
    cout << endl;
    for (int i = 0; i < current_size; i++) {
        if (governments[i].name.str == nedded_government_name) {
            displayOneStructure(governments[i]);
        }
    }
}

void writeToFile(const string& filename) {
    ofstream file(filename, ios::out);
    if (file.is_open()) {
        for (int i = 0; i < current_size; ++i) {
            file << "������������: " << governments[i].name.str << endl;
            file << "�������: " << governments[i].capital.str << endl;
            file << "����������� ���������: " << governments[i].population.fnumb << endl;
            file << "������� (� ���. ��. ��): " << governments[i].area.numb << endl;
            file << "������� ����������: " << governments[i].surname.str << endl;
            file << endl;
        }
        cout << "���������� ������� �������� � ���� " << filename << endl;
        file.close();
    }
    else {
        cout << "�� ������� ������� ���� ��� ������." << endl;
    }
}

void readFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "�� ������� ������� ���� ��� ������." << endl;
    }
}
