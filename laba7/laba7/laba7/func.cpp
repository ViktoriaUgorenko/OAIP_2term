#include "Header.h"
#include<map>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stack>

Stack::Stack() : head(nullptr) {}

Stack::~Stack() {
    clear();
}

void Stack::push(const std::string& newData) {
    Node* newNode = new Node{ newData, head };
    head = newNode;
}

std::string Stack::pop() {
    if (!head) {
        std::cerr << "стек пустой\n";
        return "";
    }
    std::string poppedData = head->data;
    Node* temp = head;
    head = head->next;
    delete temp;
    return poppedData;
}

void Stack::print() const {
    if (!head) {
        std::cout << "стек пустой\n";
        return;
    }
    Node* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void Stack::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void Stack::toFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        std::stack<std::string> tempStack; // Создаем временный стек
        Node* current = head;
        while (current) {
            tempStack.push(current->data); // Записываем данные стека во временный стек
            current = current->next;
        }
        // Теперь извлекаем элементы из временного стека и записываем их в файл
        while (!tempStack.empty()) {
            outFile << tempStack.top() << " ";
            tempStack.pop();
        }
        outFile.close();
        std::cout << "стек сохранен в файл\n";
    }
    else {
        std::cerr << "невозможно открыть файл\n";
    }
}


void Stack::fromFile(const std::string& filename) {
    clear();
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string data;
        while (inFile >> data) {
            push(data);
        }
        inFile.close();
        std::cout << "элементы считаны из файла\n";
    }
    else {
        std::cerr << "ошибка чтения файла\n";
    }
}

void Stack::countDuplicates() const {
    if (!head) {
        std::cout << "стек пустой\n";
        return;
    }
    std::map<std::string, int> counts;
    Node* current = head;
    while (current) {
        counts[current->data]++;
        current = current->next;
    }
    bool found = false;
    for (const auto& pair : counts) {
        if (pair.second > 1) {
            if (!found) {
                std::cout << "D:\n";
                found = true;
            }
            std::cout << "элемент '" << pair.first << "' повторяется " << pair.second << " раз\n";
        }
    }
    if (!found) {
        std::cout << "нет повторяющихся элементов\n";
    }
}
