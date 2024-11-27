#pragma once

#include "numver.hpp"

#include <string_view>

inline namespace arba
{
namespace vrsn
{
inline namespace concepts
{

template <typename VersionT>
concept Semver = Numver<VersionT> && requires(const VersionT& value) {
    {
        value.pre_release_version()
    } -> std::convertible_to<std::string_view>;
    {
        value.build_metadata()
    } -> std::convertible_to<std::string_view>;
};

}
}
}
