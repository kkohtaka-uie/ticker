#ifndef __TIMESTAMP_H__
#define __TIMESTAMP_H__

#include <mutex>
#include <string>

class Timestamp {

private:

  explicit Timestamp (void);

public:

  Timestamp (Timestamp const &) = delete;
  Timestamp &operator= (Timestamp const &) = delete;
  ~Timestamp (void);

  static const Timestamp &instance (void);
  const std::string timestamp (void) const;
};

#endif // __TIMESTAMP_H__
