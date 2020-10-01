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
        /*
            Function that accepts a generic generation function `gen_func`
            Returns
        */
        static std::set< typename std::result_of<F()>::type >
            rand_n_unique(const size_t n, size_t min, size_t max, F gen_func)
        {
            using v_type = typename std::result_of<F()>::type;
            assert(min < max); assert(n < max - min);

            std::set< v_type > gen;

            for (size_t i = 0; i < n; i++) {
                v_type r = min + gen_func()%(max - min);

                for(v_type x : gen) {
                    if(x <= r) r++;
                    else break;
                }

                max--;

                gen.insert(r);
            }

            return gen;
        }
};
