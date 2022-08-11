cmake_minimum_required(VERSION 3.3)

add_library(Expected
    STATIC 
    expected.h
)

target_include_directories(Expected
	PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(Expected ZumaLib)