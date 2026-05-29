add_library(src STATIC 
    buffered_file.cpp
    buffered_io.cpp
    buffered_string.cpp
    file.cpp
    string.cpp
)

target_include_directories(src PUBLIC .)