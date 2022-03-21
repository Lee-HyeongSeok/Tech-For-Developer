set(
    SRC_FILES1 simple_server_main.cpp
)

set(
    SRC_FILES2 simple_client_main.cpp
)

add_executable(server ${SRC_FILES1})
target_link_libraries(server PUBLIC serverLib)

add_executable(client ${SRC_FILES2})
target_link_libraries(client PUBLIC clientLib)