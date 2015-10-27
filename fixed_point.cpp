#include <iostream>
#include <cmath>
#include <functional>


const static double tolerance = 1e-4;

static inline bool closeEnough(double a, double b) {
    return std::abs(a-b) < tolerance;
}

double fixedPoint(std::function<double(double)> f, double firstGuess) {
    double nextGuess = f(firstGuess);
    if(closeEnough(nextGuess, firstGuess)) return firstGuess;
//    std::cout << nextGuess << '\n';
    return fixedPoint(f, nextGuess);
}

// 平均阻尼
double sqrtByFixedPoint(double x) {
    return fixedPoint([=](double y){return (y+x/y)/2;}, 1.0);
}

double goldPartition() {
    return fixedPoint([](double x){return 1+1/x;}, 1.0);
}

int main() {
    std::cout << "cos fixed point: " << fixedPoint([](double x){return std::cos(x);}, 1.0) << '\n';
    std::cout << "sqrt 5: " << sqrtByFixedPoint(5.0) << '\n';
    std::cout << "sqrt 10: " << sqrtByFixedPoint(10.0) << '\n';
    std::cout << "sqrt 1000: " << sqrtByFixedPoint(1000.0) << '\n';
    std::cout << "gold partition: " << goldPartition() << '\n';
    std::cout << "x^x=1000 :" << fixedPoint([](double x){return std::log(1000.0)/std::log(x);}, 2) << '\n';
    std::cout << "x^x=1000 :" << fixedPoint([](double x){return (x+log(1000.0)/log(x))/2;}, 2.0) << '\n';
}
