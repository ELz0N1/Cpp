
#pragma once

#include <iostream>
#include <utility>

template <typename Checker, typename... Args>
int getIndexOfFirstMatch(Checker check, Args... args) {
  int index = 0;
  int found = -1;

  (void)(... || (check(std::forward<Args>(args)) ? (found = index, true) : (++index, false)));

  return found;
}