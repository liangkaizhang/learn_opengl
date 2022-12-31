# CMake entry point
cmake_minimum_required (VERSION 3.5)

project (LearnOpenGL)

set (CMAKE_CXX_STANDARD 11)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
     "${CMAKE_SOURCE_DIR}/cmake")

# External libraries.
find_package (OpenGL REQUIRED)

find_package (GLEW REQUIRED)
set (GLEW_LIBRARY GLEW::GLEW)

find_package (GLFW3 REQUIRED)

find_package (absl REQUIRED)
set (ABSL_LIBRARY
     absl::status absl::statusor absl::flat_hash_map absl::strings absl::random_random)

find_package (glog 0.5.0 REQUIRED)
set (GLOG_LIBRARY glog::glog)

find_package(OpenCV REQUIRED)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
set (Eigen3_LIBRARY Eigen3::Eigen)

set(INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/src
    ${OPENGL_INCLUDE_DIR}
    ${GLFW3_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR})

set(LIBS
     ${GLFW3_LIBRARY}
     ${OPENGL_LIBRARIES}
     ${ABSL_LIBRARY}
     ${GLOG_LIBRARY}
     ${GLEW_LIBRARY}
     ${OpenCV_LIBS}
     ${Eigen3_LIBRARY})

include_directories (${INCLUDE_DIRS})

add_subdirectory (src)

# set(EXTRA_LIBS ${EXTRA_LIBS} renderer window)
set(EXTRA_LIBS ${EXTRA_LIBS} window gl geometry)

# 01_create_window binary.
set (BINARY 01_create_window)
add_executable( ${BINARY} ./samples/${BINARY}/main.cc)
target_link_libraries (${BINARY} PUBLIC ${LIBS} ${EXTRA_LIBS})

# # 02_create_shader binary.
# set (BINARY 02_create_shader)
# add_executable( ${BINARY} ./samples/${BINARY}/main.cc)
# target_link_libraries (${BINARY} PUBLIC ${LIBS} ${EXTRA_LIBS})

# 03_render_texture binary.
set (BINARY 03_render_texture)
add_executable( ${BINARY} ./samples/${BINARY}/main.cc)
target_link_libraries (${BINARY} PUBLIC ${LIBS} ${EXTRA_LIBS})

# 04_render_ar binary.
set (BINARY 04_render_geometry)
add_executable( ${BINARY} ./samples/${BINARY}/main.cc)
target_link_libraries (${BINARY} PUBLIC ${LIBS} ${EXTRA_LIBS})

# 05_frame_buffer binary.
set (BINARY 05_frame_buffer)
add_executable( ${BINARY} ./samples/${BINARY}/main.cc)
target_link_libraries (${BINARY} PUBLIC ${LIBS} ${EXTRA_LIBS})