# Compound C++ Type Traits

Type traits with type traits as template parameters.

## [`embed`](./src/embed.hpp)

`embed` aliases type traits with types embedded into them. For example, `embed<std::is_same, int>::front` is an alias for `template <typename T> std::is_same<int, T>`, and `embed<std::is_same, int>::back` is an alias for `template <typename T> std::is_same<T, int>`.

## [`groups`](./src/groups.hpp)

[`groups.hpp`](./src/groups.hpp) defines three type traits:
- `any`
- `all`
- `none`

Each of these type traits contain a `static constexpr bool` named `value`. Each type trait takes a type trait (`template <typename> typename Trait`) and a list of types (`typename Types...`) as its parameters. If the type list is empty, `value` is `true`.

### `all`

`value` is `true` if all of the types in the list match the type trait (`Trait<T>::value` for `T` in `Types...`).

### `any`

`value` is `true` if any of the types in the list match the type trait (`Trait<T>::value` for `T` in `Types...`).

### `none`

`value` is `true` if none of the types in the list match the type trait (`Trait<T>::value` for `T` in `Types...`).

## [Examples](./examples/)

### [`variant`](./examples/variant.hpp)

[`std::variant`](https://en.cppreference.com/w/cpp/utility/variant) is a C++ class template that behaves like a union. `std::variant<int, bool, char>` can hold an `int`, `bool`, or `char`. An `int`, `bool`, or `char` can be assigned to a `std::variant<int, bool, char>`. You can use `embed` and `any` to enable an assignment operator for these types:

```cpp
namespace lk::traits::examples {
template <typename T, typename... Types> class variant {
public:
  // ...
  // Only enable this operator= definition if U is included in T, Types...
  template <typename U>
  std::enable_if_t<
      lk::traits::any_v<lk::traits::embed<std::is_same, U>::front, T, Types...>,
      variant &>
  operator=(U const &u) {
    // ...
  }
  // ...
};
} // namespace lk::traits::examples
```

In the case of `variant<int, bool, char>`, the `operator=` definition will only be enabled when a `variant` is being assigned to from an `int`, `bool`, or `char`.

## Installing

To install the headers, navigate to the root of the repository and create a new directory. Navigate to that directory.
```bash
$> mkdir build
$> cd build
```

Invoke `cmake` to configure the CMake project.
```bash
$> cmake ..
```

Invoke `cmake` to install the headers.
```bash
$> cmake --install .
```

Once installed, you can include the headers like so:
```cpp
#include "lk/traits/embed.hpp"
#include "lk/traits/groups.hpp"
```

## Testing

The [`test`](./test/) directory contains a single C++ source file that contains `static_assert`s. If compiling this source file succeeds, then the `static_assert`s succeeded and the tests were passed.

To run these tests, navigate to the root of the repository and create a new directory. Navigate to that directory.
```bash
$> mkdir build
$> cd build
```

Invoke `cmake` to configure the CMake project.
```bash
$> cmake ..
```

Invoke `cmake` to build the test executable.
```bash
$> cmake --build .
```

If the executable builds then the tests have passed. Running the executable will not do anything.
