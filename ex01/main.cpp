/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:02:11 by juhur             #+#    #+#             */
/*   Updated: 2023/04/09 02:08:05 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

int main(int ac, char** av) {
  (void)av;
  if (ac < 2) {
    std::cout << "Error: Please input inverted Polish mathematical expression as an argument\n";
    return 1;
  }
  try {
    RPN rpn(av[1]);
    rpn.run();
  } catch(std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
