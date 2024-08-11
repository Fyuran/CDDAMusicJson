# CMakeList.txt : CMake project for CDDAMusicJson, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CDDAMusicJson WIN32 "CDDAMusicJson.cpp")
target_compile_features(CDDAMusicJson PRIVATE cxx_std_20)
target_include_directories(CDDAMusicJson PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(CDDAMusicJson PRIVATE CDDAFileFncs)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()
target_link_libraries(CDDAMusicJson PRIVATE ${wxWidgets_LIBRARIES})

add_custom_command(TARGET CDDAMusicJson POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        $<TARGET_FILE:CDDAFileFncs>      # <--this is in-file
        $<TARGET_FILE_DIR:CDDAMusicJson>)                 # <--this is out-file path