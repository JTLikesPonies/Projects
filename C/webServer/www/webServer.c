/*
 *
 * A simple web server
 *
 * ./webServer port_no
 *
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/socket.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <netinet/in.h>
 #include <error.h>
 #include <string.h>
 #include <unistd.h>
 #include <arpa/inet.h>
 #include <fcntl.h>
 #include <netdb.h>
 #include <sys/sendfile.h>

#define ERROR -1
#define MAX_DATA 40000


char * append(char *line) {
    char * newLine = malloc(strlen(line) + 2);
    int len = strlen(newLine);

    if(line[0] == '\n') return line;
    else {
        for(int i = 0; i < strlen(line); i++)
            newLine[i] = line[i];

        newLine[strlen(line)-1] = '\"';
        newLine[strlen(line)] = '\n'; }

    return newLine; }


char * prepend(char *line) {
    char * newLine = malloc(strlen(line) + 1);

    if(line[0] == '\n') return line;
    else {
        newLine[0] = '\"';
        for(int i = 0; i < strlen(line); i++) {
            newLine[i+1] = line[i]; }}

    return newLine; }


 int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sockaddr_len = sizeof(client_addr);
    int fd_server, fd_client;
    int data_len;
    FILE *fpImg;
    char *line, *prepLine, *appLine;
    int on = 1;
    char data[MAX_DATA];
    int addrLen = sizeof(server_addr);

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

    if(listen(fd_server,10) == ERROR) {
        perror("Listen: ");
        close(fd_server);
        exit(ERROR); }

    while(1) {
        //printf("\n~~~~~~~~~~~~~~ Waiting for new connection ~~~~~~~~~~~~~~~~~~\n\n");
        if((fd_client = accept(fd_server,(struct sockaddr*)&client_addr,(socklen_t*)&addrLen)) == ERROR) {
            perror("Accept: ");
            continue; }
        printf("Connection to client established\n");

        if(!fork()) {
            //printf("From the child:\n");
            close(fd_server);
            memset(data, 0, MAX_DATA);
            recv(fd_client, data, MAX_DATA, 0);

            printf("%s\n", data);

            if(!strncmp(data, "GET /index.html", 15)) {
                fpImg = fopen("index.html", "rb");
                if(fpImg) printf("File opened successfully\n"); {
                    char responseHead[MAX_DATA];
                    fseek(fpImg,0L,SEEK_END);
                    int sizeInBytes = ftell(fpImg);
                    fseek(fpImg,0L,SEEK_SET);
                    char buf[MAX_DATA];

                    sprintf(responseHead, "HTTP/1.1 200 Document Follows\r\n");
                    sprintf(responseHead + strlen(responseHead), "Content-Type: text/html,text/plain,image/png,image/gif,image/jpg,text/css,application/javascript\r\n");
                    sprintf(responseHead + strlen(responseHead), "Content-Length: %d\r\n\r\n", sizeInBytes);

                    while((line = fgets(buf, sizeof(buf), fpImg)) != NULL) {
                        prepLine = prepend(line);
                        appLine = append(prepLine);
                        sprintf(responseHead + strlen(responseHead), "%s", appLine); }

                //fwrite(responseHead, sizeof(char), sizeof(fpImg), fpImg);
                    printf("%s\n",responseHead);
                    send(fd_client, responseHead, strlen(responseHead)-1, 0);
                    printf("Response sent to client\n");
                    fclose(fpImg); }}
            else perror("Failed to open file");

            close(fd_client);
            printf("Closing connection to client...Closed\n");
            exit(0); }

        //printf("From the parent:\n");
        close(fd_client);}

    return 0;
    }
