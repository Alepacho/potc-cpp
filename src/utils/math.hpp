#ifndef POTC_MATH_H
#define POTC_MATH_H

#include <cmath>
#include "random.hpp"

class Math {
    public:
        double PI = M_PI;
        int floor(double v) {
            return std::floor(v);
        }
        int abs(double v) {
            return std::abs(v);
        }
        double ceil(double v) {
            return std::ceil(v);
        }
        double sin(double v) {
            return std::sin(v);
        }
        double cos(double v) {
            return std::cos(v);
        }
        double sqrt(double v) {
            return std::sqrt(v);
        }
        double random() {
            Random rnd;
            return rnd.nextDouble(0.0, 1.0);
        }
        double atan2(double n, double m) {
            return std::atan2(n, m);
        }
};

#endif // POTC_MATH_H