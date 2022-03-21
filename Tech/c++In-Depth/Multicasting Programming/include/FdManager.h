#ifndef FDMANAGER_H
#define FDMANAGER_H

#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h>

class FdManager{
public:
    FdManager(int);
    FdManager(int, int);
    ~FdManager(){}

    int do_select();
    int is_set(int&);
    void set_reads(int);
    void delete_reads(int);
    int get_max_fd() const;
private:
    fd_set reads, cp_reads;
    int fd_max, fd_num;
};

#endif