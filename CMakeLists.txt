cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (ProjectName IMDB_data_analyze)
project(${ProjectName})

set(Subdirectories App)
add_subdirectory(${Subdirectories})
set(BuildSource src/imdbdataanalyze.cpp)

option(TestingEnabled ON)
if(${TestingEnabled})
    add_subdirectory(tests)
endif()

add_executable(${ProjectName} ${BuildSource})
target_link_libraries(${ProjectName} ${Subdirectories})
