# The variable with the library name
set(LIB_NAME "tm1637")

file(GLOB ${LIB_NAME}_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB ${LIB_NAME}_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

# Creating a static library
add_library(lib${LIB_NAME} STATIC ${${LIB_NAME}_SOURCES} ${${LIB_NAME}_HEADERS})
target_include_directories(lib${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#  If the library uses HAL or CMSIS
target_link_libraries(lib${LIB_NAME} PUBLIC stm32cubemx)
