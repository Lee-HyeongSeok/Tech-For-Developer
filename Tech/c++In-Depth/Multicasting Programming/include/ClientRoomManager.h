#ifndef CLIENTROOMMANAGER_H
#define CLIENTROOMMANAGER_H

#define MAX_CLIENT_FD 100

enum Port{
    Room1 = 4321,
    Room2 = 4322
};

class ClientRoomManager{
public:
    ClientRoomManager();
    ~ClientRoomManager();

// client_fd는 변경되면 안됨
    void set_status_false(const int);
    void set_status_true(const int);
    void set_client_room_status(const int, int);
    bool const get_client_status(const int);
    int const get_client_room_port(const int); // int에 해당하는 FD의 room port를 얻어온다.
private:
    bool status[MAX_CLIENT_FD];
    int client_room_status[MAX_CLIENT_FD];

};

#endif