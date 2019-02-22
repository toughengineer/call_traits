#include <cstdio>
#include <string>

#include "call_traits.h"

int foo();

using FooReturnType = call_traits<decltype(foo)>::return_type;
static_assert(std::is_same_v<FooReturnType, int>);

struct Bar
{
  float method(int);
};

using BarMethodReturnType = call_traits<decltype(&Bar::method)>::return_type;
const auto BarMethodArgCount = call_traits<decltype(&Bar::method)>::arg_count;
using BarMethodArg0Type = call_traits<decltype(&Bar::method)>::arg_type<0>;
static_assert(std::is_same_v<BarMethodReturnType, float>);
static_assert(BarMethodArgCount == 1);
static_assert(std::is_same_v<BarMethodArg0Type, int>);

struct Baz
{
  std::string operator()(int) const;
};

using BazReturnType = call_traits<Baz>::return_type;
const auto BazArgCount = call_traits<Baz>::arg_count;
using BazArg0Type = call_traits<Baz>::arg_type<0>;
static_assert(std::is_same_v<BazReturnType, std::string>);
static_assert(BazArgCount == 1);
static_assert(std::is_same_v<BazArg0Type, int>);

auto lambda = [](int, char) { return 23; };

using LambdaReturnType = call_traits<decltype(lambda)>::return_type;
const auto LambdaArgCount = call_traits<decltype(lambda)>::arg_count;
using LambdaArg0Type = call_traits<decltype(lambda)>::arg_type<0>;
using LambdaArg1Type = call_traits<decltype(lambda)>::arg_type<1>;
static_assert(std::is_same_v<LambdaReturnType, int>);
static_assert(LambdaArgCount == 2);
static_assert(std::is_same_v<LambdaArg0Type, int>);
static_assert(std::is_same_v<LambdaArg1Type, char>);

int main()
{
  printf("ok");
}
