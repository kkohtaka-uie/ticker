#include "Timestamp.h"

const Timestamp &
Timestamp::instance (
    void
) {

  // Double-checked locking pattern.

  static Timestamp *pInstance = nullptr;

  if (nullptr == pInstance) {

    static std::mutex mutex;
    std::lock_guard< std::mutex > lock(mutex);

    if (nullptr == pInstance) {

      pInstance = new Timestamp();
    }
  }

  return *pInstance;
}

Timestamp::Timestamp (
    void
) {}

Timestamp::~Timestamp (
    void
) {}

const std::string
Timestamp::timestamp (
    void
) const {

  return std::string("ok?");
}
