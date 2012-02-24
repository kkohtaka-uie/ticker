#include "Timestamp.h"

static Timestamp timestamp_;

const Timestamp &
Timestamp::instance (
    void
) {

  return timestamp_;
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
