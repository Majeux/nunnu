#include "unnuun.h"

int main() {
    Unnuun genObj;
    std::random_device  rand_dev;
    std::mt19937        generator(rand_dev());

    auto nums = Unnuun::rand_n_unique(4, 0, 100, generator );

    for(auto i : nums)
        std::cerr << i << " ";

    std::cerr << std::endl;

    for(auto i : genObj.rand_n_unique(4, 0, 100))
        std::cerr << i << " ";

    std::cerr << std::endl;

    return 1;
}
