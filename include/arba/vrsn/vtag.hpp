#pragma once

#include "is_compatible_with.hpp"

#include <cstdint>
#include <tuple>

inline namespace arba
{
namespace vrsn
{

template <uint64_t Major, uint32_t Minor, uint32_t Patch>
class vtag
{
public:
    using tuple_type = std::tuple<uint64_t, uint32_t, uint32_t>;

    constexpr vtag() = default;

    inline static constexpr uint64_t major() noexcept { return Major; }
    inline static constexpr uint32_t minor() noexcept { return Minor; }
    inline static constexpr uint32_t patch() noexcept { return Patch; }

    inline constexpr tuple_type to_tuple() const noexcept { return tuple_type(Major, Minor, Patch); }

    inline constexpr bool is_major_compatible_with(const Numver auto& rv) const noexcept
    {
        return vrsn::is_major_compatible_with(*this, rv);
    }

    inline constexpr bool is_minor_compatible_with(const Numver auto& rv) const noexcept
    {
        return vrsn::is_minor_compatible_with(*this, rv);
    }

    inline constexpr bool is_patch_compatible_with(const Numver auto& rv) const noexcept
    {
        return vrsn::is_patch_compatible_with(*this, rv);
    }

    template <uint64_t OtherMajor, uint32_t OtherMinor, uint32_t OtherPatch>
    inline constexpr auto operator==(const vtag<OtherMajor, OtherMinor, OtherPatch>& other) const noexcept
    {
        return to_tuple() == other.to_tuple();
    }

    template <uint64_t OtherMajor, uint32_t OtherMinor, uint32_t OtherPatch>
    inline constexpr auto operator!=(const vtag<OtherMajor, OtherMinor, OtherPatch>& other) const noexcept
    {
        return to_tuple() != other.to_tuple();
    }

    template <uint64_t OtherMajor, uint32_t OtherMinor, uint32_t OtherPatch>
    inline constexpr auto operator<(const vtag<OtherMajor, OtherMinor, OtherPatch>& other) const noexcept
    {
        return to_tuple() < other.to_tuple();
    }

    template <uint64_t OtherMajor, uint32_t OtherMinor, uint32_t OtherPatch>
    inline constexpr auto operator>(const vtag<OtherMajor, OtherMinor, OtherPatch>& other) const noexcept
    {
        return to_tuple() > other.to_tuple();
    }

    template <uint64_t OtherMajor, uint32_t OtherMinor, uint32_t OtherPatch>
    inline constexpr auto operator<=(const vtag<OtherMajor, OtherMinor, OtherPatch>& other) const noexcept
    {
        return to_tuple() <= other.to_tuple();
    }

    template <uint64_t OtherMajor, uint32_t OtherMinor, uint32_t OtherPatch>
    inline constexpr auto operator>=(const vtag<OtherMajor, OtherMinor, OtherPatch>& other) const noexcept
    {
        return to_tuple() >= other.to_tuple();
    }
};

} // namespace vrsn
} // namespace arba
