#include "unnuun.h"

int main() {
    Unnuun gen;

    std::set<uint32_t> nums = gen.rand_n_unique(4, 6);

    for(auto i : nums)
        std::cerr << i << " ";

    return 1;
}
