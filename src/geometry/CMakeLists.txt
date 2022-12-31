set (LIB_NAME geometry)

# file (GLOB SOURCE_FILES "*.cc")
# add_library (${LIB_NAME} SHARED ${SOURCE_FILES})
# target_link_libraries (${LIB_NAME} PUBLIC ${LIBS})

add_library (${LIB_NAME} SHARED buffer_geometry.cc camera.cc mesh.cc grid.cc quad.cc)
target_link_libraries (${LIB_NAME} PUBLIC ${LIBS} gl)