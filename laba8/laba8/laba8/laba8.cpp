#include <iostream>
#include "Header.h"
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");
	Queue* queue = create();
	int lol, a, t;
	bool exit = false;
	short razmer, razmerQueue;
	cout << "����" << endl;
	while (exit != true)
	{
		cout << "\n1-�������� �������\n2-����� ������� �� �������\n3-������� �������\n4-�������� �������\n5-���������� �������������,������������ � ����������\n6-�����\n";
		cin >> lol;
		switch (lol) {
		case 1: {
			cout << "������� ������ �������:\n";
			cin >> razmer;
			for (int i = 0; i < razmer; i++) // �������� � 0
			{
				cout << "������� �����: ";
				cin >> a;
				adding(queue, a);
			}
			break;
		}
		case 2: {
			cout << "�������, ������� ��� ����, �������� " << del(queue) << endl;
			break;
		}
		case 3: {
			cout << "����� ���� �������:" << endl;
			allqueue(queue);
			break;
			cout << endl;
			break;
		}
		case 4: {t = clear(queue);
			if (t == 1)
				cout << "������� �������";
			else if (t == 0)
				cout << "������� ������ ���������";
			break;
		}
		case 5: {
			cout << "������������ �������" << max(queue) << "\n";
			cout << "����������� �������" << min(queue) << "\n";
			cout << "���-�� ���������" << length(queue) << "\n";
			break;
		}
		case 6: { exit = true; break; }
		}
	}
	system("pause");
	return 0;
}