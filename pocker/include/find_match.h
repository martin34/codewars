namespace utils {
template <class InputIt>
InputIt find_match(InputIt begin, InputIt end, InputIt pattern_begin,
                   InputIt pattern_end) {
  if (std::distance(pattern_begin, pattern_end) > std::distance(begin, end)) {
    return end;
  }
  for (; begin != end; ++begin) {
    bool match = *begin == *pattern_begin;
    auto ibegin = begin;
    auto pbegin = pattern_begin;
    for (; ibegin != end && pbegin != pattern_end; ++ibegin, ++pbegin) {
      match = *ibegin == *pbegin;
    }
    if (match) {
      return begin;
    }
  }
  return end;
}
} // namespace utils