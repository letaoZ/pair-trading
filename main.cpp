#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include "Quote.hpp"
#include "Trade.hpp"

using namespace std;

int main(int argc, const char *argv[])
{
  if (argc != 3) {
    cout << "Please specify quotes file and trades file." << endl;
    return 1;
  }

  const char * quotesFilePath = argv[1];
  const char * tradesFilePath = argv[2];

  ifstream quotesFile(quotesFilePath);
  ifstream tradesFile(tradesFilePath);

  if (!quotesFile.is_open()) {
    cout << "Cannot open quotes file." << endl;
  }
  if (!tradesFile.is_open()) {
    cout << "Cannot open trades file." << endl;
  }

  int timestep = 1;
  string quoteline;
  string tradeline;

  // ignore headers.
  getline(quotesFile, quoteline);
  getline(tradesFile, tradeline);

  unordered_map<string, Quote> quotes;

  /** next_quote: stores the next quote to update the quote table. */
  getline(quotesFile, quoteline);
  Quote next_quote(quoteline);

  unordered_map<string, queue<Trade *>> trades;
  getline(tradesFile, tradeline);

  cout
    << "OPEN_TIME," << "CLOSE_TIME,"
    << "SYMBOL," << "QUANTITY," << "PNL,"
    << "OPEN_SIDE," << "CLOSE_SIDE,"
    << "OPEN_PRICE," << "CLOSE_PRICE,"
    << "OPEN_BID," << "CLOSE_BID,"
    << "OPEN_ASK," << "CLOSE_ASK,"
    << "OPEN_LIQUIDITY," << "CLOSE_LIQUIDITY" << endl;

  while (!tradeline.empty()) {
    Trade * t = new Trade(tradeline);

    /** Update current quotes. */
    while (!quoteline.empty() && next_quote.time <= t->time) {
      quotes[next_quote.symbol] = next_quote;

      getline(quotesFile, quoteline);
      if (!quoteline.empty()) next_quote = Quote(quoteline);
    }

    /** Get current quote. */
    Quote &q = quotes[t->symbol];
    t->bid = q.bid;
    t->ask = q.ask;

    /** Get opened trades for this stock. */
    queue<Trade *> &list = trades[t->symbol];

    /** Try to close every opening trade. */
    while (!list.empty() && t->quantity > 0) {
      Trade * front = list.front();

      /** If the opening trade has the same side, break. */
      if (front->side == t->side) break;

      if (front->close(t)) {
        list.pop();
        delete front;
      }
    }

    /** If we still have some left, add to the list. */
    if (t->quantity > 0) {
      list.push(t);
    } else {
      delete t;
    }

    /** Read next trade. */
    getline(tradesFile, tradeline);
  }

  quotesFile.close();
  tradesFile.close();
  return 0;
}
