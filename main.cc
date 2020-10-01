#include "unnuun.h"

int main() {
    std::random_device  rand_dev;
    std::mt19937        generator(rand_dev());

    for(auto i : Unnuun::rand_n_unique(9, 0, 10, generator))
        std::cerr << i << " ";

    std::cerr << std::endl << "#######" << std::endl;

    //Now with default generator
    Unnuun genObj;
    for(auto i : genObj.rand_n_unique(4, 0, 6))
        std::cerr << i << " ";

    std::cerr << std::endl;

    return 1;
}
