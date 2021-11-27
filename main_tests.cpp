
#ifdef QUEUE_SIZE
#pragma message ("Ok")
#endif

#define QUEUE_SIZE 4
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

TEST(InitQueue, FailsOnNullQueue) {
    ASSERT_FALSE( zq_init( nullptr ) );
}

TEST(NullQueue, EverythingFails) {
    uint8_t value = 42;
    ASSERT_FALSE( zq_is_empty( nullptr ) );

    ASSERT_FALSE( zq_push( nullptr, 127 ) );
    ASSERT_FALSE( zq_pop( nullptr, &value ) );
    ASSERT_EQ(value, 42);

    ASSERT_FALSE( zq_leftpush( nullptr, 127 ) );
    ASSERT_FALSE( zq_leftpop( nullptr, &value ) );
    ASSERT_EQ(value, 42);
}

TEST(PopToNull, AlwaysFails) {
    EasyQueue queue;
    int ok_count = 0;

    ok_count += zq_pop( &queue, nullptr );
    ok_count += zq_leftpop( &queue, nullptr );

    ASSERT_EQ(ok_count, 0);
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

TEST(PopQueue, WorksWhenNotEmpty) {
    EasyQueue queue;
    int ok_count = 0;
    uint8_t value;

    ok_count += zq_init( &queue );
    ok_count += zq_push( &queue, 10 );
    ok_count += zq_push( &queue, 20 );

    ok_count += zq_pop( &queue, &value );
    ASSERT_EQ(value, 20);
    ok_count += zq_pop( &queue, &value );
    ASSERT_EQ(value, 10);
    ASSERT_EQ(ok_count, 5);

    ok_count += zq_pop( &queue, &value );
    ASSERT_EQ(value, 10);
    ASSERT_EQ(ok_count, 5);
}

TEST(LeftPushQueue, WorksWhenEmpty) {
    EasyQueue queue;
    int ok_count = 0;
    uint8_t value = 42;

    ok_count += zq_init( &queue );
    ok_count += zq_leftpush( &queue, value );
    ok_count += zq_leftpush( &queue, value );
    ok_count += zq_leftpush( &queue, value );

    ASSERT_EQ(ok_count, 4);
}

TEST(LeftPushQueue, FailsWhenFull) {
    EasyQueue queue;
    int ok_count = 0;
    uint8_t value = 42;

    ok_count += zq_init( &queue );

    queue.length = QUEUE_SIZE;  // consumers should never access struct members
    ok_count += zq_leftpush( &queue, value );
    ok_count += zq_leftpush( &queue, value );
    ok_count += zq_leftpush( &queue, value );

    ASSERT_EQ(ok_count, 1);
    ASSERT_EQ(queue.length, QUEUE_SIZE);
}

TEST(LeftPopQueue, FailsWhenEmpty) {
    EasyQueue queue;
    int ok_count = 0;
    uint8_t value = 42;

    ok_count += zq_init( &queue );
    ok_count += zq_leftpop( &queue, &value );
    ok_count += zq_leftpop( &queue, &value );
    ok_count += zq_leftpop( &queue, &value );

    ASSERT_EQ(ok_count, 1);
    ASSERT_EQ(value, 42);
}

TEST(LeftPopQueue, WorksWhenNotEmpty) {
    EasyQueue queue;
    int ok_count = 0;
    uint8_t value;

    ok_count += zq_init( &queue );
    ok_count += zq_push( &queue, 10 );
    ok_count += zq_push( &queue, 20 );

    ok_count += zq_leftpop( &queue, &value );
    ASSERT_EQ(value, 10);
    ok_count += zq_leftpop( &queue, &value );
    ASSERT_EQ(value, 20);
    ASSERT_EQ(ok_count, 5);

    ok_count += zq_leftpop( &queue, &value );
    ASSERT_EQ(value, 20);
    ASSERT_EQ(ok_count, 5);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
