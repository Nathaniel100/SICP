#include <iostream>
#include <sys/time.h>

uint64_t fib(uint32_t n) {
    if(n == 0) return 0;
    else if(n == 1) return 1;
    else return fib(n-1) + fib(n-2);
}

uint64_t fibLinear(uint32_t n, uint32_t counter, uint64_t a, uint64_t b) {
    if(counter == n) return a;
    else return fibLinear(n, counter + 1, b, (a+b));
}

uint64_t fib2(uint32_t n) {
    return fibLinear(n, 0, 0, 1);
}

int main() {
    struct timeval t1, t2;
    ::gettimeofday(&t1, nullptr);
    uint64_t a = fib(40);
    ::gettimeofday(&t2, nullptr);
    std::cout << "fib(40)=" << a
        << " costs " << t2.tv_sec - t1.tv_sec <<  "s "
        << t2.tv_usec - t1.tv_usec << "us\n";

    ::gettimeofday(&t1, nullptr);
    a = fib2(40);
    ::gettimeofday(&t2, nullptr);
    std::cout << "fib(40)=" << a
        << " costs " << t2.tv_sec - t1.tv_sec <<  "s "
        << t2.tv_usec - t1.tv_usec << "us\n";
}
