# 模板类 `Coor`

```cpp
Coor& operator-= (const Coor<coor_t>& right);
Coor& operator+= (const Coor<coor_t>& right);
Coor& operator+= (const coor_t& value);
Coor& operator-= (const coor_t& value);
```

For example, if `c1` and `c2` are `Coor` objects, and `v` is a `coor_t` object, then the following code snippets demonstrate the usage of these overloaded operators:
```cpp
c1 += c2; // equivalent to c1 = c1 + c2;
c1 -= c2; // equivalent to c1 = c1 - c2;
c1 += v;  // equivalent to c1 = c1 + v;
c1 -= v;  // equivalent to c1 = c1 - v;
```

# Operator overloading for `Coor`

```cpp
template <typename coor_t>
inline Coor<coor_t> operator- (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)
template <typename coor_t>
inline Coor<coor_t> operator+ (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)

template <typename coor_t>
inline Coor<coor_t> operator- (Coor<coor_t>&& lhs, const Coor<coor_t>& rhs)
template <typename coor_t>
inline Coor<coor_t> operator+ (Coor<coor_t>&& lhs, const Coor<coor_t>& rhs)

template <typename coor_t>
inline Coor<coor_t> operator- (const Coor<coor_t>& lhs, const coor_t& val)
template <typename coor_t>
inline Coor<coor_t> operator+ (const Coor<coor_t>& lhs, const coor_t& val)

template <typename coor_t>
inline Coor<coor_t> operator- (Coor<coor_t>&& lhs, const coor_t& rhs)
template <typename coor_t>
inline Coor<coor_t> operator+ (Coor<coor_t>&& lhs, const coor_t& rhs)

template <typename coor_t>
inline bool operator< (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)
template <typename coor_t>
inline bool operator> (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)

template <typename coor_t>
inline bool operator== (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)
template <typename coor_t>
inline bool operator!= (const Coor<coor_t>& lhs, const Coor<coor_t>& rhs)
```