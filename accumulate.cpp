#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> v{{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }};
    int resultSum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "sum: " << resultSum << '\n';
    int resultProduct = std::accumulate(v.begin(), v.end(),
            1, std::multiplies<int>());
    std::cout << "product: " << resultProduct << '\n';
    std::string dashString = std::accumulate(v.begin()+1, v.end(),
            std::to_string(v[0]),
            [](const std::string &a, int b) {
                return a + "-" + std::to_string(b);
            });
    std::cout << "dash-seperated string: " << dashString << '\n';
}
