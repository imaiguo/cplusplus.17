#include "gtest/gtest.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

struct S
{
    int n;
    std::string s;
    float d;
 
    friend bool operator<(const S& lhs, const S& rhs) noexcept
    {
        // compares lhs.n to rhs.n,
        // then lhs.s to rhs.s,
        // then lhs.d to rhs.d
        // in that order, first non-equal result is returned
        // or false if all elements are equal
        return std::tie(lhs.n, lhs.s, lhs.d) < std::tie(rhs.n, rhs.s, rhs.d);
    }
};
 
// Creates a tuple of lvalue references to its arguments or instances of std::ignore.
TEST(ReferenceWrapper, TIE){
    // Lexicographical comparison demo:
    std::set<S> set_of_s;
 
    S value{42, "Test", 3.14};
    std::set<S>::iterator iter;
    bool is_inserted;
 
    // Unpack a pair:
    std::tie(iter, is_inserted) = set_of_s.insert(value);
    assert(is_inserted);
 
 
    // std::tie and structured bindings:
    auto position = [](int w) { return std::tuple(1 * w, 2 * w); };
 
    auto [x, y] = position(1);
    assert(x == 1 && y == 2);
    std::tie(x, y) = position(2); // reuse x, y with tie
    assert(x == 2 && y == 4);
 
 
    // Implicit conversions are permitted:
    std::tuple<char, short> coordinates(6, 9);
    std::tie(x, y) = coordinates;
    assert(x == 6 && y == 9);
}