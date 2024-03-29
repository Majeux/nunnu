#include "unnu.h"
#include <algorithm>
#include <chrono>
#include <cstddef> // size_t
#include <iostream>
#include <random>
#include <vector>

std::random_device rand_dev;
std::mt19937 generator(rand_dev());

// auto run_std_sample(size_t n, size_t max)
// {
//   auto t1 = std::chrono::steady_clock::now();

//   std::set<uint_fast32_t> s;

//   for (size_t i = 0; i < n; i++)
//   {
//     while (s.insert(generator() % max).second == false)
//     {
//     }
//   }

//   auto t2 = std::chrono::steady_clock::now();

//   return t2 - t1;
// }

// auto run_std_sample(size_t n, size_t max)
// {
//   auto t1 = std::chrono::steady_clock::now();

//   std::vector<uint_fast32_t> v;
//   v.reserve(n);

//   for (size_t i = 0; i < max; i++)
//     v.push_back(i);

//   std::shuffle(v.begin(), v.end(), generator);
//   auto t2 = std::chrono::steady_clock::now();

//   return t2 - t1;
// }

// auto run_std_sample_prealloc(size_t n, size_t max)
// {
//   std::vector<uint_fast32_t> v;
//   v.reserve(n);

//   for (size_t i = 0; i < max; i++)
//     v.push_back(i);

//   auto t1 = std::chrono::steady_clock::now();
//   std::shuffle(v.begin(), v.end(), generator);
//   auto t2 = std::chrono::steady_clock::now();

//   return t2 - t1;
// }

// auto run_unnu(size_t n, size_t max)
// {
//   auto t1 = std::chrono::steady_clock::now();
//   std::set<uint_fast32_t> s = unnu::n_unique_numbers(generator, n, max);
//   auto t2 = std::chrono::steady_clock::now();

//   return t2 - t1;
// }

// auto run_unnuOLD(size_t n, size_t max)
// {
//   auto t1 = std::chrono::steady_clock::now();
//   std::set<uint_fast32_t> s = unnu::n_unique_numbersOLD(generator, n, max);
//   auto t2 = std::chrono::steady_clock::now();

//   return t2 - t1;
// }

int main()
{
//   size_t n = 100;
//   size_t max = 100000000;
//   /*
//       100 out of 100000000
//       run_vec_alloc:		 8151040435
//       run_vec_prealloc:	 8197613741
//       run_unnu:		     62077
//   */

//   // size_t n =   1000;
//   // size_t max = 100000;
//   /*
//       1000 out of 100000
//       run_vec_alloc:		 4275169
//       run_vec_prealloc:	 3101746
//       run_unnu:		     1760139
//   */

//   auto t_n = run_sample(n, max);
//   auto t_v = run_sample(n, max);
//   auto t_vpre = run_std_sample_prealloc(n, max);
//   auto t_unnu = run_unnu(n, max);
//   auto t_unnuOLD = run_unnuOLD(n, max);

//   std::cout << n << " out of " << max << std::endl;
//   std::cout << "______________" << std::endl;
//   std::cout << "run_naive:\t\t " << t_n.count() << std::endl;
//   std::cout << "run_vec_alloc:\t\t " << t_v.count() << std::endl;
//   std::cout << "run_vec_prealloc:\t " << t_vpre.count() << std::endl;
//   std::cout << "run_unnu:\t\t " << t_unnu.count() << std::endl;
//   std::cout << "run_unnuOLD:\t\t " << t_unnuOLD.count() << std::endl;
  return 0;
}
