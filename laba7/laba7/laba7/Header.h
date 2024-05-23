#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>
#include <string>

struct Node {
    std::string data;
    Node* next;
};

class Stack {
private:
    Node* head;

public:
    Stack();
    ~Stack();

    void push(const std::string& newData);
    std::string pop();
    void print() const;
    void clear();
    void toFile(const std::string& filename) const;
    void fromFile(const std::string& filename);
    void countDuplicates() const;
};

#endif
