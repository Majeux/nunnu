/*
    Method to generate a random series of Unique Numbers from a Uniform Distribution
*/

#include <type_traits>
#include <cassert>
#include <random>
#include <set>
#include <iostream>

class Unnuun {
    private:
        std::random_device  rand_dev;
        std::mt19937        generator;

    public:
        Unnuun();
        std::set<uint32_t> rand_n_unique(const size_t n);
        std::set<uint32_t> rand_n_unique(const size_t n, size_t max);
        std::set<uint32_t> rand_n_unique(const size_t n, size_t min, size_t max);

        template<typename F>
        static std::set< typename std::result_of<F()>::type > //return set of whatever `F gen_func` returns
            rand_n_unique(const size_t n, size_t min, size_t max, F gen_func)
        {
            assert(min < max); assert(n < max - min);

            std::set< typename std::result_of<F()>::type > gen;

            for (size_t i = 0; i < n; i++) {
                size_t r = min + gen_func()%(max - min);

                for(size_t x : gen) {
                    if(x <= r) r++;
                    else break;
                }

                max--;

                gen.insert(r);
            }

            return gen;
        }
};
