#include <iostream>
#include <span>

class App {
 public:
    static int Run(int argc, char** argv);
    int parseCmd(int argc, char** argv);
};