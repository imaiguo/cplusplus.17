
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include <gtest/gtest.h>

// 计算机 可以用以表示数值的最大值 受限于cpu通用寄存器的大小

TEST(NUMERIC, SIZEOF){
    log4cplus::Logger logger = log4cplus::Logger::getRoot();

    // size_t 理论上可以存储任何对象的大小 64位平台为8字节大小, 32位平台为4字节大小
    LOG4CPLUS_TRACE(logger, "sizeof(size_t) = [" << sizeof(size_t) << "].");
    LOG4CPLUS_TRACE(logger, "sizeof(int) = [" << sizeof(int) << "].");
    LOG4CPLUS_TRACE(logger, "sizeof(long) = [" << sizeof(long) << "].");
    LOG4CPLUS_TRACE(logger, "sizeof(long long) = [" << sizeof(long long) << "].");
}

#define COUT(x) std::cout << std::setw(w) << #x << " = " << x << '\n'

// Limits of integer types
TEST(NUMERIC, LIMIT){
    constexpr int w = 14;
    std::cout << std::left; 
    COUT( CHAR_BIT       );
    COUT( MB_LEN_MAX     );
    COUT( CHAR_MIN       );
    COUT( CHAR_MAX       );
    COUT( SCHAR_MIN      );
    COUT( SHRT_MIN       );
    COUT( INT_MIN        );
    COUT( LONG_MIN       );
    COUT( LLONG_MIN      );
    COUT( SCHAR_MAX      );
    COUT( SHRT_MAX       );
    COUT( INT_MAX        );
    COUT( LONG_MAX       );
    COUT( LLONG_MAX      );
    COUT( UCHAR_MAX      );
    COUT( USHRT_MAX      );
    COUT( UINT_MAX       );
    COUT( ULONG_MAX      );
    COUT( ULLONG_MAX     );
    COUT( PTRDIFF_MIN    );
    COUT( PTRDIFF_MAX    );
    COUT( SIZE_MAX       );
    COUT( SIG_ATOMIC_MIN );
    COUT( SIG_ATOMIC_MAX );
    COUT( WCHAR_MIN      );
    COUT( WCHAR_MAX      );
    COUT( WINT_MIN       );
    COUT( WINT_MAX       );
}

// std:: ptrdiff_t the signed integer type of the result of subtracting two pointers.
TEST(NUMERIC, ptrdiff_t){
    const std::size_t N = 10;
    int* a = new int[N];
    int* end = a + N;

    for (std::ptrdiff_t i = N; i > 0; --i)
        std::cout << (*(end - i) = i) << ' ';

    std::cout << '\n';
    delete[] a;
}
