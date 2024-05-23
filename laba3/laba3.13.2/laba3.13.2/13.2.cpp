#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <unordered_map>

int main() {
    setlocale(LC_ALL, "rus");
    // ���� ������ � ����������
    cout << "������� ������ ��������, ��������� �� ���� � ������: ";
    string inputString;
    getline(cin, inputString);

    // ������ ������ � ����
    ofstream outputFile("input.txt");
    if (!outputFile.is_open()) {
        cerr << "�� ������� ������� ���� ��� ������." << endl;
        return 1;
    }
    outputFile << inputString;
    outputFile.close();

    // ������ ������ �� ����� � ������� ���������� ��������� ������
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "�� ������� ������� ���� ��� ������." << endl;
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

    // ����� ���������� ������ ���������� ����
    cout << "���������� ��������� ������:\n";
    for (const auto& pair : bracketCounts) {
        cout << "'" << pair.first << "': " << pair.second << endl;
    }

    return 0;
}
