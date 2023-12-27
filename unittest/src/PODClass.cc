
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
