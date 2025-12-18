cmake_minimum_required(VERSION 3.15)

get_filename_component(LIB_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${LIB_NAME} C)

file(GLOB LIB_SRC CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_library(${LIB_NAME} STATIC
        ${LIB_SRC}
)

target_include_directories(${LIB_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
