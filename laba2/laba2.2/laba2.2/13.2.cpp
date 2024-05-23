#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    fstream fileF1("F1.txt");
    ofstream fileF2("F2.txt");

    if (!fileF1.is_open() || !fileF2.is_open()) {
        cerr << "Unable to open files." << endl;
        return 1;
    }

    std::string line;
    while (getline(fileF1, line)) {
        // Проверяем, начинается ли строка с цифры
        if (!line.empty() && isdigit(line[0])) {
            fileF2 << line << endl;
        }
    }

    fileF1.close();
    fileF2.close();

    return 0;
}
