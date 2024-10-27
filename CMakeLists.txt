project(webb)

add_subdirectory(src)

add_executable(webb main.cpp)
target_link_libraries(webb PUBLIC server)
target_link_libraries(webb PUBLIC http)