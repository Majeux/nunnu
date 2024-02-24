#include <cstdlib>
#include <ctime>
#include <iostream>

#include <random>

#include "unnu.h"
// #include "unnuun.h"

float testFloat() { return 0.0; }

void testVoid() {}

bool testBool() { return true; }

int main()
{
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());

  for (auto i : nunnu::n_unique_numbers(generator, 100, 100000000))
    std::cerr << i << " ";

  return 1;
}
