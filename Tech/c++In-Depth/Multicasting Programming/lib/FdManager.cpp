#include "FdManager.h"

FdManager::FdManager(int server_fd){
    FD_ZERO(&reads);
    FD_SET(server_fd, &reads);
    fd_max = server_fd;
}

FdManager::FdManager(int read_fd, int client_fd){
    FD_ZERO(&reads);
    FD_SET(read_fd, &reads);
    FD_SET(client_fd, &reads);
    fd_max = client_fd;
}

int FdManager::do_select(){
    cp_reads = reads;

    return select(fd_max+1, &cp_reads, 0, 0, 0); // timeout - 0, err - -1
}

int FdManager::is_set(int& current_fd){
    return FD_ISSET(current_fd, &cp_reads); // isn't set - 0, otherwise != 0
}

void FdManager::set_reads(int current_fd){
    FD_SET(current_fd, &reads);
    if(fd_max < current_fd){
        fd_max = current_fd;
    }
}

void FdManager::delete_reads(int current_fd){
    FD_CLR(current_fd, &reads);
}

int FdManager::get_max_fd() const{
    return fd_max;
}