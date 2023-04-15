set(LibraryName IOperation)
add_library(${LibraryName} src/IOperation.cpp)
target_include_directories(${LibraryName} PRIVATE include)
