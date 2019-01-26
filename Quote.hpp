#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>
#include <sstream>

class Quote {
  public:
  std::string symbol;

  int time;
  float bid;
  float ask;

  Quote() { }
  Quote(std::string line) {
    std::istringstream ss(line);
    std::string stime, ssymbol, sbid, sask;

    std::getline(ss, stime, ',');
    std::getline(ss, ssymbol, ',');
    std::getline(ss, sbid, ',');
    std::getline(ss, sask, ',');

    time = std::stoi(stime);
    symbol = ssymbol;
    bid = std::stof(sbid);
    ask = std::stof(sask);
  }

  void print() {
    std::cout
      << time << ','
      << symbol << ','
      << bid << ','
      << ask << std::endl;
  }
};

#endif /* end of include guard: QUOTE_H */
