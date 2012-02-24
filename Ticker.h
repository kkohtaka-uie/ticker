#ifndef __TICKER_H__
#define __TICKER_H__

class Ticker {
public:
  explicit Ticker (void);
  Ticker (Ticker const &) = delete;
  Ticker &operator= (Ticker const &) = delete;
  ~Ticker (void);

  void run (
      unsigned short port,
      int backlog
  ) const;
};

#endif // __TICKER_H__
