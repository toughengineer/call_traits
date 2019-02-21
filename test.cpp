#include <cstdio>
#include <string>

#include "call_traits.h"

int foo();

using fooReturnType = call_traits<decltype(foo)>::return_type;

struct Bar
{
  float method(int);
};

using BarMethodReturnType = call_traits<decltype(&Bar::method)>::return_type;
const auto BarMethodArgCount = call_traits<decltype(&Bar::method)>::arg_count;
using BarMethodArg0Type = call_traits<decltype(&Bar::method)>::arg_type<0>;

struct Baz
{
  std::string operator()(int) const;
};

using BazReturnType = call_traits<Baz>::return_type;
const auto BazArgCount = call_traits<Baz>::arg_count;
using BazArg0Type = call_traits<Baz>::arg_type<0>;

auto lambda = [](int, char) { return 23; };

using LambdaReturnType = call_traits<decltype(lambda)>::return_type;
const auto LambdaArgCount = call_traits<decltype(lambda)>::arg_count;
using LambdaArg0Type = call_traits<decltype(lambda)>::arg_type<0>;
using LambdaArg1Type = call_traits<decltype(lambda)>::arg_type<1>;

int main()
{
  printf("ok");
}
