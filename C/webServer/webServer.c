/*
 *
 * A simple web server
 *
 * ./server port_no
 *
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/socket.h>
 #include <sys/types.h>
 #include <netinet/in.h>
 #include <error.h>
 #include <string.h>
 #include <unistd.h>
 #include <arpa/inet.h>

#define ERROR -1
#define MAX_DATA 40000

 int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sockaddr_len = sizeof(client_addr);
    int fd_server, fd_client;
    int data_len;
    int fdImg;
    int on = 1;
    long readVal;
    int addrLen = sizeof(server_addr);
    char *hello = "HTTP/1.1 200 Document Follows\r\nContent-Type: text/plain,text/html,image/png,image/gif,image/jpg,text/css,application/javascript\r\nContent-Length: 12\r\n\r\nHello world!";

    if((fd_server = socket(AF_INET,SOCK_STREAM,0)) == ERROR) {
        perror("Server socket: ");
        close(fd_server);
        exit(ERROR); }

    setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(fd_server,(struct sockaddr *)&server_addr,sizeof(server_addr)) == ERROR) {
        perror("Bind: ");
        exit(ERROR); }

    if(listen(fd_server,2) == ERROR) {
        perror("Listen: ");
        close(fd_server);
        exit(ERROR); }

    while(1) {
        char data[MAX_DATA] = {0};
        printf("\n~~~~~~~~~~~~~~ Waiting for new connection ~~~~~~~~~~~~~~~~~~\n\n");
        if((fd_client = accept(fd_server,(struct sockaddr*)&client_addr,(socklen_t*)&addrLen)) == ERROR) {
            perror("Accept: ");
            continue; }
        printf("Connection to client established\n");

        readVal = read(fd_client, data, MAX_DATA);
        printf("%s\n",data);

        write(fd_client, hello, strlen(hello));
        printf("------------------Hello message sent-------------------\n");
        printf("server disconnected\n");
        close(fd_client); }

    return 0;
    }
