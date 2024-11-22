cmake_minimum_required(VERSION 3.11)
project(webb LANGUAGES CXX)
include_directories(webb PUBLIC "./include")
add_subdirectory(src)

add_executable(webb main.cpp)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
message(STATUS "Fetching JSON...")

FetchContent_MakeAvailable(json)

target_link_libraries(webb PUBLIC server)
target_link_libraries(webb PUBLIC http)
target_link_libraries(webb PUBLIC handler)
target_link_libraries(webb PUBLIC controller)
target_link_libraries(webb PUBLIC nlohmann_json::nlohmann_json)

