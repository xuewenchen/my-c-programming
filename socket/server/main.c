#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>

#define PORT 1500
#define BACKLOG 5

int main(int argc, char ** argv) {
    // the define of socket
    int svr_fd;  // the first get socket
    int cli_fd;  // the accept get socket
    int sin_size;

    // the define of sockaddr
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    
    // step 1: socket()
    svr_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(svr_fd == -1){
        printf("socket failed:%d\n", errno);
        return -1;
    }

    // set my_addr
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bzero(&(my_addr.sin_zero), 0);

    // step 2: bind()
    if(bind(svr_fd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) < 0) {
        printf("bind error");
        return -1;
    }

    // step 3: listen()
    listen(svr_fd, BACKLOG);
    
    while(1) {
        sin_size = sizeof(struct sockaddr_in);

        // step 4: accept()
        cli_fd = accept(svr_fd, (struct sockaddr*)&their_addr, &sin_size);
        if(cli_fd == -1) {
            printf("fail");
        } else {
            printf("success");

            // step 5: send() 
            send(cli_fd, "hello world\n", 12, 0);
        }
    }

    return 0;
}

