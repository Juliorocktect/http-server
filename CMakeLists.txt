cmake_minimum_required(VERSION 3.11)
project(webb LANGUAGES CXX)
include_directories(webb PUBLIC "./include")
add_subdirectory(src)
include_directories(src/)
link_directories(src/)
add_executable(webb main.cpp)
target_link_libraries(webb PUBLIC -lpqxx -lpq http )
target_link_libraries(webb PUBLIC handler)
target_link_libraries(webb PUBLIC server)
target_link_libraries(webb PUBLIC controller)
target_link_libraries(webb PUBLIC repo)






