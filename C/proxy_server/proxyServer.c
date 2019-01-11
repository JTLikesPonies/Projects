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

int sk1, sk2, clients[MAXCONNECTS];




void Receive(int n) {

}




void openRequestSocket(int n, char * host, char * message) {
    struct addrinfo hints, *res, *p;
    char clientMsg[99999], data[BYTES];
    char newHost[sizeof(host)-7];

    strcpy(clientMsg, message);
    printf("%s", clientMsg);

    for(int i = 0; i < sizeof(newHost); i++) {
        newHost[i] = host[i+7]; }

    printf("\n\n\nHost: %d\n\n\n\n", host[7]);
    printf("\n\n\nNew host: %d\n\n\n\n", newHost[0]);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;

    int result = getaddrinfo(host, "http", &hints, &res);
    if(result != 0) {
        fprintf(stderr, "getaddrinfo() %s", gai_strerror(result));
        exit(1); }

    freeaddrinfo(res);
}




void verifyRequest(int n) {
    struct addrinfo hints, *res, *p;
    char msgBuff[99999], *requestLine[3], tempBuff[99999];
    int rcvd;


    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    memset((void *)msgBuff, (int)'\0', 99999);

    rcvd = recv(clients[n], msgBuff, 99999, 0);
    strcpy(tempBuff, msgBuff);

    if(rcvd <= 0) perror("Receive: ");
    else {
        requestLine[0] = strtok(tempBuff, " \t\n");
        if(strncmp(requestLine[0], "GET\0", 4) == 0) {
            //printf("%s", msgBuff);
            requestLine[1] = strtok(NULL, " \t");
            requestLine[2] = strtok(NULL, " \t\n");

            if(strncmp(requestLine[2], "HTTP/1.0", 8) != 0 && strncmp(requestLine[2],"HTTP/1.1", 8) != 0)
                write(clients[n], "HTTP/1.0 400 Bad Request\n", 25);
            else {
                openRequestSocket(n, requestLine[1], msgBuff); }}}

    shutdown(clients[n], SHUT_RDWR);
    close(clients[n]);
    clients[n] = -1; }




void startProxy(char *port) {
      struct addrinfo hints, *res, *p;

      memset(&hints, 0, sizeof(hints));
      hints.ai_family = AF_INET;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_PASSIVE;
      if(getaddrinfo(NULL, port, &hints, &res) != 0) {
        perror("Get address info: ");
        exit(1); }

        for(p = res; p != NULL; p = p->ai_next) {
          sk1 = socket(p->ai_family, p->ai_socktype, 0);
          if(sk1 == -1) {
            perror("Socket 1: ");
            continue; }

            int optval = 1;
            setsockopt(sk1, SOL_SOCKET, SO_REUSEADDR,
              (const void *)&optval , sizeof(int));

              if(bind(sk1, p->ai_addr, p->ai_addrlen) == -1) {
                close(sk1);
                perror("Bind: ");
                continue; }

                break; }

                if(p == NULL) {
                  perror("Socket or Bind: ");
                  exit(1); }

                  freeaddrinfo(res);

                  if(listen(sk1, 1000000) != 0) {
                    perror("Listen1: ");
                    exit(1); }}




int main(int argc, char *argv[]) {
    struct sockaddr_in clientaddr;
    socklen_t addrlen;
    int clientNo = 0;

    for(int i = 0; i < MAXCONNECTS; i++)
        clients[i] = -1;

    //ROOT = getenv("PWD");
    startProxy(argv[1]);
    printf("Proxy server started on port no. %s\n", argv[1]);

    while(1) {
        addrlen = sizeof(clientaddr);
        clients[clientNo] = accept(sk1, (struct sockaddr*) &clientaddr, &addrlen);

        if(clients[clientNo] < 0) perror("Accept: ");
        else {
            if(fork() == 0) {
                verifyRequest(clientNo);
                //Receive(clientNo);
                exit(0); }}

        while (clients[clientNo] != -1) clientNo = (clientNo + 1) % MAXCONNECTS; }

    return 0; }
