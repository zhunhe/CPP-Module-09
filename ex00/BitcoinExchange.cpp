/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:00:15 by juhur             #+#    #+#             */
/*   Updated: 2023/04/09 12:02:53 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <algorithm>
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& inputFile)
: dataFile("data.csv")
, inputFile(inputFile) {
  std::ifstream data(this->dataFile.c_str());
  if (data.is_open() == false)
    throw std::runtime_error("Error: cannot open data file" + this->dataFile);

  std::string line;
  std::getline(data, line);

  while (data.eof() == false) {
    std::getline(data, line);
    if (line.empty() == true)
      break;

    std::istringstream lineStream(line.c_str());

    std::string date;
    std::getline(lineStream, date, ',');
    if (date.empty() == true) {
      data.close();
      throw std::runtime_error("Error: bad input data => " + line);
    }
    date = trim(date);

    std::string rawRate;
    std::getline(lineStream, rawRate);
    if (rawRate.empty() == true) {
      data.close();
      throw std::runtime_error("Error: bad input data => " + line);
    }
    rawRate = trim(rawRate);

    std::istringstream rateStream(rawRate.c_str());
    double rate;
    rateStream >> rate;
    if (rateStream.fail() == true) {
      data.close();
      throw std::runtime_error("Error: bad input data =>" + line);
    }

    checkDate(date);
    if (rate < 0) {
      data.close();
      throw std::runtime_error("Error: bad input data =>" + line);
    }
    this->data[date] = rate;
  }
  data.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& obj) {
  *this = obj;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) {
  if (this != &rhs) {
    this->dataFile = rhs.dataFile;
    this->inputFile = rhs.inputFile;
    this->data = rhs.data;
  }
  return *this;
}

BitcoinExchange::~BitcoinExchange() {
  this->data.clear();
}

void BitcoinExchange::process() {
  std::ifstream input(inputFile.c_str());
  if (input.is_open() == false)
    throw std::runtime_error("Error: cannot open input file " + inputFile);

  std::string line;
  std::getline(input, line);

  while (input.eof() == false) {
    try {
      std::getline(input, line);
      if (line.empty() == true)
        break;
      std::istringstream lineStream(line.c_str());

      std::string date;
      std::getline(lineStream, date, '|');
      if (date.empty() == true)
        throw std::runtime_error("Error: bad input => " + line);
      date = trim(date);

      std::string rawValue;
      std::getline(lineStream, rawValue);
      if (rawValue.empty() == true)
        throw std::runtime_error("Error: bad input => " + line);
      rawValue = trim(rawValue);
      std::istringstream valueStream(rawValue.c_str());
      double value;
      valueStream >> value;
      if (valueStream.fail() == true)
        throw std::runtime_error("Error: bad input => " + line);

      checkDate(date);
      checkValue(value);

      double rate = getRate(date);
      std::cout << date << " => " << value << " = " << rate * value << std::endl;
    } catch(std::exception& e) {
      std::cout << e.what() << std::endl;
    }
  }
  input.close();
}

void BitcoinExchange::checkValue(double value) {
  if (value <= 0.0)
    throw std::runtime_error("Error: not a positive number.");
  if (value >= 1000.0)
    throw std::runtime_error("Error: too large a number.");
}

double BitcoinExchange::getRate(const std::string& date) {
  std::map<std::string, double>::const_iterator lowerIterator = this->data.lower_bound(date);
  std::map<std::string, double>::const_iterator upperIterator = this->data.upper_bound(date);

  if (lowerIterator != upperIterator)
    return lowerIterator->second;
  if (upperIterator == this->data.begin())
    throw std::runtime_error("Error: cannot find price before then date " + date);
  if (date != upperIterator->first)
    upperIterator--;
  return upperIterator->second;
}

std::string BitcoinExchange::trim(const std::string &str) {
  std::string::const_iterator begin = str.begin();
  std::string::const_reverse_iterator end = str.rbegin();
  while (std::isspace(*begin))
    ++begin;
  while (std::isspace(*end))
    ++end;
  return std::string(begin, end.base());
}

static int checkYear(const std::string& rawYear, const std::string& date) {
  if (rawYear.empty() == true)
    throw std::runtime_error("Error: bad date year => " + date);
  std::istringstream yearStream(rawYear.c_str());
  int year;
  yearStream >> year;
  if (yearStream.fail() == true)
    throw std::runtime_error("Error: bad date year => " + date);
  return year;
}

static int checkMonth(const std::string& rawMonth, const std::string& date) {
  if (rawMonth.empty() == true)
    throw std::runtime_error("Error: bad date month => " + date);
  std::istringstream monthStream(rawMonth.c_str());
  int month;
  monthStream >> month;
  if (monthStream.fail() == true)
    throw std::runtime_error("Error: bad date month => " + date);
  if (month < 1 || month > 12)
    throw std::runtime_error("Error: bad date month => " + date);
  return month;
}

static void checkDay(const std::string& rawDay, const std::string& date, const int year, const int month) {
  if (rawDay.empty() == true)
    throw std::runtime_error("Error: bad date day => " + date);
  std::istringstream dayStream(rawDay.c_str());
  int day;
  dayStream >> day;
  if (dayStream.fail() == true)
    throw std::runtime_error("Error: bad date day => " + date);
  if (day < 1)
    throw std::runtime_error("Error: bad date day => " + date);

  switch (month) {
  case 2:
    // Check leaf month using Gregorian calendar
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
      if (day > 29)
        throw std::runtime_error("Error: bad date day => " + date);
    }
    else if (day > 28)
      throw std::runtime_error("Error: bad date day => " + date);
    break;
  case 1: case 3: case 5: case 7: case 8: case 10: case 12:
    if (day > 31)
      throw std::runtime_error("Error: bad date day => " + date);
    break;
  case 4: case 6: case 9: case 11:
    if (day > 30)
      throw std::runtime_error("Error: bad date day => " + date);
    break;
  }
}

void BitcoinExchange::checkDate(const std::string& date) {
  if (date.size() != 10 || std::count(date.begin(), date.end(), '-') != 2)
    throw std::runtime_error("Error: bad date => " + date);

  std::istringstream stream(date.c_str());

  std::string rawYear;
  std::getline(stream, rawYear, '-');
  int year = checkYear(rawYear, date);

  std::string rawMonth;
  std::getline(stream, rawMonth, '-');
  int month = checkMonth(rawMonth, date);

  std::string rawDay;
  std::getline(stream, rawDay);
  checkDay(rawDay, date, year, month);
}
