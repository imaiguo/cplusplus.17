

#include "log4cplus/logger.h"
#include "log4cplus/loggingmacros.h"

#include "gtest/gtest.h"


using namespace log4cplus;
using namespace log4cplus::helpers;

int random() {
    return 2;
}

TEST(log4cpusTest, PrintLog){
    Logger logger = Logger::getRoot();
    int i = 10;
    LOG4CPLUS_TRACE(logger, "trace and get the fingerprint: " << "random integer: " << random());
    LOG4CPLUS_DEBUG(logger, "this is debug log: " << "random integer: "<< random());
    LOG4CPLUS_INFO(logger, "the information centry...." << "[ 1 + 1 = " << 1 + 1 << "]");
    LOG4CPLUS_WARN(logger, "Writing warning messages to log...." << i);
    LOG4CPLUS_ERROR(logger, "ooooooh, there is an error....");

    EXPECT_EQ(logger.getName(), L"root");
}