#include "ClientRoomManager.h"

ClientRoomManager::ClientRoomManager(){

}

ClientRoomManager::~ClientRoomManager(){

}

void ClientRoomManager::set_status_false(const int client_fd){
    status[client_fd] = false;
}
void ClientRoomManager::set_status_true(const int client_fd){
    status[client_fd] = true;
}
void ClientRoomManager::set_client_room_status(const int client_fd, int port){
    (port==1)?(client_room_status[client_fd] = Port::Room1):(client_room_status[client_fd] = Port::Room2);
}
bool const ClientRoomManager::get_client_status(const int client_fd){
    return status[client_fd];
}
int const ClientRoomManager::get_client_room_port(const int client_fd){
    return client_room_status[client_fd];
}