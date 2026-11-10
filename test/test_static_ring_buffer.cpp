#include "autolib/static_ring_buffer.hpp"

#include <cstdint>

#include <gtest/gtest.h>

using autolib::StaticRingBuffer;

// @verifies REQ-RB-001
TEST(StaticRingBuffer, CapacityIsCompileTimeAndStorageIsInline) {
    static_assert(StaticRingBuffer<std::uint8_t, 16U>::capacity() == 16U);
    // No heap: the object size is dominated by its inline storage.
    static_assert(sizeof(StaticRingBuffer<std::uint8_t, 16U>) >= 16U);
    const StaticRingBuffer<std::uint8_t, 16U> rb{};
    EXPECT_TRUE(rb.empty());
}

// @verifies REQ-RB-002
TEST(StaticRingBuffer, PushOnFullIsRejectedWithoutOverwrite) {
    StaticRingBuffer<int, 2U> rb{};
    EXPECT_TRUE(rb.push(1));
    EXPECT_TRUE(rb.push(2));
    EXPECT_TRUE(rb.full());
    EXPECT_FALSE(rb.push(3));
    EXPECT_EQ(rb.pop(), 1);
    EXPECT_EQ(rb.pop(), 2);
}

// @verifies REQ-RB-003
TEST(StaticRingBuffer, PopOnEmptyReturnsNullopt) {
    StaticRingBuffer<int, 4U> rb{};
    EXPECT_FALSE(rb.pop().has_value());
}

// @verifies REQ-RB-004
TEST(StaticRingBuffer, PreservesFifoOrderAcrossWrapAround) {
    StaticRingBuffer<int, 3U> rb{};
    for (int round = 0; round < 5; ++round) {
        EXPECT_TRUE(rb.push(round * 10));
        EXPECT_TRUE(rb.push(round * 10 + 1));
        EXPECT_EQ(rb.pop(), round * 10);
        EXPECT_EQ(rb.pop(), round * 10 + 1);
    }
    EXPECT_TRUE(rb.empty());
}
