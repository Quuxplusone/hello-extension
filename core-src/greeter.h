#pragma once

#include <string>

namespace HelloWorld {

class Greeter {
    std::string who_;
    static int count_;
public:
    explicit Greeter(std::string who);
    std::string get_who() const { return who_; }
    std::string get_greeting() const { return "hello " + who_; }
    ~Greeter();

    static int count();
};

} // namespace HelloWorld
