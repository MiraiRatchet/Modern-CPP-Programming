#include "App.hpp"
#include "IOperation.hpp"

namespace {
constexpr int neededNumberOfCmdLineArguments() {
    return 2;
}
}  // namespace

int App::Run(int argc, char** argv) {
    std::stringstream commands(argv[1]);
    App::parseCmd(argc, commands);
    return 0;
}

int App::parseCmd(int argc, std::stringstream& argv) {
    if (argc != neededNumberOfCmdLineArguments()) {
        return 1;
    }
    std::string argument;
    IOperation* IOperationConveyor;
    getline(argv, argument, ' ');
    if (argument == "echo") {
        getline(argv, argument, ' ');
        IOperationConveyor = new EchoOperation(argument);
    }
    if (argument == "cat") {
        getline(argv, argument, ' ');
        IOperationConveyor = new CatOperation(argument);
    }
    IOperation* currentPtrToIOperation = IOperationConveyor;
    getline(argv, argument, ' ');
    while (!argv.eof()) {
        getline(argv, argument, ' ');
        if (argument == "echo") {
            getline(argv, argument, ' ');
            currentPtrToIOperation->SetNextOperation(new EchoOperation(argument));
        }
        if (argument == "cat") {
            getline(argv, argument, ' ');
            currentPtrToIOperation->SetNextOperation(new CatOperation(argument));
        }
        currentPtrToIOperation = currentPtrToIOperation->GetNextOperation();
        getline(argv, argument, ' ');
    }
    IOperationConveyor->HandleEndOfInput();
    delete IOperationConveyor;
    delete currentPtrToIOperation;
    return 0;
}
