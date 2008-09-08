include_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(ftuploader ftuploader.c)

target_link_libraries(ftuploader ft)

INSTALL_TARGETS(/bin ftuploader)

