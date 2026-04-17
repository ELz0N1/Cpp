#ifndef READER_WRITER_HEADER
#define READER_WRITER_HEADER

#include "reader.hpp"
#include "writer.hpp"

class ReaderWriter : virtual public Reader, virtual public Writer {};

#endif