#include <iostream>
#include "Header.h"

int main() {
    setlocale(LC_ALL, "rus");
    Stack stack;
    int choice;
    std::string filename;

    do {
        std::cout << "\n1 - добавить элемент\n";
        std::cout << "2 - извлесь элемент\n";
        std::cout << "3 - вывести стек\n";
        std::cout << "4 - сохранить в файл\n";
        std::cout << "5 - считать из файла\n";
        std::cout << "6 - повтор€ющиес€ элементы\n";
        std::cout << "7 - очистить стек\n";
        std::cout << "0 - выход\n";
        std::cout << "ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string data;
            std::cout << "введите элемент: ";
            std::cin >> data;
            stack.push(data);
            break;
        }
        case 2: {
            std::cout << "извлеченный элемент: " << stack.pop() << std::endl;
            break;
        }
        case 3: {
            std::cout << "стек: ";
            stack.print();
            break;
        }
        case 4: {
            std::cout << "им€ файла дл€ сохранени€: ";
            std::cin >> filename;
            stack.toFile(filename);
            break;
        }
        case 5: {
            std::cout << "им€ файла дл€ чтени€: ";
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
            std::cout << "стек очищен\n";
            break;
        }
        case 0:
            std::cout << "\n";
            break;
        default:
            std::cout << "неверный выблор\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
