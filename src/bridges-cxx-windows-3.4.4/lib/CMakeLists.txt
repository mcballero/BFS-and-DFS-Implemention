add_library(l STATIC my_lib.cpp my_lib.h)

target_include_directories(my_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
