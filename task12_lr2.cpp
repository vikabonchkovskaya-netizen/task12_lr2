#include <iostream>

double cor(double x) {
    if (x < 0) return -1;
    double low = 0, high = x >= 1 ? x : 1, mid;
    for (int i = 0; i < 100; i++) {
        mid = (low + high) / 2;
        double square = mid * mid;
        if (square - x < 1e-10 && square - x > -1e-10) return mid;
        if (square < x) low = mid;
        else high = mid;
    }
    return mid;
}

// Решение биквадратного уравнения (1)
void solveType1(double a, double b, double c) {
    std::cout << "\nТип 1: Биквадратное уравнение\n";
    if (a == 0) {
        std::cout << "Это не биквадратное уравнение.\n";
        return;
    }

    // x^2 = t
    double D = b * b - 4 * a * c;
    if (D < 0) {
        std::cout << "Нет действительных корней.\n";
        return;
    }
    double t1 = (-b + cor(D)) / (2 * a);
    double t2 = (-b - cor(D)) / (2 * a);

    int count = 0;
    if (t1 >= 0) {
        double x1 = cor(t1);
        double x2 = -x1;
        std::cout << "x = " << x1 << " " << x2 << " ";
        count += 2;
    }
    if (t2 >= 0 && t2 != t1) {
        double x3 = cor(t2);
        double x4 = -x3;
        std::cout << x3 << " " << x4 << "\n";
        count += 2;
    }
    if (count == 0) std::cout << "Нет действительных корней.\n";
}

int main() {
    setlocale(LC_ALL, "RU");
    double a, b, c;
    std::cout << "Введите a, b, c: ";
    std::cin >> a >> b >> c;
    solveType1(a, b, c);
    return 0;
}