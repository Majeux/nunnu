#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>

#include "unnu.h"
// #include "unnuun.h"

float testFloat() { return 0.0; }

void testVoid() {}

bool testBool() { return true; }

struct boolFunctor
{
  bool operator()() { return true; };
};

int testChar() { return 0; }

int testInt() { return 0; }

struct intFunctor
{
  int operator()() { return 5; };
};

int main()
{
  size_t n_num, min_num, max_num;

  {
    std::string n_in;
    std::cout << "How many numbers to generate?..." << std::endl;
    std::getline(std::cin, n_in);
    n_num = std::stoul(n_in.c_str());
  }
  {
    std::string min_in;
    std::cout << "Lowest number to generate?..." << std::endl;
    std::getline(std::cin, min_in);
    min_num = std::stoul(min_in.c_str());
  }
  {
    std::string max_in;
    std::cout << "Highest number to generate?..." << std::endl;
    std::getline(std::cin, max_in);
    max_num = std::stoul(max_in.c_str());
  }

  {
    std::cout << std::endl << "Generating..." << std::endl;
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());

    for (auto i : nunnu::n_unique_numbers(generator, n_num, {min_num, max_num}))
      std::cout << i << " ";

    std::cout << std::endl << "Done." << std::endl;
  }

  return 1;
}
