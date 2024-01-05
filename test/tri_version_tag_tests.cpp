#include <arba/vrsn/tri_version_tag.hpp>
#include <gtest/gtest.h>

TEST(tri_version_tag_tests, constructo__no_arg__succeed)
{
    using version_t = vrsn::tri_version_tag<1, 2, 3>;
    EXPECT_NO_THROW(
        version_t version;
        EXPECT_EQ(version.major(), 1);
        EXPECT_EQ(version.minor(), 2);
        EXPECT_EQ(version.patch(), 3);
        );
}

TEST(tri_version_tag_tests, operator_eq__other__succeed)
{
    EXPECT_EQ((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<1, 2, 3>()));
}

TEST(tri_version_tag_tests, operator_ne__other__succeed)
{
    EXPECT_NE((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<0, 2, 3>()));
    EXPECT_NE((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<1, 0, 3>()));
    EXPECT_NE((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<1, 2, 0>()));
}

TEST(tri_version_tag_tests, operator_lt__other__succeed)
{
    EXPECT_LT((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<1, 2, 4>()));
    EXPECT_LT((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<1, 3, 0>()));
    EXPECT_LT((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<2, 0, 0>()));
}

TEST(tri_version_tag_tests, operator_gt__other__succeed)
{
    EXPECT_GT((vrsn::tri_version_tag<1, 2, 4>()), (vrsn::tri_version_tag<1, 2, 3>()));
    EXPECT_GT((vrsn::tri_version_tag<1, 3, 0>()), (vrsn::tri_version_tag<1, 2, 3>()));
    EXPECT_GT((vrsn::tri_version_tag<2, 0, 0>()), (vrsn::tri_version_tag<1, 2, 3>()));
}

TEST(tri_version_tag_tests, operator_le__other__succeed)
{
    EXPECT_LE((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<1, 2, 3>()));
    EXPECT_LE((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<1, 2, 4>()));
    EXPECT_LE((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<1, 3, 0>()));
    EXPECT_LE((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<2, 0, 0>()));
}

TEST(tri_version_tag_tests, operator_ge__other__succeed)
{
    EXPECT_GE((vrsn::tri_version_tag<1, 2, 3>()), (vrsn::tri_version_tag<1, 2, 3>()));
    EXPECT_GE((vrsn::tri_version_tag<1, 2, 4>()), (vrsn::tri_version_tag<1, 2, 3>()));
    EXPECT_GE((vrsn::tri_version_tag<1, 3, 0>()), (vrsn::tri_version_tag<1, 2, 3>()));
    EXPECT_GE((vrsn::tri_version_tag<2, 0, 0>()), (vrsn::tri_version_tag<1, 2, 3>()));
}

TEST(tri_version_tag_tests, constexpr__valid_args__no_compile_error)
{
    constexpr vrsn::tri_version_tag<0, 1, 5> sv;
    static_assert(sv.major() == 0);
    static_assert(sv.minor() == 1);
    static_assert(sv.patch() == 5);

    constexpr vrsn::tri_version_tag<15, 13, 234> sv2;
    static_assert(sv2.major() == 15);
    static_assert(sv2.minor() == 13);
    static_assert(sv2.patch() == 234);

    static_assert(sv != sv2);
    static_assert(sv < sv2);
}
