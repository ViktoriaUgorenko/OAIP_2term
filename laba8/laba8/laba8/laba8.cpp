#include <iostream>
#include "Header.h"
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");
	Queue* queue = create();
	int lol, a, t;
	bool exit = false;
	short razmer, razmerQueue;
	cout << "Меню" << endl;
	while (exit != true)
	{
		cout << "\n1-Добавить элемент\n2-Взять элемент из очереди\n3-Вывести очередь\n4-Очистить очередь\n5-Вычсиление максимального,минимального и количества\n6-Выйти\n";
		cin >> lol;
		switch (lol) {
		case 1: {
			cout << "Введите размер очереди:\n";
			cin >> razmer;
			for (int i = 0; i < razmer; i++) // Начинаем с 0
			{
				cout << "Введите число: ";
				cin >> a;
				adding(queue, a);
			}
			break;
		}
		case 2: {
			cout << "Элемент, который был взят, является " << del(queue) << endl;
			break;
		}
		case 3: {
			cout << "Вывод всей очереди:" << endl;
			allqueue(queue);
			break;
			cout << endl;
			break;
		}
		case 4: {t = clear(queue);
			if (t == 1)
				cout << "Очередь очищена";
			else if (t == 0)
				cout << "Очередь нельзя почистить";
			break;
		}
		case 5: {
			cout << "максимальный элемент" << max(queue) << "\n";
			cout << "минимальный элемент" << min(queue) << "\n";
			cout << "кол-во элементов" << length(queue) << "\n";
			break;
		}
		case 6: { exit = true; break; }
		}
	}
	system("pause");
	return 0;
}