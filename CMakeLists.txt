cmake_minimum_required (VERSION 3.20.2)

# Enable hot reloading for the MSVC compiler if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (ToDoListConsoleApplication VERSION 1.2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(todolist main.cpp)

add_subdirectory (ToDoList)
add_subdirectory (ToDoListTest)

target_link_libraries(todolist ToDoList)

if (NOT googletest) # is googletest defined if already built?
	include(FetchContent)
	FetchContent_Declare(
		googletest
		# Specify the commit you depend on and update it regularly.
		URL https://github.com/google/googletest/archive/refs/heads/master.zip
	)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)
endif()

# Add a custom command to delete specification.txt if it exists
add_custom_command(
    TARGET todolist
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/specification.txt
    COMMENT "Removing specification.txt if it exists"
)

install(TARGETS todolist DESTINATION bin)

include(CPack)
set(CPACK_PACKAGE_NAME "ToDoListConsoleApplication")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple ToDo list application for the terminal.")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

# Detect platform and set CPack generator accordingly
if (WIN32)
    set(CPACK_GENERATOR "NSIS")
else ()
    set(CPACK_GENERATOR "TGZ")
endif ()
