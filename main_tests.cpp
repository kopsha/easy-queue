
#ifdef QUEUE_SIZE
#pragma message ("Ok")
#endif

#define QUEUE_SIZE 24
extern "C" {
    #include "easy_queue.h"
}


#include <gtest/gtest.h>


TEST(InitQueue, NewQueueIsEmpty) {
    EasyQueue_st first;
    EasyQueue_st second;

    easy_reset_queue( &first );
    easy_reset_queue( &second );

    EXPECT_TRUE( easy_is_queue_empty( &first ) );
    EXPECT_TRUE( easy_is_queue_empty( &second ) );

    EXPECT_FALSE( easy_queue_failed() );
    EXPECT_FALSE( easy_queue_failed() );
}

TEST(PushQueue, AddElementIncreasesSize) {
    EasyQueue_st q;


}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
