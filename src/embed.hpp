#pragma once

namespace lk::traits {
template <template <typename...> typename Trait, typename... EmbeddedTypes>
struct embed {
  template <typename... Types> using front = Trait<EmbeddedTypes..., Types...>;
  template <typename... Types> using back = Trait<Types..., EmbeddedTypes...>;
};
} // namespace lk