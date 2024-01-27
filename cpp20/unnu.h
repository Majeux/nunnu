#ifndef UNNU_H
#define UNNU_H

#include <cassert>
#include <concepts>
#include <cstddef> // size_t
#include <limits>
#include <set>

namespace unnu
{

  // an object that can be called to produce an integral number
  // it is up to the user to provide an object that can generate sufficient
  // random numbers
  // clang-format off
  template <typename T> 
  concept non_bool = !std::same_as<T, bool>;

  template <typename T>
  concept NumberGenerator = requires(T generate) 
  { 
    { generate() } -> std::integral; 
    { generate() } -> non_bool; 
  };
  // clang-format on

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
    void assert_arguments(NumberGenerator auto rgen,
                          const size_t n,
                          const Range bounds)
    {
      (void)rgen; // silence unused warning

      assert(bounds.max <= std::numeric_limits<decltype(rgen())>::max() &&
             "CAUSE: Value of `max` does not fit in rgen return type!");

      assert(bounds.min < bounds.max &&
             "CAUSE: Range [`min`, `max`) is valid!");
      assert(n <= bounds.max - bounds.min &&
             "CAUSE: Cannot generate more numbers than are in range!");
    }

  }; // namespace

  /*
      Wrapper for call to n_unique_from that allows passing a maximum value
     instead of a range
  */
  auto n_unique_from(NumberGenerator auto rgen, const size_t n, size_t max)
      -> std::set<decltype(rgen())>
  {
    Range r = {0, max};
    return n_unique_from(rgen, n, r);
  }

  auto n_unique_fromOLD(NumberGenerator auto rgen, const size_t n, size_t max)
      -> std::set<decltype(rgen())>
  {
    Range r = {0, max};
    return n_unique_fromOLD(rgen, n, r);
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
  auto n_unique_from(NumberGenerator auto rgen, const size_t n, Range bounds)
      -> std::set<decltype(rgen())>
  {
    assert_arguments(rgen, n, bounds);

    using integral_t = decltype(rgen());

    std::set<integral_t> gen;

    auto it = gen.begin();
    // track last known insertion to shorten the next search range
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

  // older implementation. Preliminary: worse in most case, sometimes better
  template <NumberGenerator F>
  auto n_unique_fromOLD(F rgen, const size_t n, Range bounds)
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

}; // namespace unnu

#endif // UNNU_H
