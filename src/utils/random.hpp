#ifndef POTC_RANDOM_H
#define POTC_RANDOM_H

#include <cfloat>
#include <random>

class Random {
private:
    std::random_device rd;
    std::mt19937 eng;
    double nextNextGaussian;
    bool haveNextNextGaussian = false;
public:
    Random() {
        std::seed_seq s{ rd() };
        eng.seed(s);
    }
    Random(long seed) {
        std::seed_seq s{ seed };
        eng.seed(s);
    }

    int nextInt() {
        std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);
        return dist(eng);
    }
    int nextInt(int scale) {
        std::uniform_int_distribution<int> dist(0, scale - 1);
        return dist(eng);
    }
    double nextDouble() {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(eng);
    }
    double nextDouble(double n, double m) {
        std::uniform_real_distribution<double> dist(n, m);
        return dist(eng);
    }
    double nextGaussian() {
        // https://docs.oracle.com/javase/8/docs/api/java/util/Random.html#nextGaussian--
        if (haveNextNextGaussian) {
            haveNextNextGaussian = false;
            return nextNextGaussian;
        } else {
            double v1, v2, s;
            do {
                v1 = 2 * nextDouble() - 1;   // between -1.0 and 1.0
                v2 = 2 * nextDouble() - 1;   // between -1.0 and 1.0
                s = v1 * v1 + v2 * v2;
            } while (s >= 1 || s == 0);
            double multiplier = std::sqrt(-2 * std::log(s) / s);
            nextNextGaussian = v2 * multiplier;
            haveNextNextGaussian = true;
            return v1 * multiplier;
        }
    }
};

#endif // POTC_RANDOM_H