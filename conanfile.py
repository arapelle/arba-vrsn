import os, re

from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import load, copy, rmdir

class ArbaVrsnRecipe(ConanFile):
    package_type = "header-library"
    description = "A C++ library providing version classes."
    url = "https://github.com/arapelle/arba-vrsn"
    homepage = "https://github.com/arapelle/arba-vrsn"
    topics = ("version", "semver", "semantic-version")
    license = "MIT"
    author = "Aymeric Pellé"

    win_bash = os.environ.get('MSYSTEM', None) is not None
    exports_sources = "LICENSE.md", "CMakeLists.txt", "test/*", "include/*", "external/*", "cmake/*"
    no_copy_source = True

    settings = "os", "compiler", "build_type", "arch"
    options = {
        "test": [True, False]
    }
    default_options = {
        "test": False
    }

    implements = ["auto_header_only"]

    def set_name(self):
        self.name = f"{self.project_namespace()}-{self.project_base_name()}".lower()

    def set_version(self):
        version_regex = r"""set_project_semantic_version\( *"?([0-9]+\.[0-9]+\.[0-9]+).*"""
        self.version = re.search(version_regex, self.cmakelist_content()).group(1)

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
            upper_name = f"{self.project_namespace()}_{self.project_base_name()}".upper()
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
        self.cpp_info.libs = [self.name]
        self.cpp_info.set_property("cmake_target_name", self.name.replace('-', '::'))

    def cmakelist_content(self):
        if not hasattr(self, "__cmakelist_content"):
            if self.source_folder is None:
                folder = self.recipe_folder
            else:
                assert self.source_folder is not None
                folder = self.source_folder
            self.__cmakelist_content = load(self, os.path.join(folder, "CMakeLists.txt"))
        return self.__cmakelist_content
    
    def project_namespace(self):
        if not hasattr(self, "__project_namespace"):
            content = self.cmakelist_content()
            project_namespace_regex = r"""set_project_name\(NAMESPACE *"?([a-zA-Z0-9_]+).*"""
            self.__project_namespace = re.search(project_namespace_regex, content).group(1)
        return self.__project_namespace

    def project_base_name(self):
        if not hasattr(self, "__project_base_name"):
            content = self.cmakelist_content()
            project_base_name = r"""set_project_name\(.*BASE_NAME *"?([a-zA-Z0-9_]+).*"""
            self.__project_base_name = re.search(project_base_name, content).group(1)
        return self.__project_base_name
