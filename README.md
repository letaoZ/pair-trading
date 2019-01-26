# Pair Trading
      Analyze stock prices (quotes and trades), and find the best paired trades
      
## Files
1. t.txt: trades file.
    > ordered by TIME
    > Each row = at TIME a SYMBOL (SPY) has quote update (BID/ASK) till another price update
2. q.txt: quotes file.
    > ordered by TIME
    > Each row = a ticker (say SPY) was B(ought) or S(old) at a PRICE for QUANTITY many shares. (by someone we don't know)
    
## What we do
Search for the best opportunity to trade. i.e. buy low sell high, search for liquidity.

      setup:
      1. For buy execution: liquidity is Passive if price <= bid; is Aggressive if price >= ask
      2. For sell execution: liquidity is Passive if price >=ask; is Aggressive if price <= bid
      3. Passive = P, Aggressive = A
      trading pairs:
      1. Given any symbol, our inventory is 0. So th 1st execution is always Buy and create +inventory = open trade
      2. Sell will result in decreasing inventory -- close trade
      3. When sell more than our inventory, we are in short position
      4. In our pairs trading result, we also compute the profile and loss. caused by paired trading 
