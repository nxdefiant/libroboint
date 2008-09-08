include_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(example example.c)

target_link_libraries(example ft)

