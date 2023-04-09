/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:00:22 by juhur             #+#    #+#             */
/*   Updated: 2023/04/09 12:04:47 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
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