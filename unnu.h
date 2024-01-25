#include <cassert>
#include <cstddef> // size_t
#include <limits>
#include <set>

namespace unnu
{

  struct Range
  {
    size_t min;
    size_t max;
  };

  namespace
  { // anonymous/private namespace for assertions

    /*
        Verifies if the arguments passed to `n_unique_from` are correct
    */
    template <typename F>
    void assert_arguments(const F rgen, const size_t n, const Range range)
    {
      using generator_return_t = typename std::result_of<F()>::type;

      static_assert(std::is_integral<generator_return_t>::value,
                    "CAUSE: The \"rgen\" function must return a integral "
                    "data type.");

      assert(range.max <= std::numeric_limits<generator_return_t>::max() &&
             "CAUSE: Value of `max` does not fit in rgen return type!");

      assert(range.min < range.max && "CAUSE: Range \[`min`, `max`) is valid!");
      assert(n <= range.max - range.min &&
             "CAUSE: Cannot generate more numbers than are in range!");
    }

  }; // namespace

  // older implementation. Preliminary: worse in most case, sometimes better
  template <typename F>
  auto n_unique_fromOLD(F rgen, const size_t n, Range range)
      -> std::set<decltype(rgen())>
  {
    assert_arguments(rgen, n, range);

    using rgen_return_t = decltype(rgen());

    std::set<rgen_return_t> gen;

    for (size_t i = 0; i < n; i++)
    {
      rgen_return_t r = range.min + rgen() % (range.max - range.min);

      for (rgen_return_t x : gen)
      {
        if (x <= r)
          r = r + 1;
        else
          break;
      }

      range.max--;

      bool inserted = gen.insert(r).second;
      assert(inserted && "A duplicate was generated, verify if `rgen` can "
                         "generate enough numbers");
    }

    return gen;
  }

  /*  n_unique_from
      Generates `n` distinct values from [`min`, `max`) obtained from `n` calls
     to `rgen`
      @param  `rgen`:   function/functor that will generate random values
      @param  `n`:      number of values to be generated
      @param  `range`:  pair of values that determine the range of values
     that can be produced

      @pre    -   `min` n `max`
              -   `n` < no. elemnts in [`min`, `max`)
              -   `rgen` should return an integral data type
              -   `rgen` should be able to generate at least `n` distinct
                  values from the range [`min`, `max`)
                  NOTE: this is not checked at compile or runtime,
                  and failing this will result in a runtime error

      @post   std::set with `n` distinct values from `rgen`
  */
  // implementation with single element memory
  template <typename F>
  auto n_unique_from(F rgen, const size_t n, Range range)
      -> std::set<decltype(rgen())>
  {
    assert_arguments(rgen, n, range);

    using rgen_return_t = decltype(rgen());

    std::set<rgen_return_t> gen;

    auto it = gen.begin();
    // track last known isertion to shorten the next search range
    auto last = gen.end();
    rgen_return_t last_value = 0;
    size_t last_offset = 0; // no. elements smaller than last

    for (size_t i = 0; i < n; i++)
    {
      rgen_return_t r = range.min + rgen() % (range.max - range.min);

      if (last != gen.end() && last_value <= r)
      {
        // std::set is ordered, all elements before `last` are smaller
        it = last;
        r += last_offset;
      }
      else
      {
        it = gen.begin();
        last_offset = 0;
      }

      // offset `r` by number of found values smaller than it
      for (; it != gen.end(); it++)
      {
        if (*it <= r)
        {
          last_offset++;
          r++;
        }
        else
          break;
      }

      range.max--;

      last = gen.insert(it, r); //`it` is a hint pointing to element after `r`
      last_value = r;
      assert(gen.size() == i + 1 && "A duplicate was generated, verify if "
                                    "`rgen` can generate enough numbers");
    }

    return gen;
  }

  /*
      Wrapper for call to n_unique_from that allows passing a maximum value
     instead of a range
  */
  template <typename F>
  auto n_unique_from(F rgen, const size_t n, size_t max)
      -> std::set<decltype(rgen())>
  {
    Range r = {0, max};
    return n_unique_from(rgen, n, r);
  }

  template <typename F>
  auto n_unique_fromOLD(F rgen, const size_t n, size_t max)
      -> std::set<decltype(rgen())>
  {
    Range r = {0, max};
    return n_unique_fromOLD(rgen, n, r);
  }
}; // namespace unnu
