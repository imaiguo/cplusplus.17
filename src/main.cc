
#include "log4cplus/initializer.h"
#include "gtest/gtest.h"

#include "Utils/log4cplusInit.h"

int main(int argc, char **argv) {
    log4cplus::Initializer initializer;
    InitLog4cplus(argv[0]);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
