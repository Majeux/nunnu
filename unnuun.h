/*
    Method to generate a random series of Unique Numbers from a Uniform Distribution
*/

#include <cassert>
#include <random>
#include <set>
#include <iostream>
#include <dbg.h>

//TODO generic type
//TODO parametrize rand generator
std::random_device  rand_dev;
std::mt19937        generator(rand_dev());

std::set<uint32_t> rand_n_unique(const size_t n, size_t min, size_t max) {
    assert(min < max); assert(n < max - min);

    std::set<uint32_t> gen;

    for (size_t i = 0; i < n; i++) {
        size_t r = min + generator()%(max - min); //TODO min fixen
        std::cerr << r << "->";

        for(size_t x : gen) {
            if(x <= r) r++;
            else break;
        }

        max--;

        std::cerr << r << " | ";
        gen.insert(r);
    }
    std::cerr << std::endl;
    return gen;
}

std::set<uint32_t> rand_n_unique(const size_t n) {
    return rand_n_unique(n, 0, generator.max());
}

std::set<uint32_t> rand_n_unique(const size_t n, size_t max) {
    return rand_n_unique(n, 0, max);
}
