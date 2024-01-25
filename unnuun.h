/*
    Method to generate a random series of Unique Numbers from a Uniform
   Distribution
*/
#include <cassert>
#include <random>
#include <set>
#include <type_traits>

#include "unnu.h"

class Unnuun {
private:
  std::random_device rand_dev;
  std::mt19937 generator;

public:
  Unnuun() : generator(rand_dev()) {}

  /*
      Generates `n` random numbers in range = [`min`, `max`)
      @pre    `min` smaller than `max`
              `n` smaller no. elemnts in [`min`, `max`)
      @post   set with `n` values
  */
  std::set<uint_fast32_t> rand_n_unique(const std::size_t n,
                                        unnu::Range range) {
    assert(range.max <= generator.max());
    return unnu::n_unique_from(generator, n, range);
  }

  /*
      Generates `n` unique random numbers in [0, `max`)
      @pre    `n` smaller no. elemnts in [0, `max`)
      @post   set with `n` values
  */
  std::set<uint_fast32_t> rand_n_unique(const std::size_t n, std::size_t max) {
    return unnu::n_unique_from(generator, n, {0, max});
  }

  /*
      Generates `n` unique random numbers in [0, std::mt19937::max)
      @pre    `n` smaller no. elemnts in [0, std::mt19937::max)
      @post   set with `n` values
  */
  std::set<uint_fast32_t> rand_n_unique(const std::size_t n) {
    return unnu::n_unique_from(generator, n, {0, generator.max()});
  }
};
