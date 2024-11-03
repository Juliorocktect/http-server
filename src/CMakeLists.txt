add_library(http ./http/HTTP.h ./http/HTTP.cpp ./http/Response.cpp)

add_library(server ./server/Server.h ./server/Server.cpp)

add_library(handler ./httpHandler/Handler.h ./httpHandler/Handler.cpp)
add_subdirectory(controller)