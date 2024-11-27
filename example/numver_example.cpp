#include <arba/vrsn/numver.hpp>
#include <arba/vrsn/version.hpp>
#include <cstdlib>
#include <iostream>

int main()
{
    vrsn::numver ver(0, 1, 0);
    std::cout << std::format("version-{}", ver) << std::endl;
    return EXIT_SUCCESS;
}
