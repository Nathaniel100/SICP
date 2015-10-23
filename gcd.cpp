#include <iostream>
#include <functional>
#include <sys/time.h>

/* *
 * Lame定理:
 * 如果欧几里得算法需要用k步计算出一对整数的GCD，那么这对数中较小的
 * 那个数必然大于或等于第k个斐波那契数
 * */

int32_t gcd(int32_t a, int32_t b) {
    if(b == 0) return a;
    else if(a < b) return gcd(b, a);
    else return gcd(b, (a%b));
}

void test(std::function<int32_t(int32_t, int32_t)> f) {
    int count = 0;
    int N = 4096 * 3;
    struct timeval t1, t2;
    ::gettimeofday(&t1, nullptr);
    for(int32_t i = 0; i < 100000; i++) {
        if(f(N, i) == N) {
            count++;
        }
    }
    ::gettimeofday(&t2, nullptr);
    std::cout << "count is " << count << '\n';
    std::cout << "cost: " << t2.tv_sec - t1.tv_sec << "s "
        << t2.tv_usec - t1.tv_usec << "us\n";
}

int main() {
    test(gcd);
}
