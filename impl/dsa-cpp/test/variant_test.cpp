#include <catch2/catch_test_macros.hpp>

#include <variant/variant.hpp>

#include <string>

// Helper to track construction/destruction for lifetime tests
struct Tracker
{
  static int constructions;
  static int destructions;
  static int copies;
  static int moves;

  static void reset()
  {
    constructions = 0;
    destructions = 0;
    copies = 0;
    moves = 0;
  }

  int value;

  Tracker() : value(0) { ++constructions; }
  explicit Tracker(int v) : value(v) { ++constructions; }
  Tracker(const Tracker &other) : value(other.value)
  {
    ++constructions;
    ++copies;
  }
  Tracker(Tracker &&other) noexcept : value(other.value)
  {
    other.value = -1;
    ++constructions;
    ++moves;
  }
  Tracker &operator=(const Tracker &other)
  {
    value = other.value;
    ++copies;
    return *this;
  }
  Tracker &operator=(Tracker &&other) noexcept
  {
    value = other.value;
    other.value = -1;
    ++moves;
    return *this;
  }
  ~Tracker() { ++destructions; }
};

int Tracker::constructions = 0;
int Tracker::destructions = 0;
int Tracker::copies = 0;
int Tracker::moves = 0;

// ============================================================
// Default construction
// ============================================================

TEST_CASE("Default construction initializes first type", "[variant]")
{
  zach::Variant<int, double, char> v;
  REQUIRE(v.index() == 0);
  REQUIRE(zach::get<0>(v) == 0);
}

TEST_CASE("Default construction with non-trivial first type", "[variant]")
{
  zach::Variant<std::string, int> v;
  REQUIRE(v.index() == 0);
  REQUIRE(zach::get<0>(v).empty());
}

// ============================================================
// Converting constructor
// ============================================================

TEST_CASE("Construct from int value", "[variant]")
{
  zach::Variant<int, double, std::string> v(42);
  REQUIRE(v.index() == 0);
  REQUIRE(zach::get<0>(v) == 42);
}

TEST_CASE("Construct from double value", "[variant]")
{
  zach::Variant<int, double, std::string> v(3.14);
  REQUIRE(v.index() == 1);
  REQUIRE(zach::get<1>(v) == 3.14);
}

TEST_CASE("Construct from string value", "[variant]")
{
  std::string s = "hello";
  zach::Variant<int, double, std::string> v(s);
  REQUIRE(v.index() == 2);
  REQUIRE(zach::get<2>(v) == "hello");
}

TEST_CASE("Construct from rvalue string", "[variant]")
{
  zach::Variant<int, double, std::string> v(std::string("world"));
  REQUIRE(v.index() == 2);
  REQUIRE(zach::get<2>(v) == "world");
}

// ============================================================
// get<I> (by index)
// ============================================================

TEST_CASE("get by index returns correct value", "[variant][get]")
{
  zach::Variant<int, double, char> v(3.14);
  REQUIRE(zach::get<1>(v) == 3.14);
}

TEST_CASE("get by index on mutable variant allows modification", "[variant][get]")
{
  zach::Variant<int, double, std::string> v(42);
  zach::get<0>(v) = 99;
  REQUIRE(zach::get<0>(v) == 99);
}

// ============================================================
// get<T> (by type)
// ============================================================

TEST_CASE("get by type returns correct value", "[variant][get]")
{
  zach::Variant<int, double, char> v('x');
  REQUIRE(zach::get<char>(v) == 'x');
}

TEST_CASE("get by type on mutable variant allows modification", "[variant][get]")
{
  zach::Variant<int, double, std::string> v(std::string("original"));
  zach::get<std::string>(v) = "modified";
  REQUIRE(zach::get<std::string>(v) == "modified");
}

// ============================================================
// Copy construction
// ============================================================

TEST_CASE("Copy construction preserves value and index", "[variant][copy]")
{
  zach::Variant<int, double, std::string> v1(std::string("copied"));
  auto v2 = v1;// NOLINT(performance-unnecessary-copy-initialization)
  REQUIRE(v2.index() == 2);
  REQUIRE(zach::get<2>(v2) == "copied");
  // Original unchanged
  REQUIRE(zach::get<2>(v1) == "copied");
}

TEST_CASE("Copy construction with trivial type", "[variant][copy]")
{
  zach::Variant<int, double, char> v1(42);
  auto v2 = v1;// NOLINT(performance-unnecessary-copy-initialization)
  REQUIRE(v2.index() == 0);
  REQUIRE(zach::get<0>(v2) == 42);
}

// ============================================================
// Move construction
// ============================================================

TEST_CASE("Move construction transfers value", "[variant][move]")
{
  zach::Variant<int, double, std::string> v1(std::string("moved"));
  auto v2 = std::move(v1);
  REQUIRE(v2.index() == 2);
  REQUIRE(zach::get<2>(v2) == "moved");
}

TEST_CASE("Move construction with trivial type", "[variant][move]")
{
  zach::Variant<int, double, char> v1(3.14);
  auto v2 = std::move(v1);
  REQUIRE(v2.index() == 1);
  REQUIRE(zach::get<1>(v2) == 3.14);
}

// ============================================================
// Copy assignment
// ============================================================

TEST_CASE("Copy assignment same type index", "[variant][assign]")
{
  zach::Variant<int, double, std::string> v1(std::string("source"));
  zach::Variant<int, double, std::string> v2(42);
  v2 = v1;
  REQUIRE(v2.index() == 2);
  REQUIRE(zach::get<2>(v2) == "source");
  REQUIRE(zach::get<2>(v1) == "source");
}

TEST_CASE("Copy assignment different type index", "[variant][assign]")
{
  zach::Variant<int, double, std::string> v1(3.14);
  zach::Variant<int, double, std::string> v2(std::string("target"));
  v2 = v1;
  REQUIRE(v2.index() == 1);
  REQUIRE(zach::get<1>(v2) == 3.14);
}

// ============================================================
// Move assignment
// ============================================================

TEST_CASE("Move assignment transfers ownership", "[variant][assign]")
{
  zach::Variant<int, double, std::string> v1(std::string("move-me"));
  zach::Variant<int, double, std::string> v2(42);
  v2 = std::move(v1);
  REQUIRE(v2.index() == 2);
  REQUIRE(zach::get<2>(v2) == "move-me");
}

// ============================================================
// Direct type assignment (operator=(T&&))
// ============================================================

TEST_CASE("Assign new value of same type", "[variant][assign]")
{
  zach::Variant<int, double, std::string> v(42);
  v = 99;
  REQUIRE(v.index() == 0);
  REQUIRE(zach::get<0>(v) == 99);
}

TEST_CASE("Assign value of different type changes active alternative", "[variant][assign]")
{
  zach::Variant<int, double, std::string> v(42);
  v = 3.14;
  REQUIRE(v.index() == 1);
  REQUIRE(zach::get<1>(v) == 3.14);
}

TEST_CASE("Assign string to variant holding int", "[variant][assign]")
{
  zach::Variant<int, double, std::string> v(42);
  v = std::string("now a string");
  REQUIRE(v.index() == 2);
  REQUIRE(zach::get<2>(v) == "now a string");
}

TEST_CASE("Multiple reassignments", "[variant][assign]")
{
  zach::Variant<int, double, std::string> v(42);
  REQUIRE(v.index() == 0);

  v = 3.14;
  REQUIRE(v.index() == 1);
  REQUIRE(zach::get<1>(v) == 3.14);

  v = std::string("hello");
  REQUIRE(v.index() == 2);
  REQUIRE(zach::get<2>(v) == "hello");

  v = 100;
  REQUIRE(v.index() == 0);
  REQUIRE(zach::get<0>(v) == 100);
}

// ============================================================
// Swap
// ============================================================

TEST_CASE("Swap variants with same active index", "[variant][swap]")
{
  zach::Variant<int, double, std::string> v1(42);
  zach::Variant<int, double, std::string> v2(99);
  v1.swap(v2);
  REQUIRE(zach::get<0>(v1) == 99);
  REQUIRE(zach::get<0>(v2) == 42);
}

TEST_CASE("Swap variants with different active index", "[variant][swap]")
{
  zach::Variant<int, double, std::string> v1(42);
  zach::Variant<int, double, std::string> v2(std::string("swapped"));
  v1.swap(v2);
  REQUIRE(v1.index() == 2);
  REQUIRE(zach::get<2>(v1) == "swapped");
  REQUIRE(v2.index() == 0);
  REQUIRE(zach::get<0>(v2) == 42);
}

// ============================================================
// index()
// ============================================================

TEST_CASE("index() reflects active alternative", "[variant][index]")
{
  zach::Variant<int, double, char, std::string> v(42);
  REQUIRE(v.index() == 0);

  v = 2.71;
  REQUIRE(v.index() == 1);

  v = 'z';
  REQUIRE(v.index() == 2);

  v = std::string("test");
  REQUIRE(v.index() == 3);
}

// ============================================================
// Lifetime correctness (destructor called properly)
// ============================================================

TEST_CASE("Destructor is called on active member", "[variant][lifetime]")
{
  Tracker::reset();
  {
    zach::Variant<Tracker, int> v(Tracker{ 5 });
    REQUIRE(zach::get<0>(v).value == 5);
  }
  // The Tracker in the variant should have been destroyed
  REQUIRE(Tracker::destructions > 0);
}

TEST_CASE("Reassignment destroys previous and constructs new", "[variant][lifetime]")
{
  Tracker::reset();
  {
    zach::Variant<Tracker, int> v(Tracker{ 10 });
    int destructions_before = Tracker::destructions;
    v = 42;// should destroy the Tracker
    REQUIRE(Tracker::destructions > destructions_before);
    REQUIRE(v.index() == 1);
    REQUIRE(zach::get<1>(v) == 42);
  }
}

TEST_CASE("Copy construction copies the active member", "[variant][lifetime]")
{
  Tracker::reset();
  zach::Variant<Tracker, int> v1(Tracker{ 7 });
  int copies_before = Tracker::copies;
  auto v2 = v1;// NOLINT(performance-unnecessary-copy-initialization)
  REQUIRE(Tracker::copies > copies_before);
  REQUIRE(zach::get<0>(v2).value == 7);
}

TEST_CASE("Move construction moves the active member", "[variant][lifetime]")
{
  Tracker::reset();
  zach::Variant<Tracker, int> v1(Tracker{ 8 });
  int moves_before = Tracker::moves;
  auto v2 = std::move(v1);
  REQUIRE(Tracker::moves > moves_before);
  REQUIRE(zach::get<0>(v2).value == 8);
}

// ============================================================
// tools:: utility tests
// ============================================================

TEST_CASE("findIndexOf finds correct index", "[variant][tools]")
{
  REQUIRE(zach::tools::findIndexOf<int, int, double, char>() == 0);
  REQUIRE(zach::tools::findIndexOf<double, int, double, char>() == 1);
  REQUIRE(zach::tools::findIndexOf<char, int, double, char>() == 2);
}

TEST_CASE("findIndexOf returns variant_npos for missing type", "[variant][tools]")
{
  REQUIRE(zach::tools::findIndexOf<float, int, double, char>() == zach::variant_npos);
}

TEST_CASE("uint_atleast_t selects smallest sufficient type", "[variant][tools]")
{
  STATIC_REQUIRE(std::is_same_v<zach::tools::uint_atleast_t<255>, uint8_t>);
  STATIC_REQUIRE(std::is_same_v<zach::tools::uint_atleast_t<256>, uint16_t>);
  STATIC_REQUIRE(std::is_same_v<zach::tools::uint_atleast_t<65535>, uint16_t>);
  STATIC_REQUIRE(std::is_same_v<zach::tools::uint_atleast_t<65536>, uint32_t>);
}

TEST_CASE("nth_type_t resolves correct type", "[variant][tools]")
{
  STATIC_REQUIRE(std::is_same_v<zach::tools::nth_type_t<0, int, double, char>, int>);
  STATIC_REQUIRE(std::is_same_v<zach::tools::nth_type_t<1, int, double, char>, double>);
  STATIC_REQUIRE(std::is_same_v<zach::tools::nth_type_t<2, int, double, char>, char>);
}
