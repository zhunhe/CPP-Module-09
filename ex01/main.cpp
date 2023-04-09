/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:02:11 by juhur             #+#    #+#             */
/*   Updated: 2023/04/09 12:04:15 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include "RPN.hpp"

int main(int ac, char** av) {
  if (ac < 2) {
    std::cout << "Error: Please input inverted Polish mathematical expression as an argument\n";
    return 0;
  }
  try {
    RPN rpn(av[1]);
    rpn.run();
  } catch(std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
