#pragma once

namespace lk::traits {
// value is true if Trait<T>::value is true for all T in Types... or if Types...
// is empty
template <template <typename> typename Trait, typename... Types> struct all {
  // Base case: no types
  static constexpr bool value = true;
};

template <template <typename> typename Trait, typename T, typename... Types>
struct all<Trait, T, Types...> {
  // 1+ types
  static constexpr bool value = Trait<T>::value && all<Trait, Types...>::value;
};

// value is true if Trait<T>::value is true for any T in Types... or if Types...
// is empty
template <template <typename> typename Trait, typename... Types> struct any {
  // Base case: no types
  static constexpr bool value = true;
};

template <template <typename> typename Trait, typename T> struct any<Trait, T> {
  // 1 type
  static constexpr bool value = Trait<T>::value;
};

template <template <typename> typename Trait, typename T1, typename T2,
          typename... Types>
struct any<Trait, T1, T2, Types...> {
  // 2+ types
  static constexpr bool value =
      Trait<T1>::value || any<Trait, T2, Types...>::value;
};

// value is true if Trait<T> is false for all T in Types... or if Types... is
// empty
template <template <typename> typename Trait, typename... Types> struct none {
  // Base case: no types
  static constexpr bool value = true;
};

template <template <typename> typename Trait, typename T, typename... Types>
struct none<Trait, T, Types...> {
  // 1+ types
  static constexpr bool value = !any<Trait, T, Types...>::value;
};

template <template <typename> typename Trait, typename... Types>
constexpr bool all_v = all<Trait, Types...>::value;
template <template <typename> typename Trait, typename... Types>
constexpr bool any_v = any<Trait, Types...>::value;
template <template <typename> typename Trait, typename... Types>
constexpr bool none_v = none<Trait, Types...>::value;
} // namespace lk::traits