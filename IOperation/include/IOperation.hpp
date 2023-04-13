#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

class IOperation {
 public:
    virtual ~IOperation() {};
    virtual void ProcessLine() = 0;
    void HandleEndOfInput();
    void SetNextOperation(IOperation* const nextOperation);
    IOperation* GetNextOperation() const;

 protected:
    IOperation* nextOperation_;
    std::string output_;
    std::string input_;
};

class CatOperation : public IOperation {
 public:
    explicit CatOperation(const std::string& str) : filename_(str) {
        nextOperation_ = nullptr;
        output_ = "";
        input_ = "";
    }
    ~CatOperation() {}
    void ProcessLine() override;

 private:
    std::string filename_;
};

class EchoOperation : public IOperation {
 public:
    explicit EchoOperation(const std::string& str) {
        output_ = str + '\n';
        nextOperation_ = nullptr;
        input_ = "";
    }
    void ProcessLine() override {}
};
