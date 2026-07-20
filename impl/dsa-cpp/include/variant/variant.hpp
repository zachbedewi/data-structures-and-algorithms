#ifndef DSA_VARIANT_HPP
#define DSA_VARIANT_HPP

#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>
#include <type_traits>
#include <utility>

namespace zach {

inline constexpr std::size_t variant_npos = static_cast<std::size_t>(-1);

namespace tools {
  template<typename T, typename... Ts> constexpr std::size_t findIndexOf()
  {
    auto i{ 0UZ };
    for (auto isSameType : { std::is_same_v<T, Ts>... }) {
      if (isSameType) { return i; }
      ++i;
    }
    return variant_npos;
  }

  template<typename T, typename... Ts>
  concept IsWithinBounds = (findIndexOf<T, Ts...>() < sizeof...(Ts));

  template<typename T, typename... Ts>
    requires IsWithinBounds<T, Ts...>
  constexpr std::size_t index_of_v = findIndexOf<T, Ts...>();

  template<typename T, typename... Ts>
  concept IndexExists = requires {
    { index_of_v<T, Ts...> };
  };

  template<std::size_t max> constexpr auto findMinUint()
  {
    if constexpr (max <= std::numeric_limits<uint8_t>::max()) {
      return uint8_t{};
    } else if constexpr (max <= std::numeric_limits<uint16_t>::max()) {
      return uint16_t{};
    } else if constexpr (max <= std::numeric_limits<uint32_t>::max()) {
      return uint32_t{};
    } else if constexpr (max <= std::numeric_limits<uint64_t>::max()) {
      return uint64_t{};
    }
  }

  template<std::size_t max> using uint_atleast_t = decltype(findMinUint<max>());

  template<std::size_t n,
    typename T0 = void,
    typename T1 = void,
    typename T2 = void,
    typename T3 = void,
    typename T4 = void,
    typename T5 = void,
    typename T6 = void,
    typename T7 = void,
    typename T8 = void,
    typename T9 = void,
    typename... Ts>
  constexpr auto getNthType()
  {
    if constexpr (n == 0) {
      return std::type_identity<T0>{};
    } else if constexpr (n == 1) {
      return std::type_identity<T1>{};
    } else if constexpr (n == 2) {
      return std::type_identity<T2>{};
    } else if constexpr (n == 3) {
      return std::type_identity<T3>{};
    } else if constexpr (n == 4) {
      return std::type_identity<T4>{};
    } else if constexpr (n == 5) {
      return std::type_identity<T5>{};
    } else if constexpr (n == 6) {
      return std::type_identity<T6>{};
    } else if constexpr (n == 7) {
      return std::type_identity<T7>{};
    } else if constexpr (n == 8) {
      return std::type_identity<T8>{};
    } else if constexpr (n == 9) {
      return std::type_identity<T8>{};
    } else {
      return getNthType<n - 10, Ts...>;
    }
  }

  template<std::size_t n, typename... Ts>
    requires(n < sizeof...(Ts))
  using nth_type_t = typename decltype(getNthType<n, Ts...>())::type;

  template<template<typename...> typename Template, typename... Ts> struct IsInstanceOfTemplate : std::false_type
  {
  };

  template<template<typename...> typename Template, typename... Ts>
  struct IsInstanceOfTemplate<Template, Template<Ts...>> : std::true_type
  {
  };

  template<typename T, template<typename...> typename Template>
  concept IsInstanceOf = IsInstanceOfTemplate<Template, T>::value;

  template<typename First, typename... Rest> struct union_
  {
    union {
      First head;
      union_<Rest...> tail;
    };

    constexpr union_() {}
    constexpr ~union_() {}

    template<typename... Args>
    constexpr explicit union_(std::in_place_index_t<0U> /* i */, Args &&...args)
      : head{ std::forward<Args>(args)... } {};

    template<std::size_t I, typename... Args>
    constexpr explicit union_(std::in_place_index_t<I> /* i */, Args &&...args)
      : tail{ std::in_place_index<I - 1>, std::forward<Args>(args)... } {};
  };

  template<typename T> struct union_<T>
  {
    T head;

    constexpr union_() = default;
    constexpr ~union_() = default;

    template<typename... Args>
    constexpr explicit union_(std::in_place_index_t<0U> /* i */, Args &&...args)
      : head{ std::forward<Args>(args)... } {};
  };

  template<typename> struct UnionSize;

  template<typename... Ts> struct UnionSize<union_<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>
  {
  };

  template<typename T> constexpr std::size_t union_size_v = UnionSize<T>::value;

  template<std::size_t I, typename T>
    requires IsInstanceOf<std::remove_cvref_t<T>, union_> && (I < union_size_v<std::remove_cvref_t<T>>)
  constexpr auto &&get(T &&self)
  {
    if constexpr (I == 0) {
      return std::forward<T>(self).head;
    } else {
      return get<I - 1>(std::forward<T>(self).tail);
    }
  }

  template<std::size_t I, typename... Ts, typename... Args>
  constexpr void construct_at(union_<Ts...> &self, Args &&...args)
  {
    std::construct_at(&self, std::in_place_index<I>, std::forward<Args>(args)...);
  }

  template<std::size_t I, typename... Ts> constexpr void destroy_at(union_<Ts...> &self)
  {
    std::destroy_at(&get<I>(self));
  }
}// namespace tools

template<typename... Ts> class Variant
{
private:
  using index_type = tools::uint_atleast_t<sizeof...(Ts)>;

  static constexpr std::size_t size_ = sizeof...(Ts);
  tools::union_<Ts...> storage_;
  index_type idx_;

public:
  constexpr Variant() : idx_(0) { tools::construct_at<0>(storage_); }

  template<typename T, typename U = std::remove_cvref_t<T>>
    requires tools::IndexExists<U, Ts...>
  constexpr explicit Variant(T &&x)
  {
    constexpr auto idx = tools::index_of_v<U, Ts...>;
    tools::construct_at<idx>(storage_, std::forward<T>(x));
    idx_ = idx;
  }

  constexpr Variant(const Variant &other) : idx_(other.idx_)
  {
    index_type idx = other.idx_;
    constexpr auto idxSeq = std::make_index_sequence<sizeof...(Ts)>();
    [&]<auto... Indices>(std::index_sequence<Indices...>) {
      (((idx == Indices) ? (tools::construct_at<Indices>(storage_, tools::get<Indices>(other.storage_)), 0) : 0), ...);
    }(idxSeq);
  }

  constexpr Variant(Variant &&other) noexcept : idx_(other.idx_)
  {
    index_type idx = other.idx_;
    constexpr auto idxSeq = std::make_index_sequence<sizeof...(Ts)>();
    [&]<auto... Indices>(std::index_sequence<Indices...>) {
      (((idx == Indices) ? (tools::construct_at<Indices>(storage_, tools::get<Indices>(std::move(other.storage_))), 0)
                         : 0),
        ...);
    }(idxSeq);
  }

  void swap(Variant<Ts...> &other) noexcept
  {
    using std::swap;
    if (idx_ == other.idx_) {
      constexpr auto idxSeq = std::make_index_sequence<sizeof...(Ts)>();
      [&]<auto... Indices>(std::index_sequence<Indices...>) {
        (((idx_ == Indices) ? (swap(tools::get<Indices>(storage_), tools::get<Indices>(other.storage_)), 0) : 0), ...);
      }(idxSeq);
    } else {
      auto tmp = std::move(*this);
      std::destroy_at(this);
      std::construct_at(this, std::move(other));
      std::destroy_at(&other);
      std::construct_at(&other, std::move(tmp));
    }
  }

  Variant<Ts...> &operator=(const Variant<Ts...> &other)
  {
    Variant(other).swap(*this);
    return *this;
  }

  Variant<Ts...> &operator=(Variant<Ts...> &&other) noexcept
  {
    Variant(std::move(other)).swap(*this);
    return *this;
  }

  template<typename T, typename U = std::remove_cvref_t<T>>
    requires tools::IndexExists<U, Ts...>
  constexpr Variant<Ts...> &operator=(T &&element)
  {
    constexpr auto idxSeq = std::make_index_sequence<sizeof...(Ts)>();
    [&]<auto... Indices>(std::index_sequence<Indices...>) {
      (((idx_ == Indices) ? (tools::destroy_at<Indices>(storage_), 0) : 0), ...);
    }(idxSeq);
    constexpr auto idx = tools::index_of_v<U, Ts...>;
    tools::construct_at<idx>(storage_, std::forward<T>(element));
    idx_ = idx;
    return *this;
  }

  constexpr ~Variant()
  {
    constexpr auto idxSeq = std::make_index_sequence<sizeof...(Ts)>();
    [&]<auto... Indices>(std::index_sequence<Indices...>) {
      (((idx_ == Indices) ? (tools::destroy_at<Indices>(storage_), 0) : 0), ...);
    }(idxSeq);
  }

  [[nodiscard]] constexpr std::size_t index() const noexcept { return idx_; }

  template<size_t I, typename... Us> constexpr friend decltype(auto) get(const Variant<Us...> &v);

  template<typename T, typename... Us> constexpr friend T &get(const Variant<Us...> &v);

  template<size_t I, typename... Us> constexpr friend decltype(auto) get(Variant<Us...> &v);

  template<typename T, typename... Us> constexpr friend T &get(Variant<Us...> &v);
};

template<size_t I, typename... Ts> constexpr decltype(auto) get(const Variant<Ts...> &v)
{
  return tools::get<I>(v.storage_);
}

template<typename T, typename... Ts> constexpr T &get(const Variant<Ts...> &v)
{
  return tools::get<tools::index_of_v<T, Ts...>>(v.storage_);
}

template<size_t I, typename... Ts> constexpr decltype(auto) get(Variant<Ts...> &v) { return tools::get<I>(v.storage_); }

template<typename T, typename... Ts> constexpr T &get(Variant<Ts...> &v)
{
  return tools::get<tools::index_of_v<T, Ts...>>(v.storage_);
}

}// namespace zach

#endif
