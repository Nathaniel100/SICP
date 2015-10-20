#include <iostream>
#include <cmath>
#include <cassert>
#include <array>
#include <sys/time.h>

static inline double average(double a, double b) {
    return (a + b) / 2;
}

template <typename T>
static inline T square(const T& t) {
    return t * t;
}

static inline bool goodEnough(double x, double guess) {
    return std::abs(x - square(guess)) < 1e-6;
}

static inline double improveGuess(double x, double guess) {
    return average(guess, x / guess);
}

static double sqrtIter(double x, double guess) {
    if(goodEnough(x, guess)) return guess;
    return sqrtIter(x, improveGuess(x, guess));
}

double sqrtMy(double x) {
    return sqrtIter(x, 1.0);
}

double sqrtIter2(double x, double guess) {
    static auto averageLam = [](double a, double b) {
        return (a + b) / 2;
    };
    static auto improveGuessLam = [](double a, double guess) {
        return averageLam(guess, a / guess);
    };
    static auto goodEnoughLam = [](double a, double guess) {
        return std::abs(a - square(guess)) < 1e-6;
    };
    if(goodEnoughLam(x, guess)) return guess;
    else return sqrtIter2(x, improveGuessLam(x, guess));
}

double sqrtMy2(double x) {
    return sqrtIter2(x, 1.0);
}

int main() {
    struct timeval t1, t2;
    std::cout << "sqrt(9) = " << sqrtMy(9) << "\n";
    std::cout << "sqrt(10) = " << sqrtMy(10) << "\n";
    std::cout << "sqrt(50) = " << sqrtMy(50) << "\n";
//    std::array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    std::array<int, 100> a;
    std::fill(a.begin(), a.end(), 1000);

    ::gettimeofday(&t1, nullptr);
    std::for_each(a.begin(), a.end(), [](int a) {
           std::cout << "sqrt(" << a << ") = " << sqrtMy(a) << '\n';
    });
    ::gettimeofday(&t2, nullptr);
    std::cout << "cost: " << t2.tv_sec -t1.tv_sec << "s " << t2.tv_usec - t1.tv_usec << "us\n";
    std::cout << "\n";
    ::gettimeofday(&t1, nullptr);
    std::for_each(a.begin(), a.end(), [](int a) {
           std::cout << "sqrt(" << a << ") = " << sqrtMy2(a) << '\n';
    });
    ::gettimeofday(&t2, nullptr);
    std::cout << "cost: " << t2.tv_sec -t1.tv_sec << "s " << t2.tv_usec - t1.tv_usec << "us\n";
    return 0;
}
