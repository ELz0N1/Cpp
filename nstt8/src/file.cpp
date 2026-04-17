#include "headers/file.hpp"

FileReader& FileReader::operator>>(std::string& str) {
  if (!open_) {
    return *this;
  }

  str.clear();
  int ch;

  while ((ch = fgetc(file_)) != EOF && std::isspace(ch)) {
    continue;
  }

  while (ch != EOF && !std::isspace(ch)) {
    str.push_back(ch);
    ch = fgetc(file_);
  }

  if (ch != EOF) {
    ungetc(ch, file_);
  }

  return *this;
}
FileReader& FileReader::operator>>(char& ch) {
  if (!open_) {
    return *this;
  }

  char holder = fgetc(file_);
  while (!eof() && !std::isalnum(holder)) {
    holder = fgetc(file_);
  }

  if (!eof() && std::isalnum(holder)) {
    ch = holder;
  }

  return *this;
}

FileReader& FileReader::operator>>(int& i) {
  if (!open_) {
    return *this;
  }

  std::string holder;
  char ch = fgetc(file_);

  while (ch != EOF && !std::isdigit(ch)) {
    ch = fgetc(file_);
  }

  while (ch != EOF && std::isdigit(ch)) {
    holder += ch;
    ch = fgetc(file_);
  }

  i = std::stoi(holder);

  return *this;
}

FileWriter& FileWriter::operator<<(std::string& str) {
  if (!open_) {
    return *this;
  }

  fwrite(str.c_str(), 1, str.size(), file_);

  return *this;
}

FileWriter& FileWriter::operator<<(int& i) {
  if (!open_) {
    return *this;
  }

  auto str = std::to_string(i);

  fwrite(str.c_str(), 1, str.size(), file_);

  return *this;
}

FileWriter& FileWriter::operator<<(char& ch) {
  if (!open_) {
    return *this;
  }

  fputc(ch, file_);

  return *this;
}
