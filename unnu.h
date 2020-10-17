#include <type_traits>
#include <limits>
#include <cassert>
#include <set>

namespace Unnu {

    struct Range {
        size_t  min;
        size_t  max;
    };

    namespace { //anonymous/private namespace for assertions

        /*
            Verifies if the arguments passed to `n_unique_from` are correct
        */
        template<typename F>
        void assert_arguments(const F generator, const size_t n, const Range range)
        {
            using generator_return_t = typename std::result_of<F()>::type;

            static_assert(
                std::is_integral< generator_return_t >::value,
                "CAUSE: The \"generator\" function must return a integral data type."
            );
            assert(
                range.max <= std::numeric_limits< generator_return_t >::max()
                && "CAUSE: Value of `max` does not fit in generator return type!"
            );
            assert(range.min < range.max && "CAUSE: Range \[`min`, `max`) is valid!");
            assert(n <= range.max - range.min && "CAUSE: Cannot generate more numbers than are in range!");
        }

    };

    /*  n_unique_from
        Generates `n` distinct values from [`min`, `max`) obtained from `n` calls to `generator`
        @param  `generator`:    function/functor that will generate values to be returned
        @param  `n`:            number of values to be generated
        @param  `range`:        pair of values that determine the range of values that can be produced

        @pre    -   `min` n `max`
                -   `n` < no. elemnts in [`min`, `max`)
                -   `generator` should return an integral data type
                -   `generator` should be able to generate at least `n` distinct
                    values from the range [`min`, `max`)
                    NOTE: this is not checked at compile or runtime,
                    and failing this will result in a runtime error

        @post   std::set with `n` distinct values from `generator`
    */
    template<typename F>
    std::set< typename std::result_of<F()>::type >
        n_unique_from(F generator, const size_t n, Range range)
    {
        assert_arguments(generator, n, range);

        using generator_return_t = typename std::result_of<F()>::type;

        std::set< generator_return_t > gen;

        auto it = gen.begin();
        // track last known isertion to shorten the next search range
        auto                last = gen.end();
        generator_return_t  last_value = 0;
        size_t              last_offset = 0; // no. elements smaller than last

        for (size_t i = 0; i < n; i++) {
            generator_return_t r = range.min + generator()%(range.max - range.min);

            if(last != gen.end() && last_value <= r) {
                // std::set is ordered, all elements before `last` are smaller
                it = last;
                r += last_offset;
            }
            else {
                it = gen.begin();
                last_offset = 0;
            }

            // offset `r` by number of found values smaller than it
            for(; it != gen.end(); it++) {
                if(*it <= r) {
                    last_offset++;
                    r++;
                }
                else break;
            }

            range.max--;

            last = gen.insert(it, r); //`it` is a hint pointing to element after `r`
            last_value = r;
            assert(gen.size() == i+1 && "A duplicate was generated, verify if `generator` can generate enough numbers");
        }

        return gen;
    }

    /*
        Wrapper for call to n_unique_from that allows passing a maximum value instead of a range
    */
    template<typename F>
    std::set< typename std::result_of<F()>::type > n_unique_from(F generator, const size_t n, size_t max)
    {
        Range r = {0, max};
        return n_unique_from(generator, n, r);
    }

};
