# CMake entry point
cmake_minimum_required (VERSION 3.5)

project (LearnOpenGL)

set (CMAKE_CXX_STANDARD 11)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# External libraries.
find_package (OpenGL REQUIRED)

find_package (GLEW REQUIRED)
set(GLEW_LIBRARY GLEW::GLEW)

find_package (GLFW3 REQUIRED)

find_package (absl REQUIRED)
set(ABSL_LIBRARY absl::status)

find_package (glog 0.5.0 REQUIRED)
set(GLOG_LIBRARY glog::glog)

set (INCLUDE_DIRS
     . ${OPENGL_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})

set (EXTERNAL_LIBS
     ${GLFW3_LIBRARY} ${OPENGL_LIBRARIES} ${ABSL_LIBRARY} ${GLOG_LIBRARY} ${GLEW_LIBRARY})

include_directories (${INCLUDE_DIRS})

# Renderer libraries.
file(GLOB renderer_srcs "renderer/*.cc")
add_library(renderer SHARED ${renderer_srcs})
target_include_directories(renderer PRIVATE ./)
target_link_libraries(renderer ${EXTERNAL_LIBS})

# 01_create_window binary.
set(BINARY 01_create_window)
add_executable(${BINARY} ./samples/${BINARY}/main.cc)
target_link_libraries(${BINARY} ${EXTERNAL_LIBS} renderer)
