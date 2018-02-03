include_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(ftuploader ftuploader.c)

target_link_libraries(ftuploader roboint)

INSTALL_TARGETS(/bin ftuploader)
