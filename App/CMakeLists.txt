set(LibraryName App)
add_library(${LibraryName} src/App.cpp)
target_include_directories(${LibraryName} PUBLIC include)
