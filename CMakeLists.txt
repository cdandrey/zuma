cmake_minimum_required(VERSION 3.3)

set (this Zuma)

project(${this} VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

include_directories(SYSTEM
	"${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/"
)

add_subdirectory("3rdparty")
add_subdirectory("src")

add_executable(${this}
    src/main.cpp
)

target_link_libraries(${this}
    ZumaLib
)

target_include_directories(${this}
	PRIVATE
	"${ZUMA_3RDPARTY_INCLUDE_DIRECTORIES}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
)
