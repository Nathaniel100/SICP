#include <iostream>
#include <sys/time.h>

template<typename T>
static inline bool even(T v) {
    return (v & 1) == 0;
}
template<typename T>
static inline T square(T v) {
    return v*v;
}
uint64_t fibI(uint32_t n) {
    uint64_t a = 0;
    uint64_t b = 1;
    while(n-- != 0){
        uint64_t tmp = a;
        a = b;
        b += tmp;
    }
    return a;
}

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

/*
 * 对偶(1,0) T看作Tpq的对偶，按照
 * a = bq + aq + ap
 * b = bp + aq
 * Tpq两次，效果等同于Tp'q'一次
 * 对偶(1,0)看作p=0,q=1的特殊情况
 */
uint64_t fibFastInner(uint32_t count, uint64_t a, uint64_t b, uint64_t p, uint64_t q) {
    if(count == 0) return b;
    else if(even(count)) return fibFastInner(count/2, a, b, square(q)+square(p), square(q)+2*p*q);
    else return fibFastInner(count-1, b*q+a*q+a*p, b*p+a*q, p, q);
}

uint64_t fibFast(uint32_t n) {
    return fibFastInner(n, 1, 0, 0, 1);
}

template<typename F>
void test(F f, uint32_t n) {
    struct timeval t1, t2;
    ::gettimeofday(&t1, nullptr);
    uint64_t a = f(n);
    ::gettimeofday(&t2, nullptr);
    std::cout << "fib( "<< n << ") = " << a
        << " costs " << t2.tv_sec - t1.tv_sec <<  "s "
        << t2.tv_usec - t1.tv_usec << "us\n";
}

int main() {
    test(fib, 15);
    test(fib2, 15);
    test(fibFast, 15);
    test(fibI, 15);
    test(fib, 25);
    test(fib2, 25);
    test(fibFast, 25);
    test(fibI, 25);
    test(fib, 35);
    test(fib2, 35);
    test(fibFast, 35);
    test(fibI, 35);
    test(fib, 45);
    test(fib2, 45);
    test(fibFast, 45);
    test(fibI, 45);
}
