#pragma once

#include "embed.hpp"
#include "groups.hpp"

#include <any>
#include <type_traits>

namespace lk::traits::examples {
template <typename T, typename... Types> class variant {
public:
  variant() = default;
  variant(variant const &) = default;
  variant(variant &&) = default;
  variant &operator=(variant const &) = default;
  variant &operator=(variant &&) = default;
  virtual ~variant() = default;

  // Only enable this constructor if U is included in T, Types...
  template <typename U,
            typename = std::enable_if_t<lk::traits::any_v<
                lk::traits::embed<std::is_same, U>::front, T, Types...>>>
  variant(U const &u) : m_data(u) {}

  // Only enable this constructor if U is included in T, Types...
  template <typename U,
            typename = std::enable_if_t<lk::traits::any_v<
                lk::traits::embed<std::is_same, U>::front, T, Types...>>>
  variant(U &&u) : m_data(std::move(u)) {}

  // Only enable this operator= definition if U is included in T, Types...
  template <typename U>
  std::enable_if_t<
      lk::traits::any_v<lk::traits::embed<std::is_same, U>::front, T, Types...>,
      variant &>
  operator=(U const &u) {
    m_data = u;
  }

  // Only enable this operator= definition if U is included in T, Types...
  template <typename U>
  std::enable_if_t<
      lk::traits::any_v<lk::traits::embed<std::is_same, U>::front, T, Types...>,
      variant &>
  operator=(U &&u) {
    m_data = std::move(u);
  }

  // You can implement the rest of the code

private:
  std::any m_data;
};
} // namespace lk::traits::examples

// Please note:
// I do not know if this follows the standard for std::variant. This only serves
// as an example of using lk::traits::embed and lk::traits::any to conditionally
// enable a template definition.