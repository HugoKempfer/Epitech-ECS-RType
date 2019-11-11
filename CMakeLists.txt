project(RType)
#cmake_minimum_required(VERSION 2.8.12)
cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 17)
add_definitions("-fPIC")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_INCLUDE_PATH})
include_directories("./include")

file(GLOB_RECURSE SERVER
		"src/server/*.cpp",
		)

file(GLOB_RECURSE CLIENT
		"src/client/*.cpp",
		)

file(GLOB_RECURSE ENGINE
		"src/engine/*.cpp",
		)

add_library(engine STATIC ${ENGINE})

add_executable(r-type_server ${SERVER})
add_executable(r-type_client ${CLIENT})

target_link_libraries(r-type_server ${CONAN_LIBS} engine)
target_link_libraries(r-type_client ${CONAN_LIBS} engine)
