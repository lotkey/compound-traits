#pragma once

namespace lk::traits {
// Used to embed types into a type trait
// For example:
//   lk::traits::embed<std::is_same, int>::front becomes an alias for
//   std::is_same<int, T>
template <template <typename...> typename Trait, typename... EmbeddedTypes>
struct embed {
  template <typename... Types> using front = Trait<EmbeddedTypes..., Types...>;
  template <typename... Types> using back = Trait<Types..., EmbeddedTypes...>;
};
} // namespace lk::traits