set (LIB_NAME gl)
file (GLOB SOURCE_FILES "*.cc")
add_library (${LIB_NAME} SHARED ${SOURCE_FILES})
target_link_libraries (${LIB_NAME} ${LIBS})

# set (LIB_NAME gl)
# add_library (${LIB_NAME} SHARED program.cc shader.cc buffer.cc vertex_arra)
# target_link_libraries (${LIB_NAME} ${LIBS})