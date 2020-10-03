#include "unnuun.h"
#include <iostream>

float testFloat() {
    return 0.0;
}

void testVoid() {

}

bool testBool() {
    return true;
}

int main() {
    std::random_device  rand_dev;
    std::mt19937        generator(rand_dev());

    for(auto i : Unnu::n_unique_from(generator, 4, 100))
        std::cerr << i << " ";

    std::cerr << std::endl;

    //Now with default generator
    Unnuun genObj;
    for(auto i : genObj.rand_n_unique(4, 100))
        std::cerr << i << " ";

    std::cerr << std::endl;

    return 1;
}
