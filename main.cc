#include "unnuun.h"

int main() {

    std::vector<uint32_t> nums = rand_n_unique(3, 5);

    for(auto i : nums)
        std::cerr << i << " ";

    return 1;
}
