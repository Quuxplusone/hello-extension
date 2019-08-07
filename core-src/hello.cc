#include <string>
#include <vector>
#include "hello.h"

std::string HelloWorld::get_hello()
{
    return "hello world";
}

std::string HelloWorld::get_personalized_greeting(const std::string& who)
{
    return "hello " + who;
}

std::vector<std::string> HelloWorld::greet_each(std::vector<std::string> v)
{
    for (auto& elt : v) {
        elt = HelloWorld::get_personalized_greeting(elt);
    }
    return v;
}
