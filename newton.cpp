#include "fixed_point.h"

static const double dx = 1e-6;
template<typename T>
inline T square(T x) {
    return x * x;
}
inline std::function<double(double)> deriv(
        std::function<double(double)> f) {
    return [&](double x) {return (f(x+dx) - f(x))/dx;};
}

inline std::function<double(double)> newtonTransform(
        std::function<double(double)> f) {
    return [=](double x) {
        return x - f(x)/deriv(f)(x);
    };
}

double newtonMethod(std::function<double(double)> f, double guess) {
    return fixedPoint(newtonTransform(f), guess);
}

double sqrtByNewton(double x) {
    return newtonMethod([=](double y){return square(y) - x;}, 1.0);
}

int main() {
    std::cout << "cos fixed point: " << fixedPoint([](double x){return std::cos(x);}, 1.0) << '\n';
    std::cout << "sqrt 5: " << sqrtByFixedPoint(5.0) << '\n';
    std::cout << "sqrt 10: " << sqrtByFixedPoint(10.0) << '\n';
    std::cout << "sqrt 1000: " << sqrtByFixedPoint(1000.0) << '\n';
    std::cout << "sqrt 5: " << sqrtByFixedPoint1(5.0) << '\n';
    std::cout << "sqrt 10: " << sqrtByFixedPoint1(10.0) << '\n';
    std::cout << "sqrt 1000: " << sqrtByFixedPoint1(1000.0) << '\n';
    std::cout << "x^x=1000 :" << fixedPoint([](double x){return std::log(1000.0)/std::log(x);}, 2) << '\n';
    std::cout << "x^x=1000 :" << fixedPoint([](double x){return (x+log(1000.0)/log(x))/2;}, 2.0) << '\n';
    std::cout << "Newton Method\n";
    std::cout << "sqrt 5: " << sqrtByNewton(5.0) << '\n';
    std::cout << "sqrt 7: " << sqrtByNewton(7.0) << '\n';
    std::cout << "sqrt 10: " << sqrtByNewton(10.0) << '\n';
    std::cout << "sqrt 100: " << sqrtByNewton(100.0) << '\n';

}
