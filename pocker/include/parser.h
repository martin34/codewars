#pragma once

#include <tuple>

#include "hand.h"

namespace pocker {
std::pair<Hand, Hand> ParseHandsFromLine(std::string const &line);
} // namespace pocker