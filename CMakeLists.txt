# set the minimum version of cmake to be compatible with
cmake_minimum_required(VERSION 3.15)

# set project name
project("OpenGL_cube")

# NOTE: use vcpkg on windows and specify -DCMAKE_TOOLCHAIN_FILE=E:\vcpkg\vcpkg\scripts\buildsystems\vcpkg.cmake to cmake command
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# get source files
file(GLOB SRCFILES CONFIGURE_DEPENDS "src/*.cpp")
# add the main executable as our target
add_executable("${PROJECT_NAME}" "${SRCFILES}")
set_property(TARGET "${PROJECT_NAME}" PROPERTY CXX_STANDARD 11)

target_link_libraries(
    "${PROJECT_NAME}" 
    PRIVATE 
    glad::glad
    glfw
    glm::glm
)

add_custom_command(
    TARGET "${PROJECT_NAME}" 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_LIST_DIR}/copied_to_bin" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)