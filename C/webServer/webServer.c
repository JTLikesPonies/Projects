/*
 *
 * A simple echo server
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

 int main(int argc, char **argv) {
    struct sockaddr_in server;
    struct sockaddr_in client;
    int sockaddr_len = sizeof(struct sockaddr_in);
    int data_len;
    //char data[MAX_DATA];
    int server_fd;
    int new;
    long readVal;
    char *hello = "Hello from server";

    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) == ERROR) {
        perror("Server socket: ");
        exit(ERROR); }

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_fd,(struct sockaddr *) &server,sizeof(server)) == ERROR) {
        perror("bind: ");
        exit(ERROR); }

    if(listen(server_fd,2) == ERROR) {
        perror("listen: ");
        exit(ERROR); }

    while(1) {
        char data[MAX_DATA] = {0};
        printf("\n~~~~~~~~~~~~~~ Waiting for new connection ~~~~~~~~~~~~~~~~~~\n\n");
        if(new = accept(server_fd,(struct sockaddr*) &client,&sockaddr_len) == ERROR) {
            perror("accept: ");
            exit(ERROR); }

        printf("New Client connected from port no %d and IP %s\n", ntohs(client.sin_port),
              inet_ntoa(client.sin_addr));

        readVal = read(new, data, MAX_DATA);
        printf("%s\n",data);

        write(new, hello, strlen(hello));
        printf("------------------Hello message sent-------------------\n");
        
        printf("Client disconnected\n");
        close(new); }

    }
