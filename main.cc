#include "unnuun.h"

int main() {

    std::set<uint32_t> nums = rand_n_unique(4, 6);

    for(auto i : nums)
        std::cerr << i << " ";

    return 1;
}
