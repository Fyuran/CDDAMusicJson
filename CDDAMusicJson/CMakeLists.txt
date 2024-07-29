# CMakeList.txt : CMake project for CDDAMusicJson, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CDDAMusicJson "CDDAMusicJson.cpp")
target_compile_features(CDDAMusicJson PRIVATE cxx_std_20)
target_include_directories(CDDAMusicJson PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(CDDAMusicJson PRIVATE CDDAFileFncs)

add_custom_command(TARGET CDDAMusicJson POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        ${CMAKE_BINARY_DIR}/CDDAFileFncs/CDDAFileFncs.dll      # <--this is in-file
        ${CMAKE_CURRENT_BINARY_DIR})                 # <--this is out-file path