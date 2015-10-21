#include <iostream>
#include <functional>
#include <sys/time.h>

uint64_t expt1(uint32_t b, uint32_t n) {
    if(n == 0) return 1;
    return b * expt1(b, n - 1);
}

static uint64_t expt2Inner(uint32_t b, uint32_t n, uint64_t r) {
    if(n == 0) return r;
    return expt2Inner(b, n-1, r * b);
}
uint64_t expt2(uint32_t b, uint32_t n) {
    return expt2Inner(b, n, 1);
}

uint64_t exptFast(uint32_t b, uint32_t n) {
    auto square = [](uint64_t a) {return a * a;};
    if(n == 0) return 1;
    else if(n % 2 == 0) return square(exptFast(b, n/2));
    else return b * exptFast(b, n - 1);
}

uint64_t exptFastIter(uint64_t b, uint32_t n, uint64_t r) {
    // a^n = (a^(n/2))^2 = (a^2)^(n/2)
    auto square = [](uint64_t a) {return a * a;};
    if(n == 0) return r;
    else if(n % 2 == 0) return exptFastIter(square(b), n/2, r);
    else return exptFastIter(b, n-1, b * r);
}

uint64_t exptFast2(uint32_t b, uint32_t n) {
    return exptFastIter(static_cast<uint64_t>(b), n, 1);
}

const static uint32_t N = 60;
void test(std::function<uint64_t(uint32_t, uint32_t)> f, uint32_t b, uint32_t n) {
    uint64_t r = 0;
    struct timeval t1, t2;
    ::gettimeofday(&t1, nullptr);
    r = f(b, n);
    ::gettimeofday(&t2, nullptr);
    std::cout << "expt("<< b << "," << n << ") = " << r << '\n';
    std::cout << "cost: " << t2.tv_sec - t1.tv_sec << "s " << t2.tv_usec - t1.tv_usec << "us\n";
}

int main() {
    test(expt1, 2, N);
    test(expt2, 2, N);
    test(exptFast, 2, N);
    test(exptFast2, 2, N);
}
