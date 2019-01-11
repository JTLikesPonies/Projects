#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>

#define BYTES 1024
#define MAXCONNECTS 1000

char * ROOT;
int sockfd, clients[MAXCONNECTS];


void startServer(char *port) {
    struct addrinfo hints, *res, *p;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if(getaddrinfo(NULL, port, &hints, &res) != 0) {
        perror("Get address info: ");
        exit(1); }

    for(p = res; p != NULL; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, 0);
        if(sockfd == -1) continue;
        if(bind(sockfd, p->ai_addr, p->ai_addrlen) == 0) break; }
    if(p == NULL) {
        perror("Socket or Bind: ");
        exit(1); }

    freeaddrinfo(res);

    if(listen(sockfd, 1000000) != 0) {
        perror("Listen: ");
        exit(1); }}


void Response(int n) {
    char msgBuff[99999], *requestLine[3], path[99999], data[BYTES];
    int rcvd, fd, b_read;

    memset((void *)msgBuff, (int)'\0', 99999);

    rcvd = recv(clients[n], msgBuff, 99999, 0);

    if(rcvd <= 0) perror("Receive: ");
    else {
        printf("%s", msgBuff);

        requestLine[0] = strtok(msgBuff, " \t\n");
        if(strncmp(requestLine[0], "GET\0", 4) == 0) {
            requestLine[1] = strtok(NULL, " \t");
            requestLine[2] = strtok(NULL, " \t\n");

            if(strncmp(requestLine[2], "HTTP/1.0", 8) != 0 && strncmp(requestLine[2],"HTTP/1.1", 8) != 0)
                write(clients[n], "HTTP/1.0 400 Bad Request\n", 25);
            else {
                if(strncmp(requestLine[1], "/\0", 2) == 0) requestLine[1] = "/index.html";

                strcpy(path, ROOT);
                strcpy(&path[strlen(ROOT)], requestLine[1]);
                printf("File: %s\n", path);

                if((fd = open(path, O_RDONLY)) != -1) {
                    send(clients[n], "HTTP/1.0 200 OK\n\n", 17, 0);
                    while((b_read = read(fd, data, BYTES)) > 0)
                        write(clients[n], data, b_read); }
                else write(clients[n], "HTTP/1.0 404 Not Found\n", 23); }}}

    shutdown(clients[n], SHUT_RDWR);
    close(clients[n]);
    clients[n] = -1; }


int main(int argc, char *argv[]) {
    struct sockaddr_in clientaddr;
    socklen_t addrlen;
    int clientNo = 0;

    for(int i = 0; i < MAXCONNECTS; i++)
        clients[i] = -1;

    ROOT = getenv("PWD");
    printf("Server started on port no. %s with root directory as %s\n", argv[1], ROOT);
    startServer(argv[1]);

    while(1) {
        addrlen = sizeof(clientaddr);
        clients[clientNo] = accept(sockfd, (struct sockaddr*) &clientaddr, &addrlen);

        if(clients[clientNo] < 0) perror("Accept: ");
        else {
            if(fork() == 0) {
                Response(clientNo);
                exit(0); }}

        while (clients[clientNo] != -1) clientNo = (clientNo + 1) % MAXCONNECTS; }

    return 0; }
