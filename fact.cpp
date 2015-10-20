#include <iostream>
#include <cstdint>
#include <array>
#include <sys/time.h>

int i = 0;
uint64_t fact(uint32_t n) {
    i = 1;
    if(n == 0) return 0;
    if(n == 1) return 1;
    return n * fact(n-1);
}

static uint64_t factLinear(uint64_t result, uint32_t counter, uint32_t n) {
    if(counter > n) return result;
    return factLinear(result * counter, counter + 1, n);
}

uint64_t fact2(uint32_t n) {
    i = 2;
    if(n == 0) return 0;
    return factLinear(1, 1, n);
}

uint64_t fact3(uint32_t n) {
    i = 3;
    if(n == 0) return 0;
    uint32_t i = 1;
    uint64_t result = 1;
    while (i <= n) {
        result *= i;
        i++;
    }
    return result;
}

template<typename T, std::size_t N>
std::array<T, N> range() {
    T i = 0;
    std::array<T, N> a;
    while(i < N) {
        a[i]= i;
        i++;
    }
    return a;
}

const static size_t NUM = 10000;

int main() {
    std::cout << "fact(50) = " <<  fact(50) << '\n';
    std::cout << "fact(50) = " <<  fact2(50) << '\n';
    std::cout << "fact(50) = " <<  fact3(50) << '\n';
    std::array<uint32_t, NUM> a = range<uint32_t, NUM>();
    struct timeval t1, t2;
    ::gettimeofday(&t1, nullptr);
    std::for_each(a.begin(), a.end(), fact);
    ::gettimeofday(&t2, nullptr);
    std::cout << "fact cost: " << t2.tv_sec - t1.tv_sec << "s" << t2.tv_usec - t1.tv_usec << "us\n";

    ::gettimeofday(&t1, nullptr);
    std::for_each(a.begin(), a.end(), fact2);
    ::gettimeofday(&t2, nullptr);
    std::cout << "fact cost: " << t2.tv_sec - t1.tv_sec << "s" << t2.tv_usec - t1.tv_usec << "us\n";

    ::gettimeofday(&t1, nullptr);
    std::for_each(a.begin(), a.end(), fact3);
    ::gettimeofday(&t2, nullptr);
    std::cout << "fact cost: " << t2.tv_sec - t1.tv_sec << "s" << t2.tv_usec - t1.tv_usec << "us\n";

    std::cout << "i: " << i << '\n';
    return 0;
}
