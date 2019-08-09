#include <string>
#include "greeter.h"

namespace HelloWorld {

int Greeter::count_ = 0;

Greeter::Greeter(std::string who) {
    ++count_;
    who_ = who;
}

Greeter::~Greeter() {
    --count_;
}

int Greeter::count() {
    return count_;
}

} // namespace HelloWorld
