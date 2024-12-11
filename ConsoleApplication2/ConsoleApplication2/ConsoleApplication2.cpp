#include <iostream>
#include <cmath>
using namespace std;

// Определение функции f(x)
double f(double x) 
{
    return acos(x) - sqrt(1 - 0.3 * pow(x, 3));
}

// Определение производной f'(x)
double df(double x) 
{
    if (x == 1 || (1 - 0.3 * pow(x, 3)) <= 0) 
    {
        throw runtime_error("Не находится в интервале");
    }
    double df_acos = -1 / sqrt(1 - pow(x, 2)); // производная arccos
    double df_sqrt = -0.9 * pow(x, 2) / (2 * sqrt(1 - 0.3 * pow(x, 3))); // производная числа sqrt(1 - 0.3 * pow(x, 3))
    return df_acos + df_sqrt;
}

// Метод Ньютона
double newtonMethod(double x0, double tol = 1e-6, int max_iter = 100) 
{
    double x = x0;
    cout << "Начальное приближение: x = " << x << endl;
    for (int i = 0; i < max_iter; ++i) 
    {
        double f_val = f(x);
        double df_val = df(x);
        if (abs(df_val) < 1e-12) 
        {  
            throw runtime_error("Деление на ноль");
        }
        double x_new = x - f_val / df_val;
        cout << "Шаг " << i + 1 << ": x = " << x_new << ", f(x) = " << f_val << endl;
        if (abs(x_new - x) < tol)  // проверка сходимости
        { 
            return x_new;
        }
        x = x_new;
    }
    throw runtime_error("Ошибка в алгоритме");
}

double truncate(double value, int decimalPlaces) // функция для сокращения числа на 4 символа
{
    double factor = pow(10, decimalPlaces);
    return trunc(value * factor) / factor;
}

int main() 
{
    setlocale(LC_ALL, "ru");
    float x0 = 0.5;  // случайно выбранная точка на интервале
    double root = newtonMethod(x0); // вызов метода
    root = truncate(root, 4); // ограничение по 4 символам после запятой
    cout << "Корень уравнения: x = "<< root << endl;
    return 0;
}
