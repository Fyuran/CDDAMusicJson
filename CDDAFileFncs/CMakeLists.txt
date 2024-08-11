include(FetchContent)

add_library(CDDAFileFncs SHARED "CDDAFileFncs.cpp")
target_compile_features(CDDAFileFncs PUBLIC cxx_std_20)
target_include_directories(CDDAFileFncs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})
# and for each of your dependent executable/library targets:
target_link_libraries(CDDAFileFncs PUBLIC ${wxWidgets_LIBRARIES})

if(WIN32)
	FetchContent_Declare(json URL https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.zip)
elseif(UNIX)
	FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
endif()

FetchContent_MakeAvailable(json)
target_link_libraries(CDDAFileFncs PUBLIC nlohmann_json::nlohmann_json)