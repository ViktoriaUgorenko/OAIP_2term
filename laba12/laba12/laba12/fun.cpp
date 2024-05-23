
#include "zag.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

void AAA::print()
{
    std::cout << x;
}

namespace heap
{
    int pozmin = -100000, minnum = 10000000;

    Heap create(int maxsize, CMP(*f)(void*, void*))
    {
        return *(new Heap(maxsize, f));
    }

    int Heap::left(int ix)
    {
        return (2 * ix + 1 >= size) ? -1 : (2 * ix + 1);
    }

    int Heap::right(int ix)
    {
        return (2 * ix + 2 >= size) ? -1 : (2 * ix + 2);
    }

    int Heap::parent(int ix)
    {
        return (ix + 1) / 2 - 1;
    }

    void Heap::swap(int i, int j)
    {
        void* buf = storage[i];
        storage[i] = storage[j];
        storage[j] = buf;
    }

    void Heap::heapify(int ix)
    {
        int l = left(ix), r = right(ix), irl = ix;
        if (l > 0)
        {
            if (isGreat(storage[l], storage[ix])) irl = l;
            if (r > 0 && isGreat(storage[r], storage[irl]))  irl = r;
            if (irl != ix)
            {
                swap(ix, irl);
                heapify(irl);
            }
        }
    }

    void Heap::insert(void* x, int k)
    {
        int i;
        if (!isFull())
        {
            storage[i = ++size - 1] = x;
            while (i > 0 && isLess(storage[parent(i)], storage[i]))
            {
                swap(parent(i), i);
                i = parent(i);
            }
        }
    }

    void* Heap::extractMax()
    {
        void* rc = nullptr;
        if (!isEmpty())
        {
            rc = storage[0];
            storage[0] = storage[size - 1];
            size--;
            heapify(0);
        }
        return rc;
    }

    void Heap::extractMin(heap::Heap& h3, heap::Heap& h1)
    {
        if (h1.size == 0) {
            cout << "Куча пуста\n";
            return;
        }
        for (int i = 0; i < size; i++) {
#define A1 ((AAA*)h1.storage[i])
            if (A1->x < minnum) {
                minnum = A1->x;
                pozmin = i;
            }
        }
        storage[pozmin] = storage[size - 1];
        h1.size--;
        if (!isEmpty())
        {
            while (!h1.isEmpty()) {
#define A1 ((AAA*)h1.storage[0])
                h3.insert(A1, A1->x);
                h1.extractMax();
            }
        }
        pozmin = -100000, minnum = 10000000;
    }

    void* Heap::extractI(int h)
    {
        void* rc = nullptr;
        if (h >= size || h < 0) {
            cout << "Некорректный номер\n";
            return nullptr;
        }
        if (!isEmpty())
        {
            rc = storage[h];
            if (h != size - 1) {
                swap(h, size - 1);
            }
            size--;
            heapify(0);
            heapify(h);
        }
        return rc;
    }

    void Heap::scan(int i) const     // Вывод значений элементов на экран
    {
        vector<int> a = { 52 };
        vector<int> b = { 26, 24, 28 };
        vector<int> c = { 16, 10, 16, 8, 16, 12, 16 };
        vector<int> d = { 8, 8, 6, 6, 6, 8, 6, 4, 6, 8, 8, 4, 8, 8, 8 };
        vector<int> e = { 4, 4, 4, 4, 4, 4, 3, 4, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 4, 3, 3, 4, 4, 4, 4, 4 };
        vector<int> vnesh = { 66, 40, 28, 20, 16, 12 };
        int y = 0;
        int level = 0;
        bool t = false;
        int current = 0;
        int j;
        std::cout << '\n';
        if (size == 0) {
            std::cout << "Куча пуста\n";
            return;
        }
        std::cout << std::setw(vnesh[level]) << std::setfill(' ');
        level++;
        ((AAA*)storage[current])->print();
        current++;
        cout << '\n';
        y = 2;
        for (int i = 0; current < size; i++) {
            if (!t) {
                std::cout << std::setw(vnesh[level]) << std::setfill(' ');
                t = true;
                j = 0;
            }
            ((AAA*)storage[current])->print();
            if (level == 1 && j < a.size()) {
                std::cout << std::setw(a[j]) << std::setfill(' ');
                j++;
            }
            else if (level == 2 && j < b.size()) {
                std::cout << std::setw(b[j]) << std::setfill(' ');
                j++;
            }
            else if (level == 3 && j < c.size()) {
                std::cout << std::setw(c[j]) << std::setfill(' ');
                j++;
            }
            else if (level == 4 && j < d.size()) {
                std::cout << std::setw(d[j]) << std::setfill(' ');
                j++;
            }
            else if (level == 5 && j < e.size()) {
                std::cout << std::setw(e[j]) << std::setfill(' ');
                j++;
            }
            current++;
            if (current > y) {
                cout << '\n';
                level++;
                y += pow(2, level);
                t = false;
            }
        }
        cout << '\n';
    }

    void Heap::unionHeap(heap::Heap buf, heap::Heap& h1) {
        while (!buf.isEmpty()) {
#define A1 ((AAA*)buf.storage[0])
            h1.insert(A1, A1->x);
            buf.extractMax();
        }
    }
}