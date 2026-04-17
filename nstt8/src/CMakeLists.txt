add_library(src STATIC 
    file.cpp
    string.cpp
)

target_include_directories(src PUBLIC .)