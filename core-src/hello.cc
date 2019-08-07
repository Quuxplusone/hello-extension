#include <string>
#include "hello.h"

std::string HelloWorld::get_hello()
{
    return "hello world";
}

std::string HelloWorld::get_personalized_greeting(const std::string& who)
{
    return "hello " + who;
}
