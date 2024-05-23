#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Функция для подсчета гласных в слове
int countVowels(const string& word) {
    int count = 0;
    string vowels = "aeiouAEIOU";
    for (char c : word) {
        if (vowels.find(c) != string::npos) {
            count++;
        }
    }
    return count;
}

// Функция для определения номера слова с наибольшим количеством гласных
int findMaxVowelWord(const string& line) {
    istringstream iss(line);
    string word;
    int maxVowelCount = 0;
    int maxVowelWordIndex = -1;
    int currentIndex = 0;
    while (iss >> word) {
        int vowelCount = countVowels(word);
        if (vowelCount > maxVowelCount) {
            maxVowelCount = vowelCount;
            maxVowelWordIndex = currentIndex + 1; // С учетом 1-индексации
        }
        currentIndex++;
    }
    return maxVowelWordIndex;
}

int main() {
    ifstream inputFile("FILE1.txt");
    ofstream outputFile("FILE2.txt");
    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Не удалось открыть файлы." << endl;
        return 1;
    }

    std::string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string word;
        int wordCount = 0;
        while (iss >> word) {
            wordCount++;
        }
        if (wordCount > 2) {
            int maxVowelWordIndex = findMaxVowelWord(line);
            outputFile << line << " (Слово с наибольшим количеством гласных - " << maxVowelWordIndex << ")\n";
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
