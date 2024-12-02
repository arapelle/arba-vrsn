#include <arba/vrsn/semver.hpp>
#include <gtest/gtest.h>

TEST(semantic_version_tests, semantic_version_constructor__x_y_z__no_exception)
{
    vrsn::semver version(1, 2, 3);
    ASSERT_EQ(version.major(), 1);
    ASSERT_EQ(version.minor(), 2);
    ASSERT_EQ(version.patch(), 3);
    ASSERT_EQ(version.pre_release(), "");
    ASSERT_EQ(version.build_metadata(), "");
}

TEST(semantic_version_tests, semantic_version_constructor__x_y_z_pr__no_exception)
{
    vrsn::semver version(1, 2, 3, "alpha.1");
    ASSERT_EQ(version.major(), 1);
    ASSERT_EQ(version.minor(), 2);
    ASSERT_EQ(version.patch(), 3);
    ASSERT_EQ(version.pre_release(), "alpha.1");
    ASSERT_EQ(version.build_metadata(), "");
}

TEST(semantic_version_tests, semantic_version_constructor__x_y_z_pr_bm__no_exception)
{
    vrsn::semver version(1, 2, 3, "alpha.1", "specific-build");
    ASSERT_EQ(version.major(), 1);
    ASSERT_EQ(version.minor(), 2);
    ASSERT_EQ(version.patch(), 3);
    ASSERT_EQ(version.pre_release(), "alpha.1");
    ASSERT_EQ(version.build_metadata(), "specific-build");
}

TEST(semantic_version_tests, semantic_version_constructor__ver_pr__no_exception)
{
    vrsn::numver version_core(1, 2, 3);
    vrsn::semver version(version_core, "pre-release.1");
    ASSERT_EQ(version.major(), 1);
    ASSERT_EQ(version.minor(), 2);
    ASSERT_EQ(version.patch(), 3);
    ASSERT_EQ(version.pre_release(), "pre-release.1");
    ASSERT_EQ(version.build_metadata(), "");
}

TEST(semantic_version_tests, semantic_version_constructor__ver_pr_bm__no_exception)
{
    vrsn::numver version_core(1, 2, 3);
    vrsn::semver version(version_core, "alpha.1", "specific-build");
    ASSERT_EQ(version.major(), 1);
    ASSERT_EQ(version.minor(), 2);
    ASSERT_EQ(version.patch(), 3);
    ASSERT_EQ(version.pre_release(), "alpha.1");
    ASSERT_EQ(version.build_metadata(), "specific-build");
}

TEST(semantic_version_tests, semantic_version_constructor__x_y_z_bpr_bm__expect_exception)
{
    try
    {
        vrsn::semver version(1, 2, 3, "alpha_1", "specific-build");
        FAIL();
    }
    catch (...)
    {
        SUCCEED();
    }
}

TEST(semantic_version_tests, semantic_version_constructor__x_y_z_pr_bbm__expect_exception)
{
    try
    {
        vrsn::semver version(1, 2, 3, "alpha.1", "specific_build");
        FAIL();
    }
    catch (...)
    {
        SUCCEED();
    }
}

void test_semver_valid_sv(unsigned major, unsigned minor, unsigned patch, std::string_view pre_release = "",
                          std::string_view build_metadata = "")
{
    std::string version_str = std::format("{}.{}.{}", major, minor, patch);
    if (!pre_release.empty())
        version_str = std::format("{}-{}", version_str, pre_release);
    if (!build_metadata.empty())
        version_str = std::format("{}+{}", version_str, build_metadata);
    std::string_view version_strv(version_str);
    vrsn::semver semver(version_strv);
    ASSERT_EQ(semver.major(), major);
    ASSERT_EQ(semver.minor(), minor);
    ASSERT_EQ(semver.patch(), patch);
    ASSERT_EQ(semver.pre_release(), pre_release);
    ASSERT_EQ(semver.build_metadata(), build_metadata);
}

TEST(semantic_version_tests, semantic_version_constructor__sv_triv__no_exception)
{
    test_semver_valid_sv(0, 11, 0);
    test_semver_valid_sv(0, 11, 1);
    test_semver_valid_sv(0, 11, 12);
    test_semver_valid_sv(0, 11, 0, "pre");
    test_semver_valid_sv(0, 11, 1, "pre");
    test_semver_valid_sv(0, 11, 12, "pre");
    test_semver_valid_sv(0, 11, 0, "", "bm");
    test_semver_valid_sv(0, 11, 1, "", "bm");
    test_semver_valid_sv(0, 11, 12, "", "bm");
}

TEST(semantic_version_tests, semantic_version_constructor__sv_triv_prer__no_exception)
{
    // w/o bm
    test_semver_valid_sv(0, 1, 0, "0.0");
    test_semver_valid_sv(0, 1, 0, "7.7");
    test_semver_valid_sv(0, 1, 0, "12.23");
    test_semver_valid_sv(0, 1, 0, "123.234");

    test_semver_valid_sv(0, 1, 0, "0a.0a");
    test_semver_valid_sv(0, 1, 0, "0ab.0ab");

    test_semver_valid_sv(0, 1, 0, "7a.7a");
    test_semver_valid_sv(0, 1, 0, "7ab.7ab");

    test_semver_valid_sv(0, 1, 0, "72a.72a");
    test_semver_valid_sv(0, 1, 0, "72ab.72ab");

    test_semver_valid_sv(0, 1, 0, "alpha.alpha");
    test_semver_valid_sv(0, 1, 0, "alpha0.alpha0");
    test_semver_valid_sv(0, 1, 0, "-56.-56");
    test_semver_valid_sv(0, 1, 0, "alpha-56.alpha-56");

    // +bm
    test_semver_valid_sv(0, 1, 0, "0.0", "bm");
    test_semver_valid_sv(0, 1, 0, "7.7", "bm");
    test_semver_valid_sv(0, 1, 0, "12.23", "bm");
    test_semver_valid_sv(0, 1, 0, "123.234", "bm");

    test_semver_valid_sv(0, 1, 0, "0a.0a", "bm");
    test_semver_valid_sv(0, 1, 0, "0ab.0ab", "bm");

    test_semver_valid_sv(0, 1, 0, "7a.7a", "bm");
    test_semver_valid_sv(0, 1, 0, "7ab.7ab", "bm");

    test_semver_valid_sv(0, 1, 0, "72a.72a", "bm");
    test_semver_valid_sv(0, 1, 0, "72ab.72ab", "bm");

    test_semver_valid_sv(0, 1, 0, "alpha.alpha", "bm");
    test_semver_valid_sv(0, 1, 0, "alpha0.alpha0", "bm");
    test_semver_valid_sv(0, 1, 0, "-56.-56", "bm");
    test_semver_valid_sv(0, 1, 0, "alpha-56.alpha-56", "bm");
}

TEST(semantic_version_tests, semantic_version_constructor__sv_full__no_exception)
{
    test_semver_valid_sv(0, 1, 0, "pre", "0aZ-.0aZ-");
    test_semver_valid_sv(0, 1, 0, "pre", "a-Z0.a-Z0");
    test_semver_valid_sv(0, 1, 0, "pre", "00");
}

void test_semver_invalid_sv(std::string_view version_strv)
{
    try
    {
        vrsn::semver semver(version_strv);
        FAIL();
    }
    catch (const std::exception&)
    {
        SUCCEED();
    }
}

TEST(semantic_version_tests, semantic_version_constructor__invalid_sv__expect_exception)
{
    test_semver_invalid_sv("");
    test_semver_invalid_sv(".");
    test_semver_invalid_sv("..");
    test_semver_invalid_sv("..");
    test_semver_invalid_sv("0..");
    test_semver_invalid_sv("0.1.");
    test_semver_invalid_sv("0.1.");
    test_semver_invalid_sv("0.1.0.");
    test_semver_invalid_sv("0.1a.0");
    test_semver_invalid_sv("0.1.0a");

    test_semver_invalid_sv("0.1.0-$0.pre");
    test_semver_invalid_sv("0.1.0-0$.pre");
    test_semver_invalid_sv("0.1.0-pre.0$");

    test_semver_invalid_sv("0.1.0-");
    test_semver_invalid_sv("0.1.0-+");

    test_semver_invalid_sv("0.1.0-00.0a");
    test_semver_invalid_sv("0.1.0-0a.00");
    test_semver_invalid_sv("0.1.0-06.0a");
    test_semver_invalid_sv("0.1.0-0a.06");
    test_semver_invalid_sv("0.1.0-00+bm");
    test_semver_invalid_sv("0.1.0-06+bm");

    test_semver_invalid_sv("0.1.0-pre+");

    test_semver_invalid_sv("0.1.0-pre+$bm");
    test_semver_invalid_sv("0.1.0-pre+.bm");
    test_semver_invalid_sv("0.1.0-pre+bm.");
    test_semver_invalid_sv("0.1.0-pre+b..m");
}

TEST(semantic_version_tests, semantic_version_constructor__bad_sv__expect_exception)
{
    try
    {
        vrsn::semver version_1("0.1.2-alpha_0+specific-build");
        FAIL();
    }
    catch (const std::exception&)
    {
        SUCCEED();
    }

    try
    {
        vrsn::semver version_2("0.1.2-alpha-0+specific_build");
        FAIL();
    }
    catch (const std::exception&)
    {
        SUCCEED();
    }

    try
    {
        vrsn::semver version_3("0.1.2-alpha.bad_item+item.specific_build");
        FAIL();
    }
    catch (const std::exception&)
    {
        SUCCEED();
    }

    try
    {
        vrsn::semver version_4("0.1.2-alpha-0+item.specific_build");
        FAIL();
    }
    catch (const std::exception&)
    {
        SUCCEED();
    }
}

TEST(semantic_version_tests, version_core__normal__no_exception)
{
    vrsn::semver version(0, 1, 2);
    ASSERT_EQ(version.core(), vrsn::numver(0, 1, 2));
    const vrsn::semver c_version(0, 1, 2);
    ASSERT_EQ(c_version.core(), vrsn::numver(0, 1, 2));
}

TEST(semantic_version_tests, operator_eq__normal__no_exception)
{
    ASSERT_EQ(vrsn::semver(0, 1, 2, "alpha.1", "build-title"),
              vrsn::semver(0, 1, 2, "alpha.1", "build-title"));
    ASSERT_EQ(vrsn::semver(0, 1, 2, "alpha.1", "build-title"), vrsn::semver(0, 1, 2, "alpha.1"));
    ASSERT_EQ(vrsn::semver(0, 1, 2, "alpha.1", "build-title"),
              vrsn::semver("0.1.2-alpha.1+build-title"));
    ASSERT_EQ(vrsn::semver(0, 1, 2, "alpha.1", "build-title"), vrsn::semver("0.1.2-alpha.1"));
}

TEST(semantic_version_tests, operator_ne__normal__no_exception)
{
    ASSERT_NE(vrsn::semver(0, 1, 2, "alpha.1", "build-title"),
              vrsn::semver(0, 1, 2, "alpha.2", "build-title"));
    ASSERT_NE(vrsn::semver(0, 1, 3, "alpha.1", "build-title"),
              vrsn::semver(0, 1, 2, "alpha.1", "build-title"));
}

TEST(semantic_version_tests, operator_lt__normal__no_exception)
{
    EXPECT_TRUE(vrsn::semver("1.2.3") < vrsn::semver("1.2.4"));
    EXPECT_TRUE(vrsn::semver("1.2.3-1234") < vrsn::semver("1.2.3-123a"));
    EXPECT_TRUE(vrsn::semver("1.2.3-alpha.99") < vrsn::semver("1.2.3-alpha.00a"));
    EXPECT_TRUE(vrsn::semver("1.2.3-alpha.9999") < vrsn::semver("1.2.3-alpha.00a"));
    EXPECT_TRUE(vrsn::semver("1.2.3-alpha.7") < vrsn::semver("1.2.3-alpha.22"));
    EXPECT_TRUE(vrsn::semver("1.2.3-alpha.7") < vrsn::semver("1.2.3-alpha.77"));
    EXPECT_TRUE(vrsn::semver("1.2.3-alpha.1") < vrsn::semver("1.2.3-alpha.-v"));
    EXPECT_TRUE(vrsn::semver("1.2.3-1.4") < vrsn::semver("1.2.3-alpha.2"));
    EXPECT_TRUE(vrsn::semver("1.2.3-alpha.beta.4") < vrsn::semver("1.2.3-alpha.gamma.2"));
    EXPECT_TRUE(vrsn::semver("1.2.3-1456") < vrsn::semver("1.2.3--lol"));
    EXPECT_TRUE(vrsn::semver("1.2.3-1456") < vrsn::semver("1.2.3-1456.123"));
    vrsn::semver va("1.2.3-045a");
    vrsn::semver vb("1.2.3-145a");
    EXPECT_TRUE(va < vb);

    EXPECT_FALSE(vrsn::semver("1.2.3-alpha.22") < vrsn::semver("1.2.3-alpha.7"));
    EXPECT_FALSE(vrsn::semver("1.2.3-alpha.77") < vrsn::semver("1.2.3-alpha.7"));
    EXPECT_FALSE(vrsn::semver("1.2.3-1456.123") < vrsn::semver("1.2.3-1456.123"));
    EXPECT_FALSE(vrsn::semver("1.2.3--lol") < vrsn::semver("1.2.3-1456"));
    EXPECT_FALSE(vrsn::semver("1.2.3-alpha.gamma") < vrsn::semver("1.2.3-alpha.beta"));
    EXPECT_FALSE(vrsn::semver("1.2.3-alpha.beta") < vrsn::semver("1.2.3-alpha"));
    EXPECT_FALSE(vrsn::semver("1.2.3-alpha.7") < vrsn::semver("1.2.3-alpha.6"));
    EXPECT_FALSE(vrsn::semver("1.2.3") < vrsn::semver("1.2.3-alpha.6"));
}

TEST(semantic_version_tests, operator_le__normal__no_exception)
{
    ASSERT_TRUE(vrsn::semver("1.2.3") <= vrsn::semver("1.2.3"));
    ASSERT_TRUE(vrsn::semver("1.2.3") <= vrsn::semver("1.2.4"));
    ASSERT_TRUE(vrsn::semver("1.2.3-alpha.1") <= vrsn::semver("1.2.3-alpha.2"));
    ASSERT_TRUE(vrsn::semver("1.2.3-1.4") <= vrsn::semver("1.2.3-alpha.2"));
    ASSERT_TRUE(vrsn::semver("1.2.3-alpha.beta.4") <= vrsn::semver("1.2.3-alpha.gamma.2"));
    ASSERT_TRUE(vrsn::semver("1.2.3-1456") <= vrsn::semver("1.2.3--lol"));
    ASSERT_TRUE(vrsn::semver("1.2.3-1456") <= vrsn::semver("1.2.3-1456.123"));
}

TEST(semantic_version_tests, operator_gt__normal__no_exception)
{
    ASSERT_TRUE(vrsn::semver("1.2.3--lol") > vrsn::semver("1.2.3-1456"));
    ASSERT_TRUE(vrsn::semver("1.2.3-alpha.gamma") > vrsn::semver("1.2.3-alpha.beta"));
    ASSERT_TRUE(vrsn::semver("1.2.3-alpha.beta") > vrsn::semver("1.2.3-alpha"));
    ASSERT_TRUE(vrsn::semver("1.2.3-alpha.7") > vrsn::semver("1.2.3-alpha.6"));
    ASSERT_TRUE(vrsn::semver("1.2.3") > vrsn::semver("1.2.3-alpha.6"));

    ASSERT_FALSE(vrsn::semver("1.2.3-1456.123") > vrsn::semver("1.2.3-1456.123"));
    ASSERT_FALSE(vrsn::semver("1.2.3") > vrsn::semver("1.2.4"));
    ASSERT_FALSE(vrsn::semver("1.2.3-alpha.1") > vrsn::semver("1.2.3-alpha.2"));
    ASSERT_FALSE(vrsn::semver("1.2.3-1.4") > vrsn::semver("1.2.3-alpha.2"));
    ASSERT_FALSE(vrsn::semver("1.2.3-alpha.beta.4") > vrsn::semver("1.2.3-alpha.gamma.2"));
    ASSERT_FALSE(vrsn::semver("1.2.3-1456") > vrsn::semver("1.2.3--lol"));
    ASSERT_FALSE(vrsn::semver("1.2.3-1456") > vrsn::semver("1.2.3-1456.123"));
}

TEST(semantic_version_tests, operator_ge__normal__no_exception)
{
    ASSERT_TRUE(vrsn::semver("1.2.3--lol") >= vrsn::semver("1.2.3-1456"));
    ASSERT_TRUE(vrsn::semver("1.2.3-alpha.gamma") >= vrsn::semver("1.2.3-alpha.beta"));
    ASSERT_TRUE(vrsn::semver("1.2.3-alpha.beta") >= vrsn::semver("1.2.3-alpha"));
    ASSERT_TRUE(vrsn::semver("1.2.3-alpha.7") >= vrsn::semver("1.2.3-alpha.6"));
    ASSERT_TRUE(vrsn::semver("1.2.3") >= vrsn::semver("1.2.3-alpha.6"));
}

TEST(semantic_version_tests, constexpr__valid_args__no_compile_error)
{
    static constexpr vrsn::semver version_1(0, 1, 2, "0.0", "specific-build");
    static_assert(version_1.major() == 0);
    static_assert(version_1.minor() == 1);
    static_assert(version_1.patch() == 2);
    static_assert(version_1.pre_release() == "0.0");
    static_assert(version_1.build_metadata() == "specific-build");

    static constexpr vrsn::semver version_2("98.7.66-0.0+specific-build");
    static_assert(version_2.major() == 98);
    static_assert(version_2.minor() == 7);
    static_assert(version_2.patch() == 66);
    static_assert(version_2.pre_release() == "0.0");
    static_assert(version_2.build_metadata() == "specific-build");

    static_assert(version_1 != version_2);
    static_assert(version_1 < version_2);
}

TEST(semantic_version_tests, std_format_semver__x_y_z_pr_bm__no_exception)
{
    const vrsn::semver version(1, 2, 3, "alpha.1", "specific-build");
    const std::string version_str = std::format("{}", version);
    ASSERT_EQ(version_str, "1.2.3-alpha.1+specific-build");
}

TEST(semantic_version_tests, std_format_semver__x_y_z_pr__no_exception)
{
    const vrsn::semver version(1, 2, 3, "alpha.1");
    const std::string version_str = std::format("{}", version);
    ASSERT_EQ(version_str, "1.2.3-alpha.1");
}

TEST(semantic_version_tests, std_format_semver__x_y_z_bm__no_exception)
{
    const vrsn::semver version(1, 2, 3, "", "specific-build");
    const std::string version_str = std::format("{}", version);
    ASSERT_EQ(version_str, "1.2.3+specific-build");
}

TEST(semantic_version_tests, std_format_semver_core__x_y_z_pr_bm__no_exception)
{
    const vrsn::semver version(1, 2, 3, "alpha.1", "specific-build");
    const std::string version_str = std::format("{}", version.core());
    ASSERT_EQ(version_str, "1.2.3");
}

TEST(semantic_version_tests, std_format_semver__x_y_z_pr_bm__ctx__no_exception)
{
    const vrsn::semver version(1, 2, 3, "alpha.1", "specific-build");
    std::string version_str = std::format("{:c}", version);
    ASSERT_EQ(version_str, "1.2.3");
    version_str = std::format("{:c-p}", version);
    ASSERT_EQ(version_str, "1.2.3-alpha.1");
    version_str = std::format("{:c+b}", version);
    ASSERT_EQ(version_str, "1.2.3+specific-build");
    version_str = std::format("{:c-p+b}", version);
    ASSERT_EQ(version_str, "1.2.3-alpha.1+specific-build");
}
