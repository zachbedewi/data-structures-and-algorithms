#ifndef STRING_H_
#define STRING_H_
namespace getcracked {

struct string_long
{
  char *m_buffer_ptr;
  size_t m_size;
  size_t m_capacity;
};

struct string_short
{
  static constexpr size_t capacity{ 23uz };
  char m_buffer[capacity];
  unsigned char m_size;
};

class string
{
  using iterator = char *;
  using const_iterator = const char *;

  union {
    string_short s;
    string_long l;
  } m_data;

  static inline constexpr std::size_t shortStringMask = 0x01;
  static inline constexpr std::size_t growthFactor = 2;

  bool isShort() const { return m_data.s.m_size & shortStringMask; }

  bool isLong() const { return !isShort(); }

  bool isFull() const { return size() == capacity(); }

  std::size_t shortSize() const { return m_data.s.m_size >> 1; }

  std::size_t longSize() const { return m_data.l.m_size; }

  std::size_t shortCapacity() const { return string_short::capacity; }

  std::size_t longCapacity() const { return m_data.l.m_capacity; }

  void setShortSize(std::size_t size) { m_data.s.m_size = (size << 1) | shortStringMask; }

  void setLongSize(std::size_t size) { m_data.l.m_size = size; }

  void setSize(std::size_t size)
  {
    if (isShort()) {
      setShortSize(size);
    } else {
      setLongSize(size);
    }
  }

  void setLongCapacity(std::size_t capacity)
  {
    assert(!(capacity & shortStringMask));
    m_data.l.m_capacity = capacity;
  }

  void setShort() { m_data.s.m_size |= shortStringMask; }

  void unsetShort() { m_data.s.m_size &= ~shortStringMask; }

  char *allocate(std::size_t capacity)
  {
    assert(!(capacity & shortStringMask));
    return static_cast<char *>(operator new(capacity));
  }

  void deallocate(char *memory) { operator delete(memory); }

  std::size_t normalize(std::size_t capacity) { return (capacity & shortStringMask) ? capacity + 1 : capacity; }

  void buildShort(const char *chars, std::size_t length)
  {
    std::copy_n(chars, length, m_data.s.m_buffer);
    m_data.s.m_buffer[length] = '\0';
    setShortSize(length);
    setShort();
  }

  void buildLong(const char *chars, std::size_t length)
  {
    std::size_t capacity = normalize(length + 1);
    m_data.l.m_buffer_ptr = allocate(capacity);
    std::copy_n(chars, length, m_data.l.m_buffer_ptr);
    m_data.l.m_buffer_ptr[length] = '\0';
    setLongSize(length);
    setLongCapacity(capacity);
    unsetShort();
  }

  void reset()
  {
    setShort();
    setSize(0);
    m_data.s.m_buffer[0] = '\0';
  }

public:
  string() { reset(); }

  string(const char *chars_array)
  {
    auto const length = std::strlen(chars_array);
    if (length <= string_short::capacity) {
      buildShort(chars_array, length);
    } else {
      buildLong(chars_array, length);
    }
  }

  string(const string &other)
  {
    auto size = other.size();

    if (other.isShort()) {
      setShort();
      setSize(size);
      std::copy_n(other.begin(), size, m_data.s.m_buffer);
      m_data.s.m_buffer[size] = '\0';
      return;
    }

    unsetShort();
    setSize(size);
    setLongCapacity(other.capacity());
    m_data.l.m_buffer_ptr = allocate(capacity());
    std::copy_n(other.begin(), size, m_data.l.m_buffer_ptr);
    m_data.l.m_buffer_ptr[size] = '\0';
  }

  string(string &&other)
  {
    auto size = other.size();

    if (other.isShort()) {
      setShort();
      setSize(size);
      std::copy_n(other.begin(), size, m_data.s.m_buffer);
      m_data.s.m_buffer[size] = '\0';
      other.reset();
      return;
    }

    unsetShort();
    m_data.l.m_buffer_ptr = std::exchange(other.m_data.l.m_buffer_ptr, nullptr);
    m_data.l.m_size = std::exchange(other.m_data.l.m_size, 0);
    m_data.l.m_capacity = std::exchange(other.m_data.l.m_capacity, 0);
    m_data.l.m_buffer_ptr[size] = '\0';
    other.reset();
  }

  void swap(string &other)
  {
    using std::swap;
    swap(*this, other);
  }

  friend void swap(string &lhs, string &rhs)
  {
    auto temp = std::move(lhs.m_data);
    lhs.m_data = std::move(rhs.m_data);
    rhs.m_data = std::move(temp);
  }

  string &operator=(const string &other)
  {
    if (this == std::addressof(other)) { return *this; }
    string(other).swap(*this);
    return *this;
  }

  string &operator=(string &&other)
  {
    string(std::move(other)).swap(*this);
    return *this;
  }

  template<typename InputIt> string(InputIt first, InputIt last)
  {
    for (auto it{ first }; it != last; ++it) { push_back(*it); }
  }

  string(std::initializer_list<char> list) : string{ list.begin(), list.end() } {}

  string(size_t count, char ch)
  {
    for (auto i{ 0uz }; i < count; ++i) { push_back(ch); }
  }

  ~string()
  {
    if (isLong()) { deallocate(m_data.l.m_buffer_ptr); }
  }

  size_t size() const
  {
    if (isShort()) { return shortSize(); }
    return longSize();
  }

  size_t capacity() const
  {
    if (isShort()) { return shortCapacity(); }
    return longCapacity();
  }

  bool empty() { return size() == 0; }

  void reserve(size_t new_capacity)
  {
    auto currentCapacity = capacity();
    if (new_capacity <= currentCapacity || new_capacity < string_short::capacity) { return; }

    new_capacity = normalize(new_capacity + 1);

    auto *memory = allocate(new_capacity);
    auto *bufferPtr = data();
    auto currentSize = size();
    std::copy_n(bufferPtr, currentSize, memory);

    if (isLong()) { deallocate(bufferPtr); }

    m_data.l.m_buffer_ptr = memory;
    m_data.l.m_capacity = new_capacity;
    setLongSize(currentSize);
    unsetShort();
  }

  char *data() { return isShort() ? &m_data.s.m_buffer[0] : m_data.l.m_buffer_ptr; }

  const char *data() const { return isShort() ? &m_data.s.m_buffer[0] : m_data.l.m_buffer_ptr; }

  char &operator[](size_t pos) { return data()[pos]; }

  // const version
  const char &operator[](size_t pos) const { return data()[pos]; }

  // indexed access with bounds checking
  char &at(size_t pos)
  {
    if (pos < 0 || pos > size()) { throw std::out_of_range("Index out of bounds."); }

    return data()[pos];
  }

  char &front() { return data()[0]; }

  char &back() { return data()[size() - 1]; }

  char *begin() { return data(); }

  const char *begin() const { return data(); }

  char *end() { return data() + size(); }

  const char *end() const { return data() + size(); }

  void push_back(char ch)
  {
    if (isFull()) { reserve(capacity() * growthFactor); }

    auto currentSize = size();
    auto *bufferPtr = data();
    bufferPtr[currentSize] = ch;
    bufferPtr[currentSize + 1] = '\0';
    setSize(currentSize + 1);
  }

  void pop_back()
  {
    auto newSize = size() - 1;
    setSize(newSize);
    data()[newSize] = '\0';
  }

  template<typename InputIt> void insert(const_iterator pos, InputIt first, InputIt last)
  {
    auto pos_ = const_cast<iterator>(pos);
    auto first_ = first;
    auto last_ = last;

    if (first < last) {
      auto offset = std::distance(begin(), pos_);
      auto n = std::distance(first, last);
      auto numShifts = std::distance(pos_, end());
      auto remainingCapacity = capacity() - size();

      string temp;
      if (first_ >= begin() && first_ < end() && last_ > begin() && last <= end()) {
        for (auto it{ first_ }; it != last_; ++it) { temp.push_back(*it); }
        first_ = temp.begin();
        last_ = temp.end();
      }

      if (n > remainingCapacity) {
        auto excess = std::max(n - remainingCapacity, 0uz);
        reserve(capacity() + excess);
        pos_ = std::next(begin(), offset);
      }

      if (n < numShifts) {
        std::copy(end() - n, end(), end());
        std::copy_backward(pos_, end() - n, end());
      } else {
        std::copy(pos_, end(), pos_ + n);
      }

      std::copy(first_, last_, pos_);
      setSize(size() + n);
      auto *bufferPtr = data();
      bufferPtr[size()] = '\0';
    }
  }

  iterator erase(const_iterator first, const_iterator last)
  {
    auto first_ = const_cast<iterator>(first);
    auto last_ = const_cast<iterator>(last);
    auto offset = std::distance(begin(), first_);
    auto numShifts = std::distance(last_, end());
    last_ = std::min(last_, end());
    string charsToRemove(first_, last_);
    auto numErased = std::distance(first_, last_);

    auto *bufferPtr = begin();
    for (auto i{ 0uz }; i < numShifts; ++i) { bufferPtr[offset + i] = bufferPtr[offset + i + numErased]; }
    setSize(size() - numErased);
    bufferPtr[size()] = '\0';
    for (auto i{ 0uz }; i < numErased; ++i) { bufferPtr[size() + 1 + i] = charsToRemove[i]; }

    return bufferPtr + offset;
  }
};

}// namespace getcracked

#endif// STRING_H_
