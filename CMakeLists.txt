cmake_minimum_required(VERSION 3.2)

set (this Zuma)

project(${this} VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("3rdparty")

add_executable(${this}
    src/main.cpp
)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

target_include_directories(${this}
	PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${ZUMA_3RDPARTY_INCLUDE_DIRECTORIES}"
)

target_link_libraries(${this}
    sfml-graphics
    sfml-system
    sfml-window
)