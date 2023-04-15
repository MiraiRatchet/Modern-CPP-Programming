set(LibraryName App)
add_library(${LibraryName} src/App.cpp)
include_directories(../IOperation/include)
target_include_directories(${LibraryName} PRIVATE include)
