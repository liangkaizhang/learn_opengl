set (LIB_NAME window)
file (GLOB SOURCE_FILES "*.cc")
add_library (${LIB_NAME} SHARED ${SOURCE_FILES})
target_link_libraries (${LIB_NAME} ${LIBS})