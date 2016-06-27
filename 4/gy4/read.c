#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    int fd;
    char buf[256];
    int len;


    if(argc < 2) {
        printf("usage: %s filename\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);

    if(fd < 0){
        perror("open");
        return 1;
    }

    // len = read(fd, buf, sizeof(buf)-1 ); // azert -1, hogy beferjen /n a vegere
    // if(len < 0){
    //     perror("read");
    //     return 1;
    // }
    //
    // buf[len] = 0;
    // printf("%s\n", buf);

    len = read(fd, buf, sizeof(buf)-1 ); // azert -1, hogy beferjen /n a vegere
    if(len < 0){
        perror("read");
        return 1;
    }

    if(write(STDOUT_FILENO, buf, len ) <0 ){ // len az ertelmes tartalom merete kell legyen, nem a buffer merete
        perror("write");
        return 1;
    }

    close(fd);

    return 0;
}
