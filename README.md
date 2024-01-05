# Concept #

A C++ library providing version classes.
- tri version: 0.1.0
- semantic_version: 0.1.0, 0.1.0-alpha.1+metadata (https://semver.org/spec/v2.0.0.html)

# Install #
## Requirements ##

Binaries:

- A C++20 compiler (ex: g++-13)
- CMake 3.26 or later

Testing Libraries (optional):

- [Google Test](https://github.com/google/googletest) 1.13 or later (optional)

## Clone

```
git clone https://github.com/arapelle/arba-vrsn --recurse-submodules
```

## Quick Install ##
There is a cmake script at the root of the project which builds the library in *Release* mode and install it (default options are used).
```
cd /path/to/arba-vrsn
cmake -P cmake/scripts/quick_install.cmake
```
Use the following to quickly install a different mode.
```
cmake -P cmake/scripts/quick_install.cmake -- TESTS BUILD Debug DIR /tmp/local
```

## Uninstall ##
There is a uninstall cmake script created during installation. You can use it to uninstall properly this library.
```
cd /path/to/installed-arba-vrsn/
cmake -P uninstall.cmake
```

# How to use
## Example - Use a semantic version
```c++
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
```

## Example - Using *arba-core* in a CMake project
See *basic_cmake_project* in example, and more specifically the *CMakeLists.txt* to see how to use *arba-vrsn* in your CMake projects.

# License

[MIT License](./LICENSE.md) © arba-vrsn
