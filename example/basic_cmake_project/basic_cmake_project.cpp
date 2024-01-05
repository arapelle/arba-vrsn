#include <arba/vrsn/semantic_version.hpp>
#include <arba/vrsn/version.hpp>
#include <cstdlib>
#include <iostream>

int main()
{
    vrsn::semantic_version ver("0.1.0-dev+metadata");
    std::cout << std::format("version-{}", ver) << std::endl;
    return EXIT_SUCCESS;
}
