#include "unnuun.h"

Unnuun::Unnuun() : generator(rand_dev()) {

}

std::set<uint32_t> Unnuun::rand_n_unique(const size_t n, size_t min, size_t max)
{
    assert(min < max); assert(n < max - min);

    std::set< uint32_t > gen;

    for (size_t i = 0; i < n; i++) {
        uint32_t r = min + generator()%(max - min);

        for(uint32_t x : gen) {
            if(x <= r) r++;
            else break;
        }

        max--;

        gen.insert(r);
    }

    return gen;
}

std::set<uint32_t> Unnuun::rand_n_unique(const size_t n) {
    return rand_n_unique(n, 0, generator.max());
}

std::set<uint32_t> Unnuun::rand_n_unique(const size_t n, size_t max) {
    return rand_n_unique(n, 0, max);
}
