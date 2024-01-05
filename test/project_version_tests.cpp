#include <arba/vrsn/version.hpp>
#include <gtest/gtest.h>

TEST(project_version_tests, test_version_core)
{
    constexpr unsigned major = 0;
    constexpr unsigned minor = 1;
    constexpr unsigned patch = 0;
    static_assert(arba::vrsn::version.core() == arba::vrsn::tri_version(major, minor, patch));
}
