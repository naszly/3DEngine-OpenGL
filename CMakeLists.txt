cmake_minimum_required(VERSION 3.19)
project(3DEngine-OpenGL)

include(cmake/CPM.cmake)
include(cmake/ImGui.cmake)

add_subdirectory(engine)
add_subdirectory(application)

add_custom_target(
        copy_resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:application>/resources
        VERBATIM
)

add_dependencies(application copy_resources)
