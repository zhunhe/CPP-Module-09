/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:11:13 by juhur             #+#    #+#             */
/*   Updated: 2023/04/09 02:11:13 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <stack>

class RPN {
private:
  std::string expression;
  std::stack<int> stack;
  RPN();
  void print();
  void calculate(char arithmeticOperator);

public:
  RPN(const std::string& expression);
  RPN(const RPN& obj);
  RPN& operator=(const RPN& rhs);
  ~RPN();

  void run();
};
