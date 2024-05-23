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
        std::cerr << "���� ������\n";
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
        std::cout << "���� ������\n";
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
        std::stack<std::string> tempStack; // ������� ��������� ����
        Node* current = head;
        while (current) {
            tempStack.push(current->data); // ���������� ������ ����� �� ��������� ����
            current = current->next;
        }
        // ������ ��������� �������� �� ���������� ����� � ���������� �� � ����
        while (!tempStack.empty()) {
            outFile << tempStack.top() << " ";
            tempStack.pop();
        }
        outFile.close();
        std::cout << "���� �������� � ����\n";
    }
    else {
        std::cerr << "���������� ������� ����\n";
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
        std::cout << "�������� ������� �� �����\n";
    }
    else {
        std::cerr << "������ ������ �����\n";
    }
}

void Stack::countDuplicates() const {
    if (!head) {
        std::cout << "���� ������\n";
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
            std::cout << "������� '" << pair.first << "' ����������� " << pair.second << " ���\n";
        }
    }
    if (!found) {
        std::cout << "��� ������������� ���������\n";
    }
}
