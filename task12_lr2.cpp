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

// кубический корень 
double myCbrt(double x) {
    double low, high, mid;
    if (x >= 0) { low = 0; high = (x >= 1 ? x : 1); }
    else { low = (x <= -1 ? x : -1); high = 0; }

    for (int i = 0; i < 100; i++) {
        mid = (low + high) / 2;
        double cube = mid * mid * mid;
        if (cube < x) low = mid;
        else high = mid;
    }
    return mid;
}

// cos(x) через ряд тейлора
double myCos(double x) {
    // [-pi, pi]
    const double PI = 3.1415926535;
    while (x > PI) x -= 2 * PI;
    while (x < -PI) x += 2 * PI;

    double term = 1.0;
    double result = 1.0;
    double x2 = x * x;
    for (int n = 1; n < 20; n++) {
        term *= -x2 / ((2 * n - 1) * (2 * n));
        result += term;
    }
    return result;
}


double arccos(double x) {
    if (x == 0) return 3.1415926535 / 2;
    if (x == 1) return 0;
    if (x == -1) return 3.1415926535;

    double result = x;
    double term = x;
    double x2 = x * x;

    for (int n = 1; n < 20; n++) {
        term *= x2 * (2.0 * n - 1) * (2.0 * n - 1) / ((2.0 * n) * (2.0 * n + 1));
        result += term;
        if (term < 1e-12 && term > -1e-12) break;
    }

    return 3.1415926535 / 2 - result; // arccos(x) = π/2 - arcsin(x)
}

int main() {
    setlocale(LC_ALL, "RU");
    double p, q;
    std::cout << "Введите p и q: ";
    std::cin >> p >> q;

    double D = (q / 2.0) * (q / 2.0) + (p / 3.0) * (p / 3.0) * (p / 3.0);

    if (D > 0) {
        // 1 корень
        double A = myCbrt(-q / 2.0 + cor(D));
        double B = myCbrt(-q / 2.0 - cor(D));
        double x = A + B;
        std::cout << "Один действительный корень: x = " << x << std::endl;
    }
    else if (D == 0) {
        // 2 или 3 корень
        double x1 = 2 * myCbrt(-q / 2.0);
        double x2 = -myCbrt(-q / 2.0);
        std::cout << "Действительные корни: x1 = " << x1 << ", x2 = x3 = " << x2 << std::endl;
    }
    else {
        // 3 корня
        const double PI = 3.1415926535;
        double r = cor(-(p / 3.0) * (p / 3.0) * (p / 3.0)); // sqrt(-(p/3)^3)
        double phi = arccos(-q / (2 * r));

        double rho = cor(-p / 3.0); // sqrt(-p/3)

        double x1 = 2 * rho * myCos(phi / 3.0);
        double x2 = 2 * rho * myCos((phi + 2 * PI) / 3.0);
        double x3 = 2 * rho * myCos((phi + 4 * PI) / 3.0);

        std::cout << "Три действительных корня:\n";
        std::cout << "x1 = " << x1 << "\n";
        std::cout << "x2 = " << x2 << "\n";
        std::cout << "x3 = " << x3 << std::endl;
    }

    return 0;
}
