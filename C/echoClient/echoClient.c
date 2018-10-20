/*
 *
 * A simple echo client
 *
 * ./client ip port
 *
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/socket.h>
 #include <netinet/in.h>
 #include <error.h>
 #include <string.h>
 #include <unistd.h>
 #include <arpa/inet.h>


 #define ERROR -1
 #define BUFFER 1024

 int main(int argc, char *argv[]) {
      struct sockaddr_in server;
      int sockfd;
      char input[BUFFER];
      char output[BUFFER];
      int data_len;

      if(argc != 3) {
          perror("Arg num: ");
          exit(ERROR); }

      if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == ERROR) {
          perror("Client socket: ");
          exit(ERROR); }

      server.sin_family = AF_INET;
      server.sin_port = htons(atoi(argv[2]));
      server.sin_addr.s_addr = inet_addr(argv[1]);
      bzero(&server.sin_zero, 8);


      if((connect(sockfd,(struct sockaddr*)&server, sizeof(struct sockaddr_in))) == ERROR) {
          perror("Connect: ");
          exit(ERROR); }
      else printf("Connected to server\n");

      while(1) {
          fgets(input, BUFFER, stdin);
          send(sockfd, input, strlen(input), 0);
          printf("Message sent to server: %s\n", input);

          data_len = recv(sockfd, output, BUFFER, 0);
          output[data_len] = '\0';
          printf("Message received from the server: %s\n", output); }

      close(sockfd);

 }
