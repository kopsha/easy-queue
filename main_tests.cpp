
#ifdef QUEUE_SIZE
#pragma message ("Ok")
#endif

#define QUEUE_SIZE 24
extern "C" {
    #include "easy_queue.h"
}


#include <gtest/gtest.h>


TEST(InitQueue, NewQueueIsEmpty) {
    EasyQueue first;
    EasyQueue second;

    zq_init( &first );
    zq_init( &second );

    EXPECT_TRUE( zq_is_empty( &first ) );
    EXPECT_TRUE( zq_is_empty( &second ) );

}

TEST(PushQueue, AddElementIncreasesSize) {
    EasyQueue q;


}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
