#ifndef _FIXED_POINT_H_
#define _FIXED_POINT_H_

#include <iostream>
#include <cmath>
#include <functional>

inline bool closeEnough(double a, double b);
inline double average(double a, double b);
// 平均阻尼
std::function<double(double)> averageDamp(std::function<double(double)> f) ;

double fixedPoint(std::function<double(double)> f, double firstGuess);

// 平均阻尼求平方根
double sqrtByFixedPoint(double x);
double sqrtByFixedPoint1(double x);

#endif
