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
        Unnuun() : generator(rand_dev()) { }

        template<typename F>
        /*
            Generates `n` distinct values from [`min`, `max`) obtained from `n` calls to
            `gen_func`
            @pre    -   `min` smaller than `max`
                    -   `n` smaller no. elemnts in [`min`, `max`)
                    NOTE:   The following preconditions are not checked at compile time
                            Not meeting them might flood you with errors
                    -   `gen_func` should be able to return at least `n` distinct values
                    -   It is recommended that the return type of `gen_func` is an
                        unsigned integral type.
                        If not you should firstly pray, secondly make sure that:
                        *   The return type of `gen_func` should insertable in an std::set
                        *   The return type of `gen_func` should be comparable using `<=`
                        *   The return type of `gen_func` should be addable to using `+`

            @post   set with `n` values
        */
        static std::set< typename std::result_of<F()>::type >
            rand_n_unique(const size_t n, size_t min, size_t max, F gen_func)
        {
            assert(min < max); assert(n < max - min);

            using v_type = typename std::result_of<F()>::type;

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

        /*
            Generates `n` random numbers in [`min`, `max`)
            @pre    `min` smaller than `max`
                    `n` smaller no. elemnts in [`min`, `max`)
            @post   set with `n` values
        */
        std::set<uint_fast32_t> rand_n_unique(const size_t n, size_t min, size_t max)
        {
            return rand_n_unique(n, min, max, generator);
        }

        /*
            Generates `n` unique random numbers in [0, `max`)
            @pre    `n` smaller no. elemnts in [0, `max`)
            @post   set with `n` values
        */
        std::set<uint_fast32_t> rand_n_unique(const size_t n, size_t max)
        {
            return rand_n_unique(n, 0, max);
        }

        /*
            Generates `n` unique random numbers in [0, std::mt19937::max)
            @pre    `n` smaller no. elemnts in [0, std::mt19937::max)
            @post   set with `n` values
        */
        std::set<uint_fast32_t> rand_n_unique(const size_t n)
        {
            return rand_n_unique(n, 0, generator.max());
        }
};
