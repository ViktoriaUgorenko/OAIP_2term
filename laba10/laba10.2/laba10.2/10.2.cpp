#include <iostream>
using namespace std;

int func(int x)
{
	int s = 0;
	if (x > 100)
		s = x + 10;

	else
		s = func(func(x + 4));

	return s;
}

int main(void)
{
	setlocale(LC_ALL, "Russian");
	int x;

	cout << "������� ��������������� �����: ";
	cin >> x;

	while (x < 0)
	{
		cout << "�������� ��������, ��������� �������: ";
		cin >> x;
	}
	cout << "��������� ���������� : " << func(x) << endl;
}