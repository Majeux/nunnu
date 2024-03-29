#ifndef NUNNU_H
#define NUNNU_H

#include <cassert>
#include <cstddef> // size_t
#include <limits>
#include <set>

namespace nunnu
{

  struct Range
  {
    size_t min;
    size_t max;
  };

  namespace
  { // anonymous/private namespace for assertions

    /*
        Verifies if the arguments passed to `n_unique_numbers` are correct
    */
    template <typename F>
    void assert_arguments(const F rgen, const size_t n, const Range bounds)
    {
      (void)rgen; // silence unused warning

      static_assert(std::is_integral<decltype(F()())>::value,
                    "CAUSE: The \"rgen\" function must return a integral "
                    "data type.");

      assert(bounds.max <= std::numeric_limits<decltype(F()())>::max() &&
             "CAUSE: Value of `max` does not fit in rgen return type!");

      assert(bounds.min < bounds.max &&
             "CAUSE: Range [`min`, `max`) is valid!");
      assert(n <= bounds.max - bounds.min &&
             "CAUSE: Cannot generate more numbers than are in range!");
    }

  }; // namespace

  // older implementation. Preliminary: worse in most case, sometimes better
  template <typename F>
  auto n_unique_numbersOLD(F rgen, const size_t n, Range bounds)
      -> std::set<decltype(F()())>
  {
    assert_arguments(rgen, n, bounds);

    using integral_t = decltype(F()());

    std::set<integral_t> gen;

    for (size_t i = 0; i < n; i++)
    {
      integral_t r = bounds.min + rgen() % (bounds.max - bounds.min);

      for (integral_t x : gen)
      {
        if (x <= r)
          r = r + 1;
        else
          break;
      }

      bounds.max--;

      bool inserted = gen.insert(r).second;
      assert(inserted && "A duplicate was generated, verify if `rgen` can "
                         "generate enough numbers");
    }

    return gen;
  }

  /*  n_unique_numbers
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
  auto n_unique_numbers(F rgen, const size_t n, Range bounds)
      -> std::set<decltype(F()())>
  {
    assert_arguments(rgen, n, bounds);

    using integral_t = decltype(F()());

    std::set<integral_t> gen;

    auto it = gen.begin();
    // track last known isertion to shorten the next search range
    auto last = gen.end();
    integral_t last_value = 0;
    size_t last_offset = 0; // no. elements smaller than last

    for (size_t i = 0; i < n; i++)
    {
      integral_t r = bounds.min + rgen() % (bounds.max - bounds.min);

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

      bounds.max--;

      last = gen.insert(it, r); //`it` is a hint pointing to element after `r`
      last_value = r;
      assert(gen.size() == i + 1 && "A duplicate was generated, verify if "
                                    "`rgen` can generate enough numbers");
    }

    return gen;
  }

  /*
      Wrapper for call to n_unique_numbers that allows passing a maximum value
     instead of a range
  */
  template <typename F>
  auto n_unique_numbers(F rgen, const size_t n, size_t max)
      -> std::set<decltype(rgen())>
  {
    Range r = {0, max};
    return n_unique_numbers(rgen, n, r);
  }

  template <typename F>
  auto n_unique_numbersOLD(F rgen, const size_t n, size_t max)
      -> std::set<decltype(rgen())>
  {
    Range r = {0, max};
    return n_unique_numbersOLD(rgen, n, r);
  }
}; // namespace nunnu

#endif // NUNNU_H
