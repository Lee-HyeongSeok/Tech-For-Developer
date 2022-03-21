set(
    SRC_FILES1 ServerSocket.cpp SocketBase.cpp FdManager.cpp MulticastManager.cpp ClientRoomManager.cpp
)

set(
    SRC_FILES2 ClientSocket.cpp SocketBase.cpp FdManager.cpp MulticastManager.cpp
)

add_library(serverLib STATIC ${SRC_FILES1})
add_library(clientLib STATIC ${SRC_FILES2})

message("lib/CMakeLists.txt, cmake_source_dir : " ${CMAKE_SOURCE_DIR})
target_include_directories(serverLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(clientLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_features(serverLib PRIVATE cxx_std_17)
target_compile_features(clientLib PRIVATE cxx_std_17)

