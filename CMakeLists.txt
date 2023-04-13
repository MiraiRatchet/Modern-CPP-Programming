cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (ProjectName StreamEditor)
project(${ProjectName})

set(Libs App IOperation)
add_subdirectory(App)
add_subdirectory(IOperation)
set(BuildSource src/main.cpp)

include_directories(App/include IOperation/include)

add_executable(${ProjectName} ${BuildSource})
target_link_libraries(${ProjectName} ${Libs})