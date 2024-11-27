#include <arba/vrsn/vtag.hpp>
#include <gtest/gtest.h>

TEST(vtag_tests, constructo__no_arg__succeed)
{
    using version_t = vrsn::vtag<1, 2, 3>;
    EXPECT_NO_THROW(
        version_t version;
        EXPECT_EQ(version.major(), 1);
        EXPECT_EQ(version.minor(), 2);
        EXPECT_EQ(version.patch(), 3);
        );
}

TEST(vtag_tests, operator_eq__other__succeed)
{
    EXPECT_EQ((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<1, 2, 3>()));
}

TEST(vtag_tests, operator_ne__other__succeed)
{
    EXPECT_NE((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<0, 2, 3>()));
    EXPECT_NE((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<1, 0, 3>()));
    EXPECT_NE((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<1, 2, 0>()));
}

TEST(vtag_tests, operator_lt__other__succeed)
{
    EXPECT_LT((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<1, 2, 4>()));
    EXPECT_LT((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<1, 3, 0>()));
    EXPECT_LT((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<2, 0, 0>()));
}

TEST(vtag_tests, operator_gt__other__succeed)
{
    EXPECT_GT((vrsn::vtag<1, 2, 4>()), (vrsn::vtag<1, 2, 3>()));
    EXPECT_GT((vrsn::vtag<1, 3, 0>()), (vrsn::vtag<1, 2, 3>()));
    EXPECT_GT((vrsn::vtag<2, 0, 0>()), (vrsn::vtag<1, 2, 3>()));
}

TEST(vtag_tests, operator_le__other__succeed)
{
    EXPECT_LE((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<1, 2, 3>()));
    EXPECT_LE((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<1, 2, 4>()));
    EXPECT_LE((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<1, 3, 0>()));
    EXPECT_LE((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<2, 0, 0>()));
}

TEST(vtag_tests, operator_ge__other__succeed)
{
    EXPECT_GE((vrsn::vtag<1, 2, 3>()), (vrsn::vtag<1, 2, 3>()));
    EXPECT_GE((vrsn::vtag<1, 2, 4>()), (vrsn::vtag<1, 2, 3>()));
    EXPECT_GE((vrsn::vtag<1, 3, 0>()), (vrsn::vtag<1, 2, 3>()));
    EXPECT_GE((vrsn::vtag<2, 0, 0>()), (vrsn::vtag<1, 2, 3>()));
}

TEST(vtag_tests, constexpr__valid_args__no_compile_error)
{
    constexpr vrsn::vtag<0, 1, 5> sv;
    static_assert(sv.major() == 0);
    static_assert(sv.minor() == 1);
    static_assert(sv.patch() == 5);

    constexpr vrsn::vtag<15, 13, 234> sv2;
    static_assert(sv2.major() == 15);
    static_assert(sv2.minor() == 13);
    static_assert(sv2.patch() == 234);

    static_assert(sv != sv2);
    static_assert(sv < sv2);
}
