#include "embed.hpp"
#include "operators.hpp"

#include <type_traits>

struct BasePolymorphic {
  virtual ~BasePolymorphic() = default;
};
struct DerivedPolymorphic : public BasePolymorphic {};

static_assert(lk::traits::embed<std::is_same, int>::front<int>::value);
static_assert(lk::traits::embed<std::is_same, int>::back<int>::value);
static_assert(!lk::traits::embed<std::is_same, int>::front<bool>::value);
static_assert(!lk::traits::embed<std::is_same, int>::back<bool>::value);

// Order matters!
static_assert(lk::traits::embed<std::is_base_of, BasePolymorphic>::front<
              DerivedPolymorphic>::value);
static_assert(!lk::traits::embed<std::is_base_of, BasePolymorphic>::back<
              DerivedPolymorphic>::value);
static_assert(lk::traits::embed<std::is_base_of, DerivedPolymorphic>::back<
              BasePolymorphic>::value);
static_assert(!lk::traits::embed<std::is_base_of, DerivedPolymorphic>::front<
              BasePolymorphic>::value);

static_assert(lk::traits::all_v<std::is_polymorphic>);
static_assert(lk::traits::all_v<std::is_polymorphic, BasePolymorphic,
                                DerivedPolymorphic>);
static_assert(!lk::traits::all_v<std::is_polymorphic, BasePolymorphic,
                                 DerivedPolymorphic, int>);

static_assert(lk::traits::any_v<std::is_polymorphic>);
static_assert(!lk::traits::any_v<std::is_polymorphic, int>);
static_assert(lk::traits::any_v<std::is_polymorphic, BasePolymorphic,
                                DerivedPolymorphic, int>);
static_assert(
    !lk::traits::any_v<std::is_polymorphic, float, bool, char, double, int>);

static_assert(lk::traits::none_v<std::is_polymorphic>);
static_assert(
    lk::traits::none_v<std::is_polymorphic, float, bool, char, double, int>);
static_assert(!lk::traits::none_v<std::is_polymorphic, BasePolymorphic, float,
                                  bool, char, double, int>);

int main() {}