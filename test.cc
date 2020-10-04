#include "unnu.h"
#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>

std::random_device  rand_dev;
std::mt19937        generator(rand_dev());

auto run_vec_alloc(size_t n, size_t max) {
    auto t1 = std::chrono::steady_clock::now();

    std::vector<uint_fast32_t> v;
    v.reserve(n);
    for(size_t i = 0; i < max; i++) v.push_back(i);
    std::shuffle(v.begin(), v.end(), generator);

    auto t2 = std::chrono::steady_clock::now();

    for(auto i : v)
        std::cerr << i << ' ';

    return t2-t1;
}

auto run_vec_prealloc(size_t n, size_t max) {
    std::vector <uint_fast32_t> v;
    v.reserve(n);
    for(size_t i = 0; i < max; i++) v.push_back(i);

    auto t1 = std::chrono::steady_clock::now();

    std::shuffle(v.begin(), v.end(), generator);

    auto t2 = std::chrono::steady_clock::now();

    for(auto i : v)
        std::cerr << i << ' ';

    return t2-t1;
}

auto run_unnu(size_t n, size_t max) {
    auto t1 = std::chrono::steady_clock::now();

    std::set<uint_fast32_t> s = Unnu::n_unique_from(generator, n, max);

    auto t2 = std::chrono::steady_clock::now();

    for(auto i : s)
        std::cerr << i << ' ';

    return t2-t1;
}

int main() {
    size_t n =   100;
    size_t max = 100000000;
    /*
        100 out of 100000000
        run_vec_alloc:		 8151040435
        run_vec_prealloc:	 8197613741
        run_unnu:		     62077
    */


    // size_t n =   1000;
    // size_t max = 100000;
    /*
        1000 out of 100000
        run_vec_alloc:		 4275169
        run_vec_prealloc:	 3101746
        run_unnu:		 1760139
    */

    std::cout << n << " out of " << max << std::endl;

    auto t = run_vec_alloc(n, max);

    std::cout << "run_vec_alloc:\t\t " << t.count() << std::endl;

    t = run_vec_prealloc(n, max);

    std::cout << "run_vec_prealloc:\t " << t.count() << std::endl;

  t = run_unnu(n, max);

  std::cout << "run_unnu:\t\t " << t.count() << std::endl;

}
