#include <iostream>
#include <cmath>
using namespace std;
const double e = 0.001;

double equation1(double x) {
    return pow(x, 3) + 5 * x - 1;
}

double equation2(double x) {
    return pow(x , 2) + 1 / x;
}

//������� ������ ���������
double bisectionMethod(double (*equation)(double), double a, double b) {
    double c;
    while ((b - a) >= e) {
        c = (a + b) / 2.0;

        // ���������, ��������� �� ������ ����� ������� a � c
        if (equation(c) == 0.0)
            break;
        else if (equation(c) * equation(a) < 0)
            b = c;
        else
            a = c;
    }
    return c;
}

int main() {
    setlocale(LC_ALL, "rus");
    // ���� �������� ������: �������� [a, b] ��� ��������� 1
    double a1, b1;
    cout << "������� �������� [a, b] ��� ��������� 1:";
    cin >> a1 >> b1;

    // ���������� ����� ��������� 1 ������� ���������
    double root1 = bisectionMethod(equation1, a1, b1);
    cout << "����� ��������� 1: " << root1 << endl;

    // ���� �������� ������: �������� [a, b] ��� ��������� 2
    double a2, b2;
    cout << "������� �������� [a, b] ��� ��������� 2: ";
    cin >> a2 >> b2;

    // ���������� ����� ��������� 2 ������� ���������
    double root2 = bisectionMethod(equation2, a2, b2);
    cout << "����� ��������� 2: " << root2 << endl;

    return 0;
}