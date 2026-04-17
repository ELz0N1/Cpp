#include "headers/string.hpp"

StringReader& StringReader::operator>>(std::string& str) {
  if (!open_) {
    return *this;
  }

  while (!eof() && std::isspace(string_[idx])) {
    ++idx;
  }

  while (!eof() && !std::isspace(string_[idx])) {
    str.push_back(string_[idx++]);
  }

  return *this;
}

StringReader& StringReader::operator>>(char& ch) {
  if (!open_) {
    return *this;
  }

  while (!eof() && !std::isalnum(string_[idx])) {
    ++idx;
  }

  if (!eof() && std::isalnum(string_[idx])) {
    ch = string_[idx++];
  }

  return *this;
}

StringReader& StringReader::operator>>(int& i) {
  if (!open_) {
    return *this;
  }

  std::string holder;
  while (!eof() && !std::isdigit(string_[idx])) {
    ++idx;
  }

  while (!eof() && std::isdigit(string_[idx])) {
    holder += string_[idx++];
  }

  if (holder.size() > 0) {
    i = std::stoi(holder);
  } else {
    i = 0;
  }

  return *this;
}

StringWriter& StringWriter::operator<<(std::string& str) {
  if (!open_) {
    return *this;
  }

  for (auto&& s : str) {
    string_.push_back(s);
  }

  return *this;
}
StringWriter& StringWriter::operator<<(int& i) {
  if (!open_) {
    return *this;
  }

  string_ += std::to_string(i);

  return *this;
}

StringWriter& StringWriter::operator<<(char& ch) {
  if (!open_) {
    return *this;
  }

  string_.push_back(ch);

  return *this;
}