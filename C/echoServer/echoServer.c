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
 #include <strings.h>
 #include <unistd.h>
 #include <arpa/inet.h>

#define ERROR -1
#define MAX_DATA 1024

 int main(int argc, char *argv[]) {
    struct sockaddr_in server;
    struct sockaddr_in client;
    int sockaddr_len = sizeof(struct sockaddr_in);
    int data_len;
    char data[MAX_DATA];
    int sockfd;
    int new;

    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == ERROR) {
        perror("Server socket: ");
        exit(ERROR); }

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, 8);

    if((bind(sockfd,(struct sockaddr *)&server,sockaddr_len)) == ERROR) {
        perror("bind: ");
        exit(ERROR); }

    if((listen(sockfd,2)) == ERROR) {
        perror("listen: ");
        exit(ERROR); }

    while(1) {
        printf("\n~~~~~~~~~~~~~~ Waiting for new connection ~~~~~~~~~~~~~~~~~~\n\n");
        if((new = accept(sockfd,(struct sockaddr*)&client,&sockaddr_len)) == ERROR) {
            perror("accept: ");
            exit(ERROR); }

        printf("New Client connected from port no %d and IP %s\n", ntohs(client.sin_port),
              inet_ntoa(client.sin_addr));


        data_len = 1;

        while(data_len) {
            bzero(data, MAX_DATA);
            data_len = recv(new, data, MAX_DATA, 0);
            printf("Received message from client: %s\n", data);

            if(data_len) {
                send(new, data, data_len, 0);
                data[data_len] = '\0';
                printf("Sent message to client: %s\n", data); }}

        printf("\nClient disconnected\n");
        close(new); }

    }
