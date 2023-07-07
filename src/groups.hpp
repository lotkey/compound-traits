#pragma once

namespace lk::traits {
template <template <typename> typename Trait, typename... Types> struct all {
  static constexpr bool value = true;
};

template <template <typename> typename Trait, typename T, typename... Types>
struct all<Trait, T, Types...> {
  static constexpr bool value = Trait<T>::value && all<Trait, Types...>::value;
};

template <template <typename> typename Trait, typename... Types> struct any {
  static constexpr bool value = true;
};

template <template <typename> typename Trait, typename T> struct any<Trait, T> {
  static constexpr bool value = Trait<T>::value;
};

template <template <typename> typename Trait, typename T1, typename T2,
          typename... Types>
struct any<Trait, T1, T2, Types...> {
  static constexpr bool value =
      Trait<T1>::value || any<Trait, T2, Types...>::value;
};

template <template <typename> typename Trait, typename... Types> struct none {
  static constexpr bool value = true;
};

template <template <typename> typename Trait, typename T, typename... Types>
struct none<Trait, T, Types...> {
  static constexpr bool value = !any<Trait, T, Types...>::value;
};

template <template <typename> typename Trait, typename... Types>
constexpr bool all_v = all<Trait, Types...>::value;
template <template <typename> typename Trait, typename... Types>
constexpr bool any_v = any<Trait, Types...>::value;
template <template <typename> typename Trait, typename... Types>
constexpr bool none_v = none<Trait, Types...>::value;
} // namespace lk::traits