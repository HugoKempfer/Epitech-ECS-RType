project(RType)

enable_testing()

cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 20)

if (APPLE)
	set(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc/9.2.0_1/bin/g++-9")
endif()


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions("-fPIC")
add_definitions("-fconcepts")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_INCLUDE_PATH})
include_directories("./include/")

file(GLOB_RECURSE ENGINE "src/engine/core/*.cpp")

file(GLOB_RECURSE ENGINE_RENDER "src/engine/render/*.cpp")

file(GLOB_RECURSE ENGINE_NETWORK "src/engine/network/*.cpp")

file(GLOB_RECURSE SERVER "src/server/*.cpp")

file(GLOB_RECURSE CLIENT "src/client/*.cpp")

file(GLOB_RECURSE TEST_ENGINE "tests/engine/*.cpp")

file(GLOB_RECURSE TEST_RENDER "tests/render/*.cpp")

add_library(engine STATIC ${ENGINE} ${ENGINE_NETWORK})
add_library(engine_render STATIC ${ENGINE_RENDER})

add_executable(r-type_server ${SERVER})
add_executable(r-type_client ${CLIENT})
add_executable(engine_test ${TEST_ENGINE})
add_executable(render_test ${TEST_RENDER})

target_link_libraries(engine_render engine)
target_link_libraries(r-type_server engine)
target_link_libraries(r-type_client ${CONAN_LIBS} engine engine_render)

target_link_libraries(engine_test engine criterion)
target_link_libraries(render_test ${CONAN_LIBS} engine engine_render criterion)

add_test(engine bin/engine_test)
add_test(render bin/render_test)


if (DEFINED ENV{RTYPE_DEBUG})
		set(CMAKE_BUILD_TYPE Debug)
		add_definitions("-Wall -Wextra -fipa-pure-const
		-Wsuggest-attribute=const")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -g")
endif()
