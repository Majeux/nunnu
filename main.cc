#include "unnuun.h"

int main() {
    Unnuun gen;
    std::random_device  rand_dev;
    std::mt19937        generator;

    std::set<uint32_t> nums = gen.rand_n_unique(4, 0, 100, [&]() { return generator(); } );

    for(auto i : nums)
        std::cerr << i << " ";

    return 1;
}
