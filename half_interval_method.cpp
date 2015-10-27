#include <iostream>
#include <functional>
#include <cmath>

static inline bool closeEnough(double a, double b) {
    return std::abs(a-b) < 1e-3;
}

double searchBinary(std::function<double(double)> f, double neg, double pos) {
    double mid = (neg + pos) / 2;
    if(closeEnough(neg, pos)) return mid;
    double test = f(mid);
    if(test > 0) {
        return searchBinary(f, neg, mid);
    } else if(test < 0) {
        return searchBinary(f, mid, pos);
    } else {
        return mid;
    }
}

double halfIntervalMethod(std::function<double(double)> f, double a, double b) {
    double aV = f(a);
    double bV = f(b);
    if(aV < 0 && bV > 0) return searchBinary(f, a, b);
    else if(aV > 0 && bV < 0) return searchBinary(f, b, a);
    else throw "Illegal section";
}

int main() {
    std::cout << halfIntervalMethod([](double x){return x*x*x - 2*x -3;}, 1, 2) << '\n';
}

