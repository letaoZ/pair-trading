#ifndef TRADE_H
#define TRADE_H

#include <iostream>
#include <sstream>
#include "Quote.hpp"

class Trade {
  public:
  std::string symbol;

  int time;
  char side;
  float price;
  int quantity;

  float bid;
  float ask;

  Trade(std::string line) {
    std::istringstream ss(line);
    std::string stime, ssymbol, sside, sprice, squantity;

    std::getline(ss, stime, ',');
    std::getline(ss, ssymbol, ',');
    std::getline(ss, sside, ',');
    std::getline(ss, sprice, ',');
    std::getline(ss, squantity, ',');

    time = std::stoi(stime);
    symbol = ssymbol;
    side = sside.c_str()[0];
    price = std::stof(sprice);
    quantity = std::stoi(squantity);
  }

  bool close(Trade * t) {
    int size = std::min(t->quantity, quantity);
    print_trade_pair(t, size);

    quantity -= size;
    t->quantity -= size;

    return (quantity == 0);
  }

  void print() {
    std::cout
      << time << ","
      << symbol << ","
      << side << ","
      << price << ","
      << quantity << std::endl;
  }

  void set_quote(Quote const * quote) {
    bid = quote->bid;
    ask = quote->ask;
  }

  char liquidity() const {
    if (side == 'B') {
      if (price <= bid) return 'P';
      if (price >= ask) return 'A';
    } else {
      if (price >= ask) return 'P';
      if (price <= bid) return 'A';
    }

    return 'X';
  }

  private:
  void print_trade_pair(Trade * t, int size) {
    float pnl = size * (side == 'B' ? t->price - price : price -
        t->price);
    if (pnl > -0.005 && pnl < 0.00) pnl = 0.00;

    std::cout.precision(2);

    std::cout
      << time << ',' /** Open time */
      << t->time << ',' /** Close time */
      << symbol << ',' /** Symbol */
      << size << ',' /** Quantity */
      << std::fixed << pnl << ',' /** PNL */
      << side << ',' /** Open side */
      << t->side << ',' /** Close side */
      << price << ',' /** Open price */
      << t->price << ',' /** Close price */
      << bid << ',' /** Open bid */
      << t->bid << ',' /** Close bid */
      << ask << ',' /** Open ask */
      << t->ask << ',' /** Close ask */
      << this->liquidity() << ',' /** Open liquidity */
      << t->liquidity() << std::endl; /** Cloase liquidity */
  }
};

#endif /* end of include guard: TRADE_H */
