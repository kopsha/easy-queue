
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
    int ok_count = 0;

    ok_count += zq_init( &first );
    ok_count += zq_init( &second );
    ASSERT_EQ( ok_count, 2 );

    ASSERT_TRUE( zq_is_empty( &first ) );
    ASSERT_TRUE( zq_is_empty( &second ) );
}

TEST(InitQueue, UninitializedQueueIsNotEmpty) {
    EasyQueue queue;
    // Should not really rely on such test
    ASSERT_FALSE( zq_is_empty( &queue ) );
}

TEST(PushQueue, WorksWhenEmpty) {
    EasyQueue queue;
    int ok_count = 0;
    uint8_t value = 42;

    ok_count += zq_init( &queue );
    ok_count += zq_push( &queue, value );
    ok_count += zq_push( &queue, value );
    ok_count += zq_push( &queue, value );

    ASSERT_EQ(ok_count, 4);
}

TEST(PushQueue, FailsWhenFull) {
    EasyQueue queue;
    int ok_count = 0;
    uint8_t value = 42;

    ok_count += zq_init( &queue );

    queue.length = QUEUE_SIZE;  // consumers should never access struct members
    ok_count += zq_push( &queue, value );
    ok_count += zq_push( &queue, value );
    ok_count += zq_push( &queue, value );

    ASSERT_EQ(ok_count, 1);
    ASSERT_EQ(queue.length, QUEUE_SIZE);
}

TEST(PopQueue, FailsWhenEmpty) {
    EasyQueue queue;
    int ok_count = 0;
    uint8_t value = 42;

    ok_count += zq_init( &queue );
    ok_count += zq_pop( &queue, &value );
    ok_count += zq_pop( &queue, &value );
    ok_count += zq_pop( &queue, &value );

    ASSERT_EQ(ok_count, 1);
    ASSERT_EQ(value, 42);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
