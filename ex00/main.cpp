#include <iostream>
#include <exception>
#include <map>
#include "BitcoinExchange.hpp"

int main(int ac, char** av) {
  (void)av;
  if (ac != 2) {
    std::cout << "Error: could not open file.\n";
    return 0;
  }
  try {
    BitcoinExchange bitcoinExchange(av[1]);
    bitcoinExchange.process();
  } catch(std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}