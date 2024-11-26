import os, re

from conan import ConanFile
from conan.tools.files import load
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class ArbaVrsnRecipe(ConanFile):
    package_type = "header-library"
    win_bash = os.environ.get('MSYSTEM', None) is not None

    # Optional metadata
    license = "MIT"
    author = "Aymeric Pellé"

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "test/*", "include/*", "external/*", "cmake/*"
    no_copy_source = True

    settings = "os", "compiler", "build_type", "arch"
    options = {"test": [True, False]}
    default_options = {"test": False}

    def package_id(self):
        self.info.clear()

    def set_name(self):
        content = load(self, os.path.join(self.recipe_folder, "CMakeLists.txt"))
        project_namespace = re.search(r"""set_project_name\(NAMESPACE *"?([a-zA-Z0-9_]+).*""", content).group(1)
        project_base_name = re.search(r"""set_project_name\(.*BASE_NAME *"?([a-zA-Z0-9_]+).*""", content).group(1)
        self.name = f"{project_namespace}-{project_base_name}".lower()

    def set_version(self):
        content = load(self, os.path.join(self.recipe_folder, "CMakeLists.txt"))
        self.version = re.search(r"""set_project_semantic_version\( *"?([0-9]+\.[0-9]+\.[0-9]+).*""", content).group(1)

    def layout(self):
        cmake_layout(self)

    def build_requirements(self):
        self.test_requires("gtest/[^1.14]")

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        if self.options.test:
            upper_name = self.name.replace('-', '_').upper()
            tc.variables[f"BUILD_{upper_name}_TESTS"] = "TRUE"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        if self.options.test:
            cmake.build()
            cmake.ctest(cli_args=["--progress", "--output-on-failure"])

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.libs = [self.name]
        self.cpp_info.set_property("cmake_target_name", self.name.replace('-', '::'))
