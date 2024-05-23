#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <sstream>

using namespace std;

const int SIZE = 30;
int current_size = 0;
int current_y = 2023;
int current_m = 3;
int current_d = 14;

enum Faculties {
    FIT = 1,
    TOV,
    HTIT,
    PIM
};

struct EnterTime {
    unsigned day : 5;
    unsigned month : 4;
    unsigned year : 11;

};

struct Students {
    string surname;
    string name;
    string middlename;
    EnterTime enter_time;
    string specialty;
    int group; 
    Faculties faculty;
    double average;
} students[SIZE];
Students empty_student = { "", "", "", {0, 0, 0}, "", 0, FIT, 0.0 };

void addNew();
void displayOneStructure(Students onePupil);
void display();
void deleteRecord();
void search();

string replaceDot(string str);

bool contains_space(const std::string& str) {
    return str.find(' ') != std::string::npos;
}

bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool is_valid_date(int day, int month, int year) {
    if (year < 0 || month < 1 || month > 12)
        return false;

    if (month == 2) {
        if (is_leap_year(year))
            return (day >= 1 && day <= 29);
        else
            return (day >= 1 && day <= 28);
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return (day >= 1 && day <= 30);
    }
    else {
        return (day >= 1 && day <= 31);
    }
}

void deleteRecord() {
    int rec_number;
    cout << "Введите номер записи для удаления" << endl;
    cin >> rec_number;
    if (rec_number != 0) {
        for (int de = (rec_number - 1); de < current_size - 1; de++)
            students[de] = students[de + 1];
        current_size -= 1;
    }
    if (rec_number == 0)
        for (int i = 0; i < SIZE; i++)
            students[i] = empty_student;
}

void search() {
    double nedded_average;
    cout << "Введите средний балл для поиска: ";
    cin >> nedded_average;
    cout << endl;
    const double EPSILON = 0.0001; // Точность сравнения для среднего балла с плавающей точкой
    for (int i = 0; i < current_size; i++) {
        if (abs(students[i].average - nedded_average) < EPSILON) {
            displayOneStructure(students[i]);
        }
    }
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
        if (students[num - 1].surname != "") {
            displayOneStructure(students[num - 1]);
        }
        else {
            cout << "Запись пуста" << endl;
        }
    }
    else if (ch == 2) {
        bool anyStudentDisplayed = false;
        for (int i = 0; i < current_size; i++) {
            if (students[i].surname != "") {
                displayOneStructure(students[i]);
                cout << endl;
                anyStudentDisplayed = true;
            }
        }
        if (!anyStudentDisplayed) {
            cout << "Нет заполненных записей" << endl;
        }
    }
    else {
        cout << "Неверный ввод";
    }
}



void displayOneStructure(Students onePupil) {
    cout << endl;
    cout << "Фамилия: " << onePupil.surname << endl;
    cout << "Имя: " << onePupil.name << endl;
    cout << "Отчество: " << onePupil.middlename << endl;
    cout << "День: " << onePupil.enter_time.day << endl;
    cout << "Месяц: " << onePupil.enter_time.month << endl;
    cout << "Год: " << onePupil.enter_time.year << endl;
    cout << "Специальность: " << onePupil.specialty << endl;
    cout << "Группа: " << onePupil.group << endl;
    cout << "Факультет:";
    if (onePupil.faculty == FIT)
        cout << "FIT" << endl;
    if (onePupil.faculty == TOV)
        cout << "TOV" << endl;
    if (onePupil.faculty == HTIT)
        cout << "HTIT" << endl;
    if (onePupil.faculty == PIM)
        cout << "PIM" << endl;

    // Указываем фиксированную точность с двумя знаками после запятой
    cout << "Средний балл: " << std::fixed << onePupil.average << endl;
}

bool contains_digits(const string& str) {
    for (char c : str) {
        if (isdigit(c)) { // Проверяем, является ли символ цифрой
            return true; // Если найдена цифра, возвращаем true
        }
    }
    return false; // Если цифр не найдено, возвращаем false
}

bool contains_letters(const std::string& str) {
    for (char c : str) {
        if (isalpha(c)) { // Проверяем, является ли символ буквой
            return true; // Если найдена буква, возвращаем true
        }
    }
    return false; // Если букв не найдено, возвращаем false
}
double calculateAverageScore(const string& grades);
void addNew() {
    cout << "Ввод информации" << endl;
    cout << "Запись " << current_size + 1 << endl;

    if (current_size < SIZE) {
        bool surname_entered = false;
        while (!surname_entered) {
            std::cout << "Фамилия: ";
            std::cin.ignore(); // Используем ignore перед getline для очистки буфера
            std::getline(std::cin, students[current_size].surname);
            if (contains_digits(students[current_size].surname) || contains_space(students[current_size].surname)) {
                std::cout << "Ошибка: Фамилия не должна содержать цифры или пробелы, попробуйте еще раз:)" << std::endl;
            }
            else {
                surname_entered = true;
            }
        }

        bool name_entered = false;
        while (!name_entered) {
            std::cout << "Имя: ";
            std::getline(std::cin, students[current_size].name);
            if (contains_digits(students[current_size].name) || contains_space(students[current_size].name)) {
                std::cout << "Ошибка: Имя не должно содержать цифры или пробелы, попробуйте еще раз:)" << std::endl;
            }
            else {
                name_entered = true;
            }
        }

        bool middlename_entered = false;
        while (!middlename_entered) {
            cout << "Отчество: ";
            getline(cin, students[current_size].middlename);
            if (contains_digits(students[current_size].middlename) || contains_space(students[current_size].middlename)) {
                std::cout << "Ошибка: Отчество не должно содержать цифры или пробелы, попробуйте еще раз:)" << std::endl;
            }
            else {
                middlename_entered = true;
            }
        }

        int is_correct_arriving_time = 0;
        while (is_correct_arriving_time != 2) {
            int day;
            int month;
            int year;
            cout << "Введите дату: " << endl;

            cout << "День: ";
            cin >> day;
            if (cin.fail() || day < 1 || day > 31) {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Ошибка: Введите корректный день." << endl;
                continue;
            }

            cout << "Месяц: ";
            cin >> month;
            if (cin.fail() || month < 1 || month > 12) {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Ошибка: Введите корректный месяц." << endl;
                continue;
            }

            cout << "Год: ";
            cin >> year;

            if (cin.fail() || year < 0) {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Ошибка: Введите корректный год." << endl;
                continue;
            }

            // Проверка на валидность даты
            if (!is_valid_date(day, month, year)) {
                cout << "Неверная дата, попробуйте еще раз:)" << endl;
                continue;
            }

            if (year > 2024 || (year == 2024 && (month > 4 || (month == 4 && day > 26)))) {
                cout << "Неверная дата. Попробуйте еще раз:)" << endl;
                continue;
            }

            students[current_size].enter_time.day = day;
            students[current_size].enter_time.month = month;
            students[current_size].enter_time.year = year;

            is_correct_arriving_time = 2; // Обновляем значение is_correct_arriving_time
        }


        std::string specialty;
        bool is_specialty_entered = false;
        while (!is_specialty_entered) {
            std::cout << "Специальность: ";
            std::cin.ignore();
            getline(cin, students[current_size].specialty);
            if (contains_digits(students[current_size].specialty)) {
                std::cout << "Ошибка: Специальность не должна содержать цифры, попробуйте еще раз:)" << std::endl;
            }
            else {
                is_specialty_entered = true;
            }
        }
        string gr;
        bool is_group_entered = false;
        while (!is_group_entered) {
            std::cout << "Группа: ";
            std::cin >> gr;

            // Проверяем, что введены только цифры
            bool onlyDigits = std::all_of(gr.begin(), gr.end(), [](char c) {
                return std::isdigit(c);
                });

            if (!onlyDigits) {
                std::cout << "Ошибка: Номер группы должен состоять только из цифр, попробуйте еще раз:)" << std::endl;
            }
            else {
                students[current_size].group = std::stoi(gr); // Преобразуем строку в число
                is_group_entered = true;
            }
        }



        int fac;
        bool is_valid_input_faculty = false;
        while (!is_valid_input_faculty) {
            std::cout << "Факультет(1 - FIT, 2 - TOV, 3 - HTIT, 4 - PIM): ";
            std::string input;
            std::cin >> input;

            // Проверяем, что введены только цифры
            bool onlyDigits = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    onlyDigits = false;
                    break;
                }
            }

            if (!onlyDigits) {
                std::cout << "Ошибка: Некорректный ввод. Введите число от 1 до 4." << std::endl;
                continue; 
            }

            fac = std::stoi(input);  

            if (fac < 1 || fac > 4) {
                std::cout << "Ошибка: Введите число от 1 до 4." << std::endl;
            }
            else {
                is_valid_input_faculty = true;
            }
        }

        // Присваивание значения переменной в соответствии с введенным числом
        switch (fac) {
        case 1: students[current_size].faculty = FIT; break;
        case 2: students[current_size].faculty = TOV; break;
        case 3: students[current_size].faculty = HTIT; break;
        case 4: students[current_size].faculty = PIM; break;
        default: break;
        }
        cout << "Средний балл: ";
        while (!(cin >> students[current_size].average) || cin.peek() != '\n') {
            cout << "Ошибка: Введите числовое значение для среднего балла: ";
            cin.clear(); // Сброс флагов ошибок
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
        }

        // Проверка на диапазон среднего балла
        while (students[current_size].average < 0 || students[current_size].average > 10.0) {
            cout << "Ошибка: Введите корректный средний балл (от 0 до 10): ";
            cin >> students[current_size].average;
        }


		current_size++;

      
    }
}

string replaceDot(string str) {
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '.')
        {
            str[i] = ',';
        }
    }

    return str;
}


int main()
{
    setlocale(LC_ALL, "rus");
    short choose;
    Students students[SIZE];
    do
    {
        cout << "\nВведите:\n1 - Для ввода новой записи;\n2 - Для отображения информации;\n3 - Для удаления записи;\n4 - Для поиска\n5 - Выход.\n";
        cin >> choose;
        switch (choose) {
        case 1: addNew(); break;
        case 2: display(); break;
        case 3: deleteRecord(); break;
        case 4: search(); break;
        }
    } while (choose != 5);

    return 0;
}