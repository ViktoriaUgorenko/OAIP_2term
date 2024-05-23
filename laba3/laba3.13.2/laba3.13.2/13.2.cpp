#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <unordered_map>

int main() {
    setlocale(LC_ALL, "rus");
    // Ввод строки с клавиатуры
    cout << "Введите строку символов, состоящую из цифр и скобок: ";
    string inputString;
    getline(cin, inputString);

    // Запись строки в файл
    ofstream outputFile("input.txt");
    if (!outputFile.is_open()) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return 1;
    }
    outputFile << inputString;
    outputFile.close();

    // Чтение данных из файла и подсчет количества различных скобок
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл для чтения." << endl;
        return 1;
    }

    unordered_map<char, int> bracketCounts;
    char c;
    while (inputFile.get(c)) {
        if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') {
            bracketCounts[c]++;
        }
    }

    inputFile.close();

    // Вывод количества скобок различного вида
    cout << "Количество различных скобок:\n";
    for (const auto& pair : bracketCounts) {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }

    return 0;
}
