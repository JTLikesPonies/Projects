/*
 * udpserver.c - A simple UDP echo server
 * usage: udpserver <port>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dirent.h>

#define BUFSIZE 30000
#define openFlags O_CREAT | O_RDWR
#define filePerms S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
extern int errno;

/*
 * error - wrapper for perror
 */
void error(char *msg) {
  perror(msg);
  exit(1); }

int main(int argc, char **argv) {
  int sockfd; /* socket */
  int portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  char buf[BUFSIZE]; /* message buf */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  int n; /* message byte size */
  int errnum;
  char * token1, * token2;
  char * tempBuf = (char*)malloc(strlen(buf)+1);
  char * tempBuf2 = (char*)malloc(strlen(buf)+1);
  char * msgBuf;
  long sizeInBytes;
  char buf2[BUFSIZE];

  /*
   * check command line arguments
   */
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1); }
  portno = atoi(argv[1]);

  /*
   * socket: create the parent socket
   */
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) error("ERROR opening socket");

  /* setsockopt: Handy debugging trick that lets
   * us rerun the server immediately after we kill it;
   * otherwise we have to wait about 20 secs.
   * Eliminates "ERROR on binding: Address already in use" error.
   */
  optval = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
	     (const void *)&optval , sizeof(int));

  /*
   * build the server's Internet address
   */
  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons((unsigned short)portno);

  /*
   * bind: associate the parent socket with a port
   */
  if (bind(sockfd, (struct sockaddr *) &serveraddr,
	   sizeof(serveraddr)) < 0)
    error("ERROR on binding");

  clientlen = sizeof(clientaddr);

  /*
   * main loop: wait for a datagram, then echo it
   */
  while (1) {
      /*
       * recvfrom: receive a UDP datagram from a client
       */
      bzero(buf, BUFSIZE);
      bzero(buf2, BUFSIZE);
      n = recvfrom(sockfd, buf, BUFSIZE, 0,
  		 (struct sockaddr *) &clientaddr, &clientlen);
      if (n < 0) error("ERROR in recvfrom");
      /*
       * gethostbyaddr: determine who sent the datagram
       */
      hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
      	  sizeof(clientaddr.sin_addr.s_addr), AF_INET);
      if (hostp == NULL)
        error("ERROR on gethostbyaddr");
      hostaddrp = inet_ntoa(clientaddr.sin_addr);
      if (hostaddrp == NULL)
        error("ERROR on inet_ntoa\n");
      printf("\nserver received datagram from %s (%s)\n",
        hostp->h_name, hostaddrp);
      printf("server received %d/%d bytes\n", (int)strlen(buf), n);


      strcpy(tempBuf, buf);
      token1 = strtok(tempBuf," ");


      if(!strcmp(token1,"ls\n")) {
          printf("\nListing all files on server...\n\n");
          DIR *d;
          struct dirent *dir;
          d = opendir(".");
          char * filename;

          if(d) {
              printf("Directory opened\n");

              while(dir = readdir(d)) {
                  printf("File: %s\n",dir->d_name);
                  filename = dir->d_name;

                  n = sendto(sockfd, filename, strlen(filename), 0,
                    (struct sockaddr *) &clientaddr, clientlen); }

              printf("File listing complete");
              closedir(d); }
          else {
              errnum = errno;
              fprintf(stderr,"Failed to open directory: %s\n",strerror(errnum)); }}


      strcpy(tempBuf2, buf);
      token2 = strtok(tempBuf2," ");
      token2 = strtok(NULL," ");
      token2[strlen(token2)-1] = '\0';

      printf("Token1: %s\n", token1);

      if(!strcmp(token1,"get\0")) {
          printf("Download request received from client\n\n");
          FILE * file = fopen(token2,"rb");
          if(file) {
              printf("File opened successfully\n");

              fseek(file,0L,SEEK_END);
              sizeInBytes = ftell(file);
              printf("Size of file: %ld bytes\n", sizeInBytes);
              fseek(file,0L,SEEK_SET);

              msgBuf = (char*) calloc(sizeInBytes,sizeof(char));
              if(msgBuf == NULL) return 1;
              long unsigned readSize = fread(msgBuf,
                sizeof(char),sizeInBytes,file);


              printf("\nSending file to client...\n\n");


              n = sendto(sockfd, msgBuf, readSize, MSG_CONFIRM,
                (struct sockaddr *) &clientaddr, clientlen);
              if (n < 0) error("ERROR in sendto");
              else {
                  printf("Finished sending file\n");
                  printf("%d bytes sent to client\n", n); }}
          else {
              errnum = errno;
              fprintf(stderr,"Failed to open file: %s\n",strerror(errnum));
              n = sendto(sockfd, 0, 0, 0, (struct sockaddr *) &clientaddr,
                clientlen);
              continue; }

          fclose(file);
          free(msgBuf); }


      else if(!strcmp(token1,"put\0")) {
          n = recvfrom(sockfd, buf2, BUFSIZE, 0,
            (struct sockaddr *) &clientaddr, &clientlen);

          printf("Upload request received from client\n\n");

          if (n <= 0) error("ERROR in recvfrom");
          else {
              printf("File uploaded\n");
              printf("%d bytes read from client\n", n); }

          FILE * file = fopen(token2,"wb");
          long unsigned writeSize = fwrite(buf, sizeof(char), n, file);
          printf("Size of file: %ld bytes\n", writeSize);

          fclose(file); }


      else if(!strcmp(token1,"delete\0")) {
          printf("Delete request received from client\n");

          FILE * file = fopen(token2,"w");

          if(file) {
              printf("File opened successfully\n");
              char * filename = (char *)malloc(strlen(token2)+1);
              strcpy(filename,token2);

              printf("Filename: %s", filename);
              fclose(file);

              printf("\nDeleting file on server...\n\n");
              if(remove(filename)) {
                  errnum = errno;
                  fprintf(stderr, "Failed to delete the file: %s\n",
                   strerror(errnum)); }
              else printf("File deleted\n");

              char * retMsg = "File deleted";

              n = sendto(sockfd, retMsg, strlen(retMsg), 0,
                (struct sockaddr *) &clientaddr, clientlen); }
          else {
              errnum = errno;
              fprintf(stderr,"Failed to open file: %s\n",strerror(errnum)); }}

  free(tempBuf);
  free(tempBuf2); }}
