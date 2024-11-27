#pragma once

#include "_private/extract_semver.hpp"
#include "concepts/semver.hpp"
#include "numver.hpp"

inline namespace arba
{
namespace vrsn
{
// https://semver.org/spec/v2.0.0.html

class semver : protected numver
{
public:
    constexpr semver(uint64_t major, uint32_t minor, uint32_t patch,
                               std::string_view pre_release = std::string_view(),
                               std::string_view build_metadata = std::string_view());

    constexpr explicit semver(const Numver auto& version_core,
                                        std::string_view pre_release = std::string_view(),
                                        std::string_view build_metadata = std::string_view());

    constexpr semver(std::string_view version);

    constexpr const numver& core() const noexcept { return static_cast<const numver&>(*this); }
    constexpr numver& core() noexcept { return static_cast<numver&>(*this); }
    constexpr std::string_view pre_release() const noexcept { return pre_release_; }
    constexpr std::string_view build_metadata() const noexcept { return build_metadata_; }

    using numver::is_major_compatible_with;
    using numver::is_minor_compatible_with;
    using numver::is_patch_compatible_with;
    using numver::major;
    using numver::minor;
    using numver::patch;
    using numver::set_major;
    using numver::set_minor;
    using numver::set_patch;
    using numver::up_major;
    using numver::up_minor;
    using numver::up_patch;

    inline constexpr bool operator==(const semver& other) const;
    inline constexpr bool operator<(const semver& other) const;
    inline constexpr bool operator!=(const semver& other) const { return !(other == *this); }
    inline constexpr bool operator>(const semver& other) const { return other < *this; }
    inline constexpr bool operator<=(const semver& other) const { return !(other < *this); }
    inline constexpr bool operator>=(const semver& other) const { return !(*this < other); }

private:
    constexpr bool pre_release_is_less_than_(const std::string& right_pr) const;

    static constexpr semver valid_semantic_version_(std::string_view semver);
    static constexpr std::string_view valid_pre_release_(std::string_view pre_release_version);
    static constexpr std::string_view valid_build_metadata_(std::string_view build_metadata);

private:
    std::string pre_release_;
    std::string build_metadata_;
};

constexpr semver::semver(uint64_t major, uint32_t minor, uint32_t patch,
                                             std::string_view pre_release, std::string_view build_metadata)
    : numver(major, minor, patch), pre_release_(valid_pre_release_(pre_release)),
      build_metadata_(valid_build_metadata_(build_metadata))
{
}

constexpr semver::semver(const Numver auto& version_core, std::string_view pre_release,
                                             std::string_view build_metadata)
    : numver(version_core.major(), version_core.minor(), version_core.patch()),
      pre_release_(valid_pre_release_(pre_release)), build_metadata_(valid_build_metadata_(build_metadata))
{
}

constexpr semver::semver(std::string_view version)
    : numver(), pre_release_(), build_metadata_()
{
    *this = valid_semantic_version_(version);
}

inline constexpr bool semver::operator==(const semver& other) const
{
    return static_cast<const numver&>(*this) == static_cast<const numver&>(other)
           && pre_release_ == other.pre_release_;
}

inline constexpr bool semver::operator<(const semver& other) const
{
    auto cmp_res = static_cast<const numver&>(*this) <=> static_cast<const numver&>(other);
    return cmp_res < 0 || (cmp_res == 0 && pre_release_is_less_than_(other.pre_release_));
}

constexpr bool semver::pre_release_is_less_than_(const std::string& right_pr) const
{
    if (pre_release_.empty())
        return false;
    else if (right_pr.empty())
        return true;

    bool left_is_shortest = false;
    bool left_is_num = true;
    bool right_is_num = true;

    const auto left_end_iter = pre_release_.end();
    const auto right_end_iter = right_pr.end();
    auto left_iter = pre_release_.begin();
    auto right_iter = right_pr.begin();
    char left_ch = '\0';
    char right_ch = '\0';

    auto left_part_iter = left_iter;
    auto right_part_iter = right_iter;

    for (;;)
    {
        if (left_iter == left_end_iter)
        {
            if (right_iter == right_end_iter)
                return false;
            left_is_shortest = true;
            break;
        }
        else if (right_iter == right_end_iter)
            break;

        left_ch = *left_iter;
        right_ch = *right_iter;
        if (left_ch != right_ch)
            break;

        ++left_iter, ++right_iter;
        if (left_ch == '.')
        {
            left_is_num = true;
            left_part_iter = left_iter;
            right_part_iter = right_iter;
            // save first char pos of the part.
        }
        else
            left_is_num = left_is_num && (left_ch >= '0' && left_ch <= '9');
    }

    right_is_num = left_is_num;
    bool left_is_lt = left_ch < right_ch;
    bool length_break = true;

    if (left_ch != right_ch)
    {
        length_break = false;
        left_is_num = left_is_num && (left_ch >= '0' && left_ch <= '9');
        right_is_num = right_is_num && (right_ch >= '0' && right_ch <= '9');
        if (!left_is_num && !right_is_num)
            return left_is_lt;
    }
    else if (!left_is_num && !right_is_num)
    {
        return left_is_shortest;
    }

    for (; left_iter != left_end_iter && left_is_num; ++left_iter)
    {
        left_ch = *left_iter;
        if (left_ch == '.')
            break;
        left_is_num = left_is_num && (left_ch >= '0' && left_ch <= '9');
    }

    for (; right_iter != right_end_iter && right_is_num; ++right_iter)
    {
        right_ch = *right_iter;
        if (right_ch == '.')
            break;
        right_is_num = right_is_num && (right_ch >= '0' && right_ch <= '9');
    }

    if (left_is_num)
    {
        if (!right_is_num)
            return true;
        unsigned left_number = std::stoi(std::string(left_part_iter, left_iter));
        unsigned right_number = std::stoi(std::string(right_part_iter, right_iter));
        return left_number < right_number || (length_break && left_is_shortest);
    }
    if (right_is_num)
        return false;
    return left_is_lt;
}

constexpr semver semver::valid_semantic_version_(std::string_view semver_str)
{
    std::string_view major, minor, patch, pr, bm;
    if (!private_::extract_semver_(semver_str, major, minor, patch, pr, bm)) [[unlikely]]
    {
        if (std::is_constant_evaluated())
        {
            compile_time_error("'semver' is not a valid semantic version.");
        }
        throw std::invalid_argument(std::string(semver_str));
    }

    return semver(stoi64(major), stoi64(minor), stoi64(patch), pr, bm);
}

constexpr std::string_view semver::valid_pre_release_(std::string_view pre_release_version)
{
    if (!pre_release_version.empty())
    {
        if (!private_::extract_pre_release_(pre_release_version, pre_release_version)) [[unlikely]]
        {
            if (std::is_constant_evaluated())
            {
                compile_time_error("'pre_release_version' is not a valid pre-release version.");
            }
            throw std::invalid_argument(std::string(pre_release_version));
        }
    }

    return pre_release_version;
}

constexpr std::string_view semver::valid_build_metadata_(std::string_view build_metadata)
{
    if (!build_metadata.empty())
    {
        if (!private_::check_build_metadata_(build_metadata)) [[unlikely]]
        {
            if (std::is_constant_evaluated())
            {
                compile_time_error("'build_metadata' is not a valid build metadata string.");
            }
            throw std::invalid_argument(std::string(build_metadata));
        }
    }

    return build_metadata;
}

}
}

template <class CharT>
struct std::formatter<::arba::vrsn::semver, CharT>
{
    template <class FormatParseContext>
    inline constexpr auto parse(FormatParseContext& ctx)
    {
        return ctx.begin();
    }

    template <class FormatContext>
    auto format(const ::arba::vrsn::semver& version, FormatContext& ctx) const
    {
        return std::format_to(ctx.out(), "{}-{}+{}", version.core(), version.pre_release(), version.build_metadata());
    }
};
