/*
    Method to generate a random series of Unique Numbers from a Uniform Distribution
*/

#include <cassert>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <dbg.h>

//TODO generic type
//TODO parametrize rand generator
std::random_device  rand_dev;
std::mt19937        generator(rand_dev());

//max range generator
std::vector<uint32_t> rand_n_unique(const size_t n) {
    std::vector<uint32_t> gen;
    gen.reserve(n);

    for (size_t i = 0; i < n; i++) {
        size_t r = generator();
        size_t offset = std::count_if(
            gen.begin(), gen.end(),
            [=] (size_t i) { return i <= r; }
        );

        gen.push_back(r + offset);
    }

    return gen;
}

//TODO argument max - generator
std::vector<uint32_t> rand_n_unique(const size_t n, size_t max) {
    assert(n < max);

    std::vector<uint32_t> gen;
    gen.reserve(n);

    for (size_t i = 0; i < n; i++) {
        size_t r = generator() % max;
        r = 0;
        std::cerr << r << " ";
        if(r != max--) {
            uint32_t offset = std::count_if(
                gen.begin(), gen.end(),
                [=] (size_t x) { std::cerr << x << " <= " << r << ": " << (x <= r) << std::endl; return x <= r; }
            );

            r += dbg(offset);
        }

        gen.push_back(r);
    }
    std::cerr << std::endl;
    return gen;
}

//TODO argument range - generator
