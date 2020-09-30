/*
    Method to generate a random series of Unique Numbers from a Uniform Distribution
*/

#include <functional>
#include <cassert>
#include <random>
#include <set>
#include <iostream>

//TODO generic type
class Unnuun {
    private:
        //TODO parametrize rand generator
        std::random_device  rand_dev;
        std::mt19937        generator;

    public:
        Unnuun();
        std::set<uint32_t> rand_n_unique(const size_t n);
        std::set<uint32_t> rand_n_unique(const size_t n, size_t max);
        std::set<uint32_t> rand_n_unique(const size_t n, size_t min, size_t max);

        template<typename TF>
        std::set<uint32_t> rand_n_unique(const size_t n, size_t min, size_t max,
            TF&& gen_func)
        {
            assert(min < max); assert(n < max - min);

            std::set<uint32_t> gen;

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
