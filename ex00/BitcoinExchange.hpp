#pragma once

#include <string>
#include <map>

class BitcoinExchange {
private:
  std::string dataFile;
  std::string inputFile;
  std::map<std::string, double> data;
  BitcoinExchange();

  void checkDate(const std::string& date);
  void checkValue(double value);
  double getRate(const std::string& date);

  std::string trim(const std::string& string);

public:
  BitcoinExchange(const std::string& inputFile);
  BitcoinExchange(const BitcoinExchange& obj);
  BitcoinExchange& operator=(const BitcoinExchange& rhs);
  ~BitcoinExchange();

  void process();
};
