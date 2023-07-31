cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION $ENV{RUN_NUMBER} CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(print_ip VERSION ${PROJECT_VESRION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(print_ip_cli main.cpp)
add_library(print_ip print_ip_concepts.cpp print_ip_without_concepts.cpp)
add_executable(tests tests.cpp)

set_target_properties(print_ip_cli print_ip tests PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        )
target_include_directories(print_ip
        PRIVATE "${CMAKE_BINARY_DIR}"
        )
set_target_properties(tests PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )

target_link_libraries(print_ip_cli PRIVATE
        print_ip
        )
target_link_libraries(tests
        ${Boost_LIBRARIES}
        print_ip
        )

if (MSVC)
    target_compile_options(print_ip_cli PRIVATE
            /W4
            )
    target_compile_options(print_ip PRIVATE
            /W4
            )
    target_compile_options(tests PRIVATE
            /W4
            )
else ()
    target_compile_options(print_ip_cli PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
    target_compile_options(print_ip PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
    target_compile_options(tests PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()



install(TARGETS print_ip_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(tests GTest::gtest_main print_ip)

include(GoogleTest)
gtest_discover_tests(tests)