#include "unnu.h"
#include <algorithm>
#include <chrono>
#include <concepts>
#include <cstddef> // size_t
#include <iostream>
#include <ostream>
#include <random>
#include <sstream>
#include <vector>

std::random_device rand_dev;
std::mt19937 generator(rand_dev());

// clang-format off
template <typename T>
concept ULContainter = requires(T container) 
{ 
  { *container.cbegin() } -> std::same_as<const size_t&>; 
  { *container.cend() } -> std::same_as<const size_t&>; 
};
// clang-format on

class Result
{
public:
  Result(size_t n,
         nunnu::Range range,
         const std::set<size_t> &numbers,
         std::chrono::duration<double> dt_s)
  {
    auto in_range = [range](size_t num)
    { return range.min <= num && num <= range.max; };

    generated_n = numbers.size() == n;
    all_unique = true; // items in set are all unique
    all_in_range = std::all_of(numbers.cbegin(), numbers.cend(), in_range);
    runtime_s = dt_s;
  }

  Result(size_t n,
         nunnu::Range range,
         const ULContainter auto &numbers,
         std::chrono::duration<double> dt_s)
  {
    auto in_range = [range](size_t num)
    { return range.min <= num && num <= range.max; };
    // get all unique "numbers"
    std::set<size_t> numbers_set(numbers.cbegin(), numbers.cend());

    generated_n = numbers.size() == n;
    all_unique = numbers_set.size() == n;
    all_in_range = std::all_of(numbers.cbegin(), numbers.cend(), in_range);
    runtime_s = dt_s;
  }

  std::string runtime_str() const
  {
    std::stringstream out;
    out << runtime_s.count() << "s";
    return out.str();
  }

  std::string display() const
  {
    std::stringstream out;
    out << "runtime: " << runtime_str() << std::endl;
    out << "-----" << std::endl;
    out << "N numbers:\t\t" << success_or_fail(generated_n) << std::endl;
    out << "all unique numbers:\t" << success_or_fail(all_unique) << std::endl;
    out << "all numbers in range:\t" << success_or_fail(all_in_range)
        << std::endl;

    return out.str();
  }

private:
  bool generated_n;
  bool all_unique;
  bool all_in_range;
  std::chrono::duration<double> runtime_s;

  static std::string success_or_fail(bool success)
  {
    if (success)
      return "SUCCESS";
    return "FAIL";
  }
};

// benchmark functions
//
Result run_naive(size_t n, size_t max)
{
  auto t1 = std::chrono::steady_clock::now();

  std::set<size_t> s;

  for (size_t i = 0; i < n; i++)
  {
    while (s.insert(generator() % max).second == false) {}
  }

  auto t2 = std::chrono::steady_clock::now();

  return Result(n, {0, max}, s, t2 - t1);
}

Result run_std_sample(size_t n, size_t max)
{
  auto t1 = std::chrono::steady_clock::now();

  std::vector<size_t> v, out;
  v.reserve(max);
  out.reserve(n);
  for (size_t i = 0; i < max; i++) v.push_back(i);

  std::sample(v.cbegin(), v.cend(), std::back_inserter(out), n, generator);

  auto t2 = std::chrono::steady_clock::now();

  return Result(n, {0, max}, out, t2 - t1);
}

Result run_std_sample_prealloc(size_t n, size_t max)
{
  std::vector<size_t> v, out;
  v.reserve(max);
  out.reserve(n);
  for (size_t i = 0; i < max; i++) v.push_back(i);

  auto t1 = std::chrono::steady_clock::now();
  std::sample(v.cbegin(), v.cend(), std::back_inserter(out), n, generator);
  auto t2 = std::chrono::steady_clock::now();

  return Result(n, {0, max}, out, t2 - t1);
}

Result run_nunnu(size_t n, size_t max)
{
  auto t1 = std::chrono::steady_clock::now();
  std::set<size_t> s = nunnu::n_unique_numbers(generator, n, max);
  auto t2 = std::chrono::steady_clock::now();

  return Result(n, {0, max}, s, t2 - t1);
}

Result run_nunnuOLD(size_t n, size_t max)
{
  auto t1 = std::chrono::steady_clock::now();
  std::set<size_t> s = nunnu::n_unique_numbersOLD(generator, n, max);
  auto t2 = std::chrono::steady_clock::now();

  return Result(n, {0, max}, s, t2 - t1);
}

int main(int argc, char **argv)
{
  if (argc != 3) {
    std::cout << "Incorrect number of arguments" << std::endl;
    return 1;
  }

  size_t n = std::stoul(argv[1]);
  size_t max = std::stoul(argv[2]);

  std::cout << "generating " << n << " numbers in [0," << max
            << "):" << std::endl;
  std::cout << "================" << std::endl;

  Result naive = run_naive(n, max);
  Result sample = run_std_sample(n, max);
  Result sample_prealloc = run_std_sample_prealloc(n, max);
  Result nunnu = run_nunnu(n, max);
  Result nunnuOLD = run_nunnuOLD(n, max);

  std::cout << "run_naive:               " << naive.runtime_str() << std::endl
            << "run_std_sample:          " << sample.runtime_str() << std::endl
            << "run_std_sample_prealloc: " << sample_prealloc.runtime_str()
            << std::endl
            << "run_nunnu:               " << nunnu.runtime_str() << std::endl
            << "run_nunnuOLD:            " << nunnuOLD.runtime_str()
            << std::endl;

  std::cout << std::endl << "================" << std::endl;

  std::cout << "run_naive" << std::endl
            << naive.display() << std::endl
            << std::endl;

  std::cout << "run_std_sample" << std::endl
            << sample.display() << std::endl
            << std::endl;

  std::cout << "run_std_sample_prealloc" << std::endl
            << sample_prealloc.display() << std::endl
            << std::endl;

  std::cout << "run_nunnu" << std::endl
            << nunnu.display() << std::endl
            << std::endl;

  std::cout << "run_nunnuOLD" << std::endl << nunnuOLD.display() << std::endl;

  /* Preliminary results
   * nunnu works best for low n and high |range|
   * and when max is very low
   *
   * sample works best when n is close to |range|
   */

  return 0;
}
