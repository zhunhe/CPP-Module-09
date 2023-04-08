/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 02:11:08 by juhur             #+#    #+#             */
/*   Updated: 2023/04/09 02:11:09 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const std::string& expression) {
  this->expression = expression;
}

RPN::RPN(const RPN& obj) {
  *this = obj;
}

RPN& RPN::operator=(const RPN& rhs) {
  if (this != &rhs) {
    this->expression = rhs.expression;
    this->stack = rhs.stack;
  }
  return *this;
}

RPN::~RPN() {}

void RPN::run() {
  const size_t length = this->expression.size();
  for (size_t i = 0; i < length; i++) {
    char c = this->expression[i];
    if (c == ' ')
      continue;
    if (std::isdigit(c)) {
      this->stack.push(c - '0');
      continue;
    }
    if (std::strchr("+-*/", c)) {
      this->calculate(c);
      continue;
    }
    throw std::invalid_argument("Error: Invalid argument");
  }
  this->print();
}

void RPN::calculate(char arithmeticOperator) {
  if (this->stack.size() < 2)
    throw std::invalid_argument("Error: stack.size() < 2");

  int rhs = this->stack.top();
  this->stack.pop();
  int lhs = this->stack.top();
  this->stack.pop();

  switch (arithmeticOperator) {
  case '+':
    this->stack.push(lhs + rhs);
    break;
  case '-':
    this->stack.push(lhs - rhs);
    break;
  case '*':
    this->stack.push(lhs * rhs);
    break;
  case '/':
    if (rhs == 0)
      throw std::invalid_argument("Error: Cannot divide by 0");
    this->stack.push(lhs / rhs);
    break;
  }
}

void RPN::print() {
  if (this->stack.size() != 1) {
    throw std::invalid_argument("Error: Cannot print invalid expression");
  }
  std::cout << this->stack.top() << std::endl;
}
