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

// Объявления функций
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
        cout << "\nВведите:\n1 - Для ввода новой записи;\n2 - Для отображения информации;\n3 - Для поиска;\n4 - Для записи в файл;\n5 - Для чтения из файла;\n6 - Для выхода." << endl;
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
    cout << "Информация об государствах" << endl;
    cout << "Запись  " << current_size + 1 << endl;
    if (current_size < SIZE) {
        cin.ignore();
        bool validName = false;
        while (!validName) {
            cout << "Наименование: ";
            cin.getline(governments[current_size].name.str, 50);
            if (containsDigits(governments[current_size].name.str) || containsSpaces(governments[current_size].name.str)) {
                cout << "Ошибка: Наименование не должно содержать цифры или пробелы, попробуйте еще раз:)" << endl;
            }
            else {
                validName = true;
            }
        }


        bool validCapital = false;
        while (!validCapital) {
            cout << "Столица: ";
            cin.getline(governments[current_size].capital.str, 50);
            if (containsDigits(governments[current_size].capital.str) || containsSpaces(governments[current_size].capital.str)) {
                cout << "Ошибка: Столица должна содержать только буквы и не должна содержать пробелы, попробуйте еще раз:)" << endl;
            }
            else {
                validCapital = true;
            }
        }
        while (true) {
            cout << "Численность населения: ";
            cin >> governments[current_size].population.fnumb;

            if (cin.fail() || cin.peek() != '\n') {
                cout << "Ошибка: Численность населения должна быть числом, попробуйте еще раз:)" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "Площадь (в тыс. кв. км): ";
            cin >> governments[current_size].area.numb;

            if (cin.fail() || cin.peek() != '\n') {
                cout << "Ошибка: Площадь должна быть числом ,попробуйте еще раз:)" << endl;
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
            cout << "Фамилия президента: ";
            cin.getline(governments[current_size].surname.str, 50);
            if (containsDigits(governments[current_size].surname.str) || containsSpaces(governments[current_size].surname.str)) {
                cout << "Ошибка: Фамилия президента должна содержать только буквы и не должна содержать пробелы, попробуйте еще раз:)" << endl;
            }
            else {
                validSurname = true;
            }
        }

        current_size++;
    }
    else {
        cout << "Больше никаких записей ввести невозможно" << endl;
    }
}

void displayOneStructure(Notebook oneProduct) {
    cout << endl;
    cout << "Наименование: " << oneProduct.name.str << endl;
    cout << "Столица: " << oneProduct.capital.str << endl;
    cout << "Численность населения: " << oneProduct.population.fnumb << endl;
    cout << "Площадь (в тыс. кв. км): " << oneProduct.area.numb << endl;
    cout << "Фамилия президента: " << oneProduct.surname.str << endl;
}

void display() {
    int ch, num;
    cout << "1 - для отображения одной записи" << endl;
    cout << "2 - для отображения всех записей" << endl;
    cin >> ch;
    if (ch == 1) {
        cout << "Введите номер записи для отображения" << endl;
        cin >> num;
        if (num > current_size or num < 1)
            cout << "Неверный ввод";
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
        cout << "Неверный ввод";
}

void search() {
    string nedded_government_name;
    cout << "Введите название правительства для поиска: ";
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
            file << "Наименование: " << governments[i].name.str << endl;
            file << "Столица: " << governments[i].capital.str << endl;
            file << "Численность населения: " << governments[i].population.fnumb << endl;
            file << "Площадь (в тыс. кв. км): " << governments[i].area.numb << endl;
            file << "Фамилия президента: " << governments[i].surname.str << endl;
            file << endl;
        }
        cout << "Информация успешно записана в файл " << filename << endl;
        file.close();
    }
    else {
        cout << "Не удалось открыть файл для записи." << endl;
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
        cout << "Не удалось открыть файл для чтения." << endl;
    }
}
