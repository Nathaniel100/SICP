#include <iostream>
#include <functional>
#include <cassert>

template<typename T>
T cube(T a) {
    return a*a*a;
}

int32_t sumIntergers(int32_t a, int32_t b) {
    if(a > b) return 0;
    else return a + sumIntergers(a+1, b);
}

int32_t sumCubes(int32_t a, int32_t b) {
    if(a > b) return 0;
    else return cube(a) + sumCubes(a+1, b);
}

// PI/8 = 1/(1*3) + 1/(5*7) + 1/(9*11) + ...
double piSum(int32_t a, int32_t b) {
    if(a > b) return 0;
    else return (1.0 /(a*(a+2))) + piSum(a+4, b);
}

template<typename R, typename T>
R sum(std::function<R(T)> term, T a, std::function<T(T)> next, T b) {
    if(a > b) return 0;
    return term(a) + sum(term, next(a), next, b);
}

template<typename F>
double integral(F f, int a, int b, double dx) {
    auto addDx = [=](double x){return x + dx;};
    return sum<double, double>(f,(a+dx/2), addDx, b) * dx;
}

int main() {
    std::cout << "1-100 sum: " << sumIntergers(1, 100) << '\n';
    std::cout << "1-100  cube sum: " << sumCubes(1, 100) << '\n';
    std::cout << "pi/8: " << piSum(1, 100) << '\n';

    std::cout << "Abstract sum" << '\n';
    std::cout << "1-100 sum: "
        << sum<int32_t, int32_t>(
                [](int32_t a){return a;},
                1,
                [](int32_t a){return a+1;},
                100)
        << '\n';
    std::cout << "1-100 cube sum: "
        << sum<int32_t, int32_t>(
                cube<int32_t>,
                1,
                [](int32_t a){return a+1;},
                100)
        << '\n';
    std::cout << "pi/8: "
        << sum<double, int32_t>(
                [](int32_t a)->double{return 1.0/(a*(a+2));},
                1,
                [](int32_t a){return a+4;},
                100)
        << '\n';
    std::cout << "integral cube 0-1: " << integral(cube<double>, 0, 1, 0.01) << '\n';

}
