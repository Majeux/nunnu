#include "unnuun.h"

int main() {
    std::random_device  rand_dev;

    std::set<uint32_t> nums = Unnuun::rand_n_unique(4, 0, 100, std::mt19937(rand_dev()) );

    for(auto i : nums)
        std::cerr << i << " ";

    return 1;
}
