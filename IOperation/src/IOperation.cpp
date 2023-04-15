#include <IOperation.hpp>

IOperation* IOperation::GetNextOperation() const {
    return nextOperation_;
}

void IOperation::HandleEndOfInput() {
    ProcessLine();
    if (nextOperation_) {
        nextOperation_->input_ = output_;
        nextOperation_->HandleEndOfInput();
        return;
    }
    std::cout << output_ << std::endl;
};
void IOperation::SetNextOperation(IOperation* const nextOperation) {
    nextOperation_ = nextOperation;
}

void CatOperation::ProcessLine(){
    auto stream = std::make_unique<std::ifstream>(filename_);
    std::string content((std::istreambuf_iterator<char>(*stream)), (std::istreambuf_iterator<char>()));
    output_ = input_ + content;
}