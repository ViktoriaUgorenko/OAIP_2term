#include <iostream>
#include "Header.h"

int main() {
    setlocale(LC_ALL, "rus");
    Stack stack;
    int choice;
    std::string filename;

    do {
        std::cout << "\n1 - �������� �������\n";
        std::cout << "2 - ������� �������\n";
        std::cout << "3 - ������� ����\n";
        std::cout << "4 - ��������� � ����\n";
        std::cout << "5 - ������� �� �����\n";
        std::cout << "6 - ������������� ��������\n";
        std::cout << "7 - �������� ����\n";
        std::cout << "0 - �����\n";
        std::cout << "��� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string data;
            std::cout << "������� �������: ";
            std::cin >> data;
            stack.push(data);
            break;
        }
        case 2: {
            std::cout << "����������� �������: " << stack.pop() << std::endl;
            break;
        }
        case 3: {
            std::cout << "����: ";
            stack.print();
            break;
        }
        case 4: {
            std::cout << "��� ����� ��� ����������: ";
            std::cin >> filename;
            stack.toFile(filename);
            break;
        }
        case 5: {
            std::cout << "��� ����� ��� ������: ";
            std::cin >> filename;
            stack.fromFile(filename);
            break;
        }
        case 6: {
            stack.countDuplicates();
            break;
        }
        case 7: {
            stack.clear();
            std::cout << "���� ������\n";
            break;
        }
        case 0:
            std::cout << "\n";
            break;
        default:
            std::cout << "�������� ������\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
