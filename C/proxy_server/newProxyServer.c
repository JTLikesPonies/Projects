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
#include <time.h>
#include <pthread.h>

#define MAXREQ 8192
#define MAXURL 2048
#define BYTES 512

struct args {
    int id;
    int connfd;
    char buffer[MAXREQ]; };

struct request {
    char request[MAXREQ];
    char method[16];
    char path[MAXURL];
    char version[16];
    char conttenttype[128];
    char host[MAXURL];
    char page[MAXURL]; };





int connectTo(char *host, int portno) {
    struct sockaddr_in server_addr;
    struct hostent *server;
    int sock;

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Client socket\n");
        exit(1); }

    printf("CONNECTING TO HOST @ %s\n", host);
    server = gethostbyname(host);
    if(server == NULL) {
        perror("Client host\n");
        exit(1); }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    server_addr.sin_port = htons(80);

    if(connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connecting to client socket\n");
        exit(0); }

    return sock; }





void sendRequest(char filename[MAXURL], char host[MAXURL], int sockfd) {
    time_t res;
    res = time(NULL);
    struct tm* brokentime = localtime(&res);
    int bytesRead, bytesWritten;
    ssize_t sckt;
    int totalread = 0;
    int totalwritten = 0;

    char data[BYTES];
    char requestBuff[BYTES];
    bzero(requestBuff, BYTES);

    sckt = connectTo(host, 80);
    strcat(requestBuff, "GET ");
    strcat(requestBuff, filename);
    strcat(requestBuff, " HTTP/1.1\n");
    strcat(requestBuff, "host: ");
    strcat(requestBuff, host);
    strcat(requestBuff, "\n\n");
    printf("request sent to %s \n%s\nSent at: %s\n", host, requestBuff, asctime(brokentime));

    bytesRead = write(sckt, requestBuff, strlen(requestBuff));
    while((bytesRead = read(sckt, data, sizeof(data))) != (size_t)NULL) {
        bytesWritten = write(sockfd, data, bytesRead);
        totalread += bytesRead;
        totalwritten += bytesWritten; }

    close(sckt);
    close(sockfd); }





void parseRequest(char *request, struct request *myreq) {
    char host[MAXURL], page[MAXURL];
    strncpy(myreq->request, request, MAXREQ-1);
    strncpy(myreq->method, strtok(request, " "), 16-1);
    strncpy(myreq->path, strtok(NULL, " "), MAXURL-1);
    strncpy(myreq->version, strtok(NULL, "\r\n"), 16-1);
    sscanf(myreq->path, "http://%99[^/]%99[^\n]", host, page);
    strncpy(myreq->host, host, MAXURL-1);
    strncpy(myreq->page, page, MAXURL-1);
    printf("method: %s\nversion: %s\npath: %s\nhost: %s\npage: %s\n", myreq->method, myreq->version, myreq->path, myreq->host, myreq->page); }





void *processClient(void *args) {
    int bytesRead;
    struct args* myarg = (struct args*) args;
    struct request* myreq;
    myreq = (struct request*) malloc(sizeof(struct request));

    bzero(myarg->buffer, MAXREQ);
    bytesRead = read(myarg->connfd, myarg->buffer, sizeof(myarg->buffer));
    parseRequest(myarg->buffer, myreq);
    sendRequest(myreq->page, myreq->host, myarg->connfd);

    printf("Thread %d exits\n", myarg->id);
    pthread_exit(NULL); }





int listenFor(int sockfd) {
    int client_length, newsockfd;
    struct sockaddr_in client_addr;

    listen(sockfd, 100);

    client_length = sizeof(client_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_length);
    if(newsockfd < 0) printf("ERROR on accept\n");

    return newsockfd; }





int serverSocket(int port) {
    int sockfd;
    struct sockaddr_in server_addr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Server socket");
        exit(1); }
    else printf("\n\n****Creating proxy server on port %d****\n\n\n", port);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
      (const void *)&optval , sizeof(int));

    if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind on server socket");
        exit(1); }

    return sockfd; }





int main(int argc, char *argv[]) {
    time_t res;
    res = time(NULL);
    struct tm* brokentime = localtime(&res);
    int port = atoi(argv[1]);
    int threadID = 0;

    int server_sock;
    server_sock = serverSocket(port);

    while(1) {
        struct args* myargs;
        myargs = (struct args*) malloc(sizeof(struct args));
        myargs->connfd = listenFor(server_sock);

        pthread_t thread;
        threadID++;
        myargs->id = threadID;
        pthread_create(&thread, NULL, processClient, myargs);
        printf("Thread %d created\n", myargs->id); }

    close(server_sock);
    return 0; }
