project(RType)

enable_testing()

cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 20)
IF(APPLE)
	set(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc/9.2.0_1/bin/g++-9")
ENDIF(APPLE)
add_definitions("-fPIC")
add_definitions("-fconcepts")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_INCLUDE_PATH})
include_directories("./include/")

file(GLOB_RECURSE ENGINE
		"src/engine/*.cpp",
		)

file(GLOB_RECURSE SERVER
		"src/server/*.cpp",
		)

file(GLOB_RECURSE CLIENT
		"src/client/*.cpp",
		)

file(GLOB_RECURSE TEST_ENGINE
		"tests/engine/*.cpp"
		)

add_library(engine STATIC ${ENGINE})

add_executable(r-type_server ${SERVER})
add_executable(r-type_client ${CLIENT})
add_executable(engine_test ${TEST_ENGINE})

target_link_libraries(engine_test engine criterion)
target_link_libraries(r-type_server ${CONAN_LIBS} engine)
target_link_libraries(r-type_client ${CONAN_LIBS} engine)

add_test(world bin/engine_test)
