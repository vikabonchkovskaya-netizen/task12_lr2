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

int kvad(double a, double b, double c, double& x1, double& x2) {
    double D = b * b - 4 * a * c;
    if (D < 0) return 0;
    else if (D == 0) {
        x1 = -b / (2 * a);
        return 1;
    }
    else {
        x1 = (-b + cor(D)) / (2 * a);
        x2 = (-b - cor(D)) / (2 * a);
        return 2;
    }
}

void solveType2(double a, double b, double c) {
    std::cout << "Тип 2: Симметричное уравнение\n";
    if (a == 0) {
        std::cout << "Это не симметричное уравнение.\n";
        return;
    }

    // az^2 + bz + (c-2a) = 0
    double z1, z2;
    int zRoots = kvad(a, b, c - 2 * a, z1, z2);

    if (zRoots == 0) {
        std::cout << "Нет действительных корней.\n";
        return;
    }

    double x1, x2, x3, x4;
    int count = 0;

    if (zRoots >= 1) {
        int roots1 = kvad(1, -z1, 1, x1, x2);
        if (roots1 == 1) std::cout << "x = " << x1 << std::endl;
        if (roots1 == 2) std::cout << "x = " << x1 << ", " << x2 << std::endl;
        count += roots1;
    }
    if (zRoots == 2) {
        int roots2 = kvad(1, -z2, 1, x3, x4);
        if (roots2 == 1) std::cout << "x = " << x3 << std::endl;
        if (roots2 == 2) std::cout << "x = " << x3 << ", " << x4 << std::endl;
        count += roots2;
    }

    if (count == 0) std::cout << "Нет действительных корней.\n";
}


int main() {
    setlocale(LC_ALL, "RU");
    double a, b, c;
    std::cout << "Введите a, b, c: ";
    std::cin >> a >> b >> c;
    solveType2(a, b, c);
}