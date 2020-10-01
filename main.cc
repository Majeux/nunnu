#include "unnuun.h"

int main() {
    std::random_device  rand_dev;

    auto nums = Unnuun::rand_n_unique(4, 0, 100, std::mt19937(rand_dev()) );

    for(auto i : nums)
        std::cerr << i << " ";

    std::cerr << std::endl;

    return 1;
}
