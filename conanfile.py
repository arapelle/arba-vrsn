import os, re

from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import load, copy, rmdir

required_conan_version = ">=2.2.0"

class ArbaVrsnRecipe(ConanFile):
    project_namespace = "arba"
    project_base_name = "vrsn"
    name = f"{project_namespace}-{project_base_name}"
    package_type = "header-library"

    # Optional metadata
    description = "A C++ library providing version classes."
    url = "https://github.com/arapelle/arba-vrsn"
    homepage = "https://github.com/arapelle/arba-vrsn"
    topics = ("version", "semver", "semantic-version")
    license = "MIT"
    author = "Aymeric Pellé"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "test": [True, False]
    }
    default_options = {
        "test": False
    }

    # Build
    win_bash = os.environ.get('MSYSTEM', None) is not None
    no_copy_source = True

    # Sources
    exports_sources = "LICENSE.md", "CMakeLists.txt", "test/*", "include/*", "external/*", "cmake/*"

    # Other
    implements = ["auto_header_only"]

    def set_version(self):
        cmakelist_content = load(self, os.path.join(self.recipe_folder, "CMakeLists.txt"))
        version_regex = r"""set_project_semantic_version\( *"?([0-9]+\.[0-9]+\.[0-9]+).*"""
        self.version = re.search(version_regex, cmakelist_content).group(1)

    def layout(self):
        cmake_layout(self)

    def validate(self):
        check_min_cppstd(self, 20)

    def build_requirements(self):
        self.test_requires("gtest/[^1.14]")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        if self.options.test:
            upper_name = f"{self.project_namespace}_{self.project_base_name}".upper()
            tc.variables[f"BUILD_{upper_name}_TESTS"] = "TRUE"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        if self.options.test:
            cmake.build()
            cmake.ctest(cli_args=["--progress", "--output-on-failure"])

    def package(self):
        copy(self, "LICENSE.md", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()
        rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.set_property("cmake_target_name", self.name.replace('-', '::'))
