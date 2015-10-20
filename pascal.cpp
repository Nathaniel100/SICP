#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <string>

/* *
 * 帕斯卡三角形
 *
 *                      1
 *                  1       1
 *              1       2       1
 *          1       3       3       1
 *      1       4       6       4       1
 *  1       5       10      10      5       1
 * 递归实现帕斯卡三角形
 * */

// line从1开始, col从1到line，返回帕斯卡三角形值
uint32_t pascal(uint32_t line, uint32_t col) {
    assert(line >= col && line >= 1 && col >= 1);
    if(line == 1 || col == 1 || line == col) return 1;
    return pascal(line-1, col-1) + pascal(line-1, col);
}

void printPascal(uint32_t line) {
    std::ostringstream oss;
    for(uint32_t i = 1; i <= line; i++) {
        oss << std::string(line-i, '\t');
        for(uint32_t j = 1; j <= i; j++) {
            oss << pascal(i, j);
            if(i != j) {
                oss << "\t\t";
            }
        }
        oss << std::string(line-i, '\t') << '\n';
    }
    std::cout << oss.str();
}

int main() {
    printPascal(7);
}

