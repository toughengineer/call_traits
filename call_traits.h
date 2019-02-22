#pragma once

/*Determine return type, number of arguments and argument types of a callable type (function or function object).
Usage:

  int foo() { return 42; }

  using FooReturnType = call_traits<decltype(foo)>::return_type;

  struct Bar
  {
    float method(int) { return 3.141592654; }
  };

  using BarMethodReturnType = call_traits<decltype(&Bar::method)>::return_type;
  const auto BarMethodArgCount = call_traits<decltype(&Bar::method)>::arg_count;
  using BarMethodArg0Type = call_traits<decltype(&Bar::method)>::arg_type<0>;

  struct Baz
  {
    std::string operator()(int) { return {}; }
  };

  using BazReturnType = call_traits<Baz>::return_type;
  const auto BazArgCount = call_traits<Baz>::arg_count;
  using BazArg0Type = call_traits<Baz>::arg_type<0>;

  auto lambda = [](int, char){ return 23; };

  using LambdaReturnType = call_traits<decltype(lambda)>::return_type;
  const auto LambdaArgCount = call_traits<decltype(lambda)>::arg_count;
  using LambdaArg0Type = call_traits<decltype(lambda)>::arg_type<0>;
  using LambdaArg1Type = call_traits<decltype(lambda)>::arg_type<1>;
*/

#include <tuple>

template<typename F>
struct call_traits;

template<typename R, typename... Args>
struct call_traits<R(Args...)>
{
  using return_type = R;
  static constexpr size_t arg_count = sizeof...(Args);
  template<size_t Index>
  using arg_type = std::tuple_element_t<Index, std::tuple<Args...>>;
};

template<typename R, typename... Args>
struct call_traits<R(*)(Args...)> : call_traits<R(Args...)>
{
};

template<typename R, typename F, typename... Args>
struct call_traits<R(F::*)(Args...)> : call_traits<R(Args...)>
{
};

template<typename R, typename F, typename... Args>
struct call_traits<R(F::*)(Args...) const> : call_traits<R(Args...)>
{
};

template<typename F>
struct call_traits : call_traits<decltype(&F::operator())>
{
};
