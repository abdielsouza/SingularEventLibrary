cmake_minimum_required(VERSION 3.5)
project(SingularEventHandler VERSION 0.1.0)

add_library(singular INTERFACE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
target_include_directories(
    singular INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

enable_testing()

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(singular::singular ALIAS singular)

set(MAIN_PROJECT OFF)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif()

if (POLICY CMP0077)
	# Allow CMake 3.13+ to override options when using add_subdirectory/FetchContent.
	cmake_policy(SET CMP0077 NEW)
endif (POLICY CMP0077)

option(SINGULAR_INSTALL "Enable installation" ${MAIN_PROJECT})

if (SINGULAR_INSTALL)
    # Install the library
	install(
		TARGETS singular
		EXPORT singularTargets
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)

	# Install the headers
	install(
		DIRECTORY include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)

	# (Generate and) install the target import file
	install(
		EXPORT singularTargets
		NAMESPACE singular::
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/singular
	)

	# Generate the package version file
	include(CMakePackageConfigHelpers)
	write_basic_package_version_file(
		${CMAKE_CURRENT_BINARY_DIR}/singularConfigVersion.cmake
		VERSION ${PROJECT_VERSION}
		COMPATIBILITY AnyNewerVersion
	)

	# Generate the package configuration file, that allows other
	# CMake projects to find the library with find_package()
	configure_package_config_file(
		cmake/singularConfig.cmake.in
		${CMAKE_CURRENT_BINARY_DIR}/singularConfig.cmake
		INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/singular
	)

	# Install the package version and configuration files
	install(
		FILES
		${CMAKE_CURRENT_BINARY_DIR}/singularConfig.cmake
		${CMAKE_CURRENT_BINARY_DIR}/singularConfigVersion.cmake
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/singular
	)

	# Install readme and license
	install(
		FILES
		readme.md
		license
		DESTINATION ${CMAKE_INSTALL_DATADIR}/singular
	)
endif()

add_executable(
	singular_test
	tests/singular_test.cpp
)

target_include_directories(
    singular_test PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(singular_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(singular_test)