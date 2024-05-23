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

//Функция метода дихотомии
double bisectionMethod(double (*equation)(double), double a, double b) {
    double c;
    while ((b - a) >= e) {
        c = (a + b) / 2.0;

        // Проверяем, находится ли корень между точками a и c
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
    // Ввод исходных данных: интервал [a, b] для уравнения 1
    double a1, b1;
    cout << "Введите интервал [a, b] для уравнения 1:";
    cin >> a1 >> b1;

    // Вычисление корня уравнения 1 методом дихотомии
    double root1 = bisectionMethod(equation1, a1, b1);
    cout << "Корни уравнения 1: " << root1 << endl;

    // Ввод исходных данных: интервал [a, b] для уравнения 2
    double a2, b2;
    cout << "Введите интервал [a, b] для уравнения 2: ";
    cin >> a2 >> b2;

    // Вычисление корня уравнения 2 методом дихотомии
    double root2 = bisectionMethod(equation2, a2, b2);
    cout << "Корни уравнения 2: " << root2 << endl;

    return 0;
}