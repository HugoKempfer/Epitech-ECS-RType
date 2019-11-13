project(RType)

cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 20)
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


add_library(engine STATIC ${ENGINE})

add_executable(r-type_server ${SERVER})
add_executable(r-type_client ${CLIENT})

target_link_libraries(r-type_server ${CONAN_LIBS} engine)
target_link_libraries(r-type_client ${CONAN_LIBS} engine)
