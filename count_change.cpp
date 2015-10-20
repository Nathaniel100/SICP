#include <iostream>
#include <array>
#include <sys/time.h>
#include <functional>

/* *
 * 1 5 10 25 50美分零钱
 * 1美元有多少种换法
 *
 * 两种情况:
 * 不包含最大零钱a,总金额其他的分法
 * 包含最大零钱a,
 * */
/* -- my -- */
static const uint32_t CHANGES_COUNT = 5;
static const std::array<uint32_t, CHANGES_COUNT> CHANGES= {1, 5, 10, 25, 50};

uint32_t forChange(uint32_t total, uint32_t pos) {
    if(pos == 0 || total == 0) return 1;
    uint32_t maxCount = total / CHANGES[pos];
    uint32_t result = 0;
    for(uint32_t i = 0; i <= maxCount; i++) {
        result += forChange(total - i * CHANGES[pos], pos-1);
    }
    return result;
}

uint32_t countChangeMy(uint32_t total) {
    return forChange(total, CHANGES_COUNT - 1);
}

uint32_t cc(int32_t amount, uint32_t kindsOfCoins) {
    static auto denom = [](uint32_t kind) {
        switch(kind) {
            case 1: return 1;
            case 2: return 5;
            case 3: return 10;
            case 4: return 25;
            default: return 50;
        }
    };
    if(amount == 0 || kindsOfCoins == 1) return 1;
    else if(amount < 0 || kindsOfCoins == 0) return 0;
    else return cc(amount, kindsOfCoins - 1) + cc(amount - denom(kindsOfCoins), kindsOfCoins);
}

uint32_t countChange(int32_t amount) {
    return cc(amount, 5);
}

void test(std::function<uint32_t(uint32_t)> f) {
    int n = 0;
    struct timeval t1, t2;
    ::gettimeofday(&t1, nullptr);
    std::cout << "change count : " << n << ", " << f(n) << '\n';
    n = 1;
    std::cout << "change count : " << n << ", " << f(n) << '\n';
    n = 10;
    std::cout << "change count : " << n << ", " << f(n) << '\n';
    n = 100;
    std::cout << "change count : " << n << ", " << f(n) << '\n';
    n = 1000;
    std::cout << "change count : " << n << ", " << f(n) << '\n';
    n = 10000;
    std::cout << "change count : " << n << ", " << f(n) << '\n';
    ::gettimeofday(&t2, nullptr);
    std::cout << "cost: " << t2.tv_sec - t1.tv_sec << "s, " << t2.tv_usec - t1.tv_usec << "us\n";

}

int main() {
    std::cout << "--------test MY---------\n";
    test(countChangeMy);
    std::cout << "--------test book's---------\n";
    test(countChange);
    return 0;
}
