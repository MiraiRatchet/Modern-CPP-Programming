#pragma once

#include <iostream>
#include <sstream>

class App {
 public:
    static int Run(int argc, char** argv);
    static int parseCmd(int argc, std::stringstream& argv);
};
