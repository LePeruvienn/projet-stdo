file(GLOB TEST_FILES CONFIGURE_DEPENDS "*.c")

find_library(CUNIT_LIB cunit REQUIRED)

foreach(TEST_FILE ${TEST_FILES})
	get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
	add_executable(${TEST_NAME}.tst ${TEST_FILE})
	target_link_libraries(${TEST_NAME}.tst LSP core cunit)
endforeach()
