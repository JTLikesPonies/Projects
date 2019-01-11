/*
 * udpclient.c - A simple UDP client
 * usage: udpclient <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>


#define BUFSIZE 30000
extern int errno;

/*
 * error - wrapper for perror
 */
void error(char *msg) {
    perror(msg);
    exit(0); }

int main(int argc, char **argv) {
    int sockfd, portno, n;
    int serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;
    char buf[BUFSIZE];
    char * token1, * token2;
    char * tempBuf = (char*)malloc(strlen(buf)+1);
    char * tempBuf2 = (char*)malloc(strlen(buf)+1);
    int errnum;
    char * msgBuf;
    long sizeInBytes;

    /* check command line arguments */
    if (argc != 3) {
       fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       exit(0); }

    hostname = argv[1];
    portno = atoi(argv[2]);

    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* gethostbyname: get the server's DNS entry */
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0); }

    /* build the server's Internet address */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
	  (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);

    serverlen = sizeof(serveraddr);

    while(1) {
        /* get a message from the user */

        bzero(buf, BUFSIZE);
        printf("\nGiven the options below, enter a message with any appropriate parameters:\n\n");
        printf("1. get 'filename'\n2. put 'filename'\n3. delete 'filename'\n4. ls\n5. exit\n");
        printf("\nPlease enter msg: ");
        fgets(buf, BUFSIZE, stdin);

        strcpy(tempBuf, buf);
        token1 = strtok(tempBuf," ");


        if(!strcmp(token1,"ls\n\0")) {
            n = sendto(sockfd, token1, strlen(token1), 0,
              (struct sockaddr *) &serveraddr, serverlen);
            if (n < 0)
                error("ERROR in sendto");

            printf("Listing all files on server...\n\n");
            do {
                n = recvfrom(sockfd, buf, BUFSIZE, 0,
                  (struct sockaddr *) &serveraddr, &serverlen);
                printf("%s\n",buf);
                bzero(buf,BUFSIZE); } while(n); }


        else if(!strcmp(token1,"exit\n\0")) {
            printf("Exiting...\n\n");
            int i = shutdown(sockfd,2);
            return 0; }


        if(!strcmp(token1,"get\0")) {
            strcpy(tempBuf2, buf);
            token2 = strtok(tempBuf2," ");
            token2 = strtok(NULL," ");
            token2[strlen(token2)-1] = '\0';
            n = sendto(sockfd, buf, BUFSIZE, 0,
              (struct sockaddr *) &serveraddr, serverlen);
            if (n < 0)
                error("ERROR in sendto");

            n = recvfrom(sockfd, buf, BUFSIZE, 0,
              (struct sockaddr *) &serveraddr, &serverlen);

            if (n < 0) error("ERROR in recvfrom");
            else if(n == 0) {
                printf("Failed to open file\nFile does not exist\n");
                continue; }
            else {
                printf("%d bytes read from server\n", n);
                printf("File downloaded\n");

                FILE *infile = fopen(token2,"wb");
                long unsigned writeSize = fwrite(buf, sizeof(char), n, infile);
                printf("Size of file: %ld bytes\n", writeSize);

                fclose(infile); }}


        else if(!strcmp(token1,"put\0")) {
            n = sendto(sockfd, buf,strlen(buf), 0,
              (struct sockaddr *) &serveraddr, serverlen);
            if (n < 0) error("ERROR in sendto");
            else printf("Sending request to server\n");

            strcpy(tempBuf2, buf);
            token2 = strtok(tempBuf2," ");
            token2 = strtok(NULL," ");
            token2[strlen(token2)-1] = '\0';
            FILE *outfile = fopen(token2,"rb");
            if(outfile) {
                printf("File opened successfully\n");

                fseek(outfile,0L,SEEK_END);
                sizeInBytes = ftell(outfile);
                printf("Size of file: %ld bytes\n", sizeInBytes);
                fseek(outfile,0L,SEEK_SET);

                msgBuf = (char*) calloc(sizeInBytes,sizeof(char));
                if(msgBuf == NULL) return 1;
                long unsigned readSize = fread(msgBuf,
                  sizeof(char),sizeInBytes,outfile);


                printf("\nSending file to server...\n\n");


                n = sendto(sockfd, msgBuf, readSize, 0,
                  (struct sockaddr *) &serveraddr, serverlen);
                if (n < 0) error("ERROR in sendto");
                else {
                    printf("Finished sending file\n");
                    printf("%d bytes sent to server\n", n); }

                fclose(outfile);
                free(msgBuf); }

            else {
                errnum = errno;
                fprintf(stderr,"Failed to open file: %s\n",strerror(errnum));
                continue; }}


        else if(!strcmp(token1,"delete\0")) {
            strcpy(tempBuf2, buf);
            token2 = strtok(tempBuf2," ");
            token2 = strtok(NULL," ");
            token2[strlen(token2)-1] = '\0';
            printf("Deleting file on server...\n\n");

            n = sendto(sockfd, buf, strlen(buf), 0,
              (struct sockaddr *) &serveraddr, serverlen);

            n = recvfrom(sockfd, buf, strlen(buf), 0,
              (struct sockaddr *) &serveraddr, &serverlen);
            printf("%s\n", buf); }


    free(tempBuf);
    free(tempBuf2); }

    return 0; }
