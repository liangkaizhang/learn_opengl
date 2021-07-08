# CMake entry point
cmake_minimum_required (VERSION 3.5)

project (LearnOpenGL)

set (CMAKE_CXX_STANDARD 11)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
     "${CMAKE_SOURCE_DIR}/cmake")

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
     ./src ${OPENGL_INCLUDE_DIR} ${GLFW3_INCLUDE_DIR}
     ${GLEW_INCLUDE_DIR})

set (LIBS
     ${GLFW3_LIBRARY} ${OPENGL_LIBRARIES}
     ${ABSL_LIBRARY} ${GLOG_LIBRARY} ${GLEW_LIBRARY})

include_directories (${INCLUDE_DIRS})

# Window libraries.
file(GLOB window_srcs "src/window/*.cc")
add_library(window SHARED ${window_srcs})
target_link_libraries(window ${LIBS})
list(APPEND LIBS window)

# 01_create_window binary.
set(BINARY 01_create_window)
add_executable(${BINARY}
               ./samples/${BINARY}/main.cc)
target_link_libraries(${BINARY} ${LIBS})