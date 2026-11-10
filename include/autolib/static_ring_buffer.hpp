/**
 * @file static_ring_buffer.hpp
 * @brief Fixed-capacity FIFO without dynamic memory, for embedded C++.
 *
 * @satisfies REQ-RB-001, REQ-RB-002, REQ-RB-003, REQ-RB-004
 */
#ifndef AUTOLIB_STATIC_RING_BUFFER_HPP
#define AUTOLIB_STATIC_RING_BUFFER_HPP

#include <array>
#include <cstddef>
#include <optional>
#include <type_traits>

namespace autolib {

template <typename T, std::size_t Capacity>
class StaticRingBuffer {
    static_assert(Capacity > 0U, "Capacity must be greater than zero");
    static_assert(std::is_trivially_copyable_v<T>,
                  "T must be trivially copyable (no hidden allocations)");

public:
    /// Adds an element. Returns false (and keeps existing data) when full.
    [[nodiscard]] constexpr bool push(const T& value) noexcept {
        if (full()) {
            return false;
        }
        storage_[tail_] = value;
        tail_ = next(tail_);
        ++size_;
        return true;
    }

    /// Removes the oldest element, or returns std::nullopt when empty.
    [[nodiscard]] constexpr std::optional<T> pop() noexcept {
        if (empty()) {
            return std::nullopt;
        }
        T value = storage_[head_];
        head_ = next(head_);
        --size_;
        return value;
    }

    [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0U; }
    [[nodiscard]] constexpr bool full() const noexcept { return size_ == Capacity; }
    [[nodiscard]] constexpr std::size_t size() const noexcept { return size_; }
    [[nodiscard]] static constexpr std::size_t capacity() noexcept { return Capacity; }

private:
    [[nodiscard]] static constexpr std::size_t next(std::size_t idx) noexcept {
        return (idx + 1U) % Capacity;
    }

    std::array<T, Capacity> storage_{};
    std::size_t head_{0U};
    std::size_t tail_{0U};
    std::size_t size_{0U};
};

}  // namespace autolib

#endif  // AUTOLIB_STATIC_RING_BUFFER_HPP
