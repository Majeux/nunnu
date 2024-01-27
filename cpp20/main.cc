#include <cstdlib>
#include <ctime>
#include <iostream>

#include <random>

#include "unnu.h"
// #include "unnuun.h"

float testFloat() { return 0.0; }

void testVoid() {}

bool testBool() { return true; }

struct boolFunctor{
  bool operator()(){ return true; };
};

int testInt() { return 0; }

struct intFunctor{
  int operator()(){ return 0; };
};


int main()
{
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());

  for (auto i : unnu::n_unique_from(intFunctor(), 100, 100000000))
    std::cerr << i << " ";

  // for (auto i : unnu::n_unique_from(testFloat, 100, 100000000))
  //   std::cerr << i << " ";

  std::cerr << std::endl << "#######" << std::endl;

  // Now with default generator
  // Unnuun genObj;
  // for (auto i : genObj.rand_n_unique(4, 100))
  //   std::cerr << i << " ";

  // std::cerr << std::endl;

  return 1;
}
