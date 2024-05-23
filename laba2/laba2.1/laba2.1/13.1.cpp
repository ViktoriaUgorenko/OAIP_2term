#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    ifstream fileA("fileA.txt");
    ofstream fileB("fileB.txt");

    if (!fileA.is_open() || !fileB.is_open()) {
        cerr << "Невозможно открыть файл" << endl;
        return 1;
    }

    unordered_map<int, int> occurrences;

    int number;
    while (fileA >> number) {
        occurrences[number]++;
    }

    for (const auto& pair : occurrences) {
        if (pair.second > 2) {
            fileB << pair.first << endl;
        }
    }

    fileA.close();
    fileB.close();

    return 0;
}
