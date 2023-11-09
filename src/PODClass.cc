
// POD = Plain Old Data
/*
用来说明类/结构体的属性，具体来说它是指没有使用面相对象的思想来设计的类/结构体。POD的全称是Plain Old Data，Plain表明它是一个普通的类型，没有虚函数虚继承等特性；Old表明它与C兼容。

POD类型在C++中有两个独立的特性：

支持静态初始化（static initialization）
拥有和C语言一样的内存布局（memory layout
*/

#include <type_traits>

#include <gtest/gtest.h>


// #pragma pack(push, 1)
struct S
{
    char   m0;
    double m1;
    short  m2;
    char   m3;
    // private: int z; // warning: 'S' is a non-standard-layout type
};
// #pragma pack(pop)

TEST(PODCLASS, PTRDIFF){
 
    std::cout << "sizeof(S) = [" << sizeof(S) << "]."<<std::endl;
    std::cout << "sizeof(char) = [" << sizeof(char) << "]."<<std::endl;
    std::cout << "sizeof(double) = [" << sizeof(double) << "]."<<std::endl;
    std::cout << "sizeof(short) = [" << sizeof(short) << "]."<<std::endl;
    std::cout << "sizeof(char) = [" << sizeof(char) << "]."<<std::endl;
    std::cout
        << "offset of char   m0 = " << offsetof(S, m0) << '\n'
        << "offset of double m1 = " << offsetof(S, m1) << '\n'
        << "offset of short  m2 = " << offsetof(S, m2) << '\n'
        << "offset of char   m3 = " << offsetof(S, m3) << '\n';
        // << "offset of char   z = " << offsetof(S, z) << '\n';
}

// std::integral_constant wraps a static constant of specified type. It is the base class for the C++ type traits.
TEST(PODCLASS, INTEGRAL_CONSTANT){

    typedef std::integral_constant<int, 2> two_t;
    typedef std::integral_constant<int, 4> four_t;
 
    static_assert(!std::is_same<two_t, four_t>::value, "two_t and four_t are equal!");
 
    static_assert(two_t::value * 2 == four_t::value, "2*2 != 4");
 
    enum class my_e { e1, e2 };
 
    typedef std::integral_constant<my_e, my_e::e1> my_e_e1;
    typedef std::integral_constant<my_e, my_e::e2> my_e_e2;
 
    static_assert(my_e_e1() == my_e::e1);
 
    static_assert(my_e_e1::value != my_e::e2, "my_e_e1::value == my_e::e2");
 
    static_assert(std::is_same<my_e_e2, my_e_e2>::value, "my_e_e2 != my_e_e2");
}