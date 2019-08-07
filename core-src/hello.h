#pragma once

#include <string>
#include <vector>

namespace HelloWorld {

std::string get_hello();

std::string get_personalized_greeting(const std::string& who);

std::vector<std::string> greet_each(std::vector<std::string> v);

} // namespace HelloWorld
