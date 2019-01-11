#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <openssl/md5.h>
#include <stdbool.h>

#define BYTES 256
#define SEG 512
#define TEMPLATE "FLAG %s %[^\n]s"

typedef struct user_struct {
  char* username;
  char* password;
} user_struct;

typedef struct server_config_struct {
    char server_name[BYTES];
    user_struct* users[4];
    int user_no;
} server_config_struct;

typedef struct recv_command_struct {
    char* flag;
    user_struct user;
    char folder[BYTES];
    char file[BYTES];
} recv_command_struct;



char* find_substring_after_needle(char* haystack, char* needle) {
    char* ptr;

    if(haystack == NULL || needle == NULL) return NULL;

    ptr = strstr(haystack, needle);
    ptr += (ptr) ? strlen(needle) : 0;

    return ptr;
}



void encode_int_to_uchar(u_char* buffer, int n) {
    buffer[0] = (n >> 24) & 0xFF;
    buffer[1] = (n >> 16) & 0xFF;
    buffer[2] = (n >> 8) & 0xFF;
    buffer[3] = n & 0xFF;
}



void decode_int_from_uchar(u_char* buffer, int* n) {
    int temp;

    temp = buffer[0] << 24;
    temp |= buffer[1] << 16;
    temp |= buffer[2] << 8;
    temp |= buffer[3];

    *n = temp;
}



char* find_needle(char* haystack, char* needle) {
    if(haystack == NULL || needle == NULL) return NULL;
    else return strstr(haystack, needle);
}



int recv_from_socket(int socket, u_char* payload, int size_of_payload) {
  int read = 0;

  while((read += recv(socket, 4 + payload, size_of_payload - read, 0)) < 0) {
      perror("Unable to receive payload on socket");
      exit(1);

      if(read == 0) break;
  }

  return read;
}



void get_socket_value(int socket, int* value) {
    u_char payload[4];

    recv_from_socket(socket, payload, 4);
    decode_int_from_uchar(payload, value);
}



void accept_command(int socket, server_config_struct* server_config) {
    char buffer[SEG], temp[SEG], *flag;
    user_struct* user;
    recv_command_struct recv_command;
    int c_size;

    memset(buffer, 0, sizeof(buffer));
    memset(temp, 0, sizeof(temp));
    memset(&recv_command, 0, sizeof(recv_command));

    recv_command.user.username = (char*)malloc(BYTES * sizeof(char));
    recv_command.user.password = (char*)malloc(BYTES * sizeof(char));

    user = &recv_command.user;
    //get_socket_value(socket, &c_size);
    recv_from_socket(socket, buffer, c_size);

    printf("BUFFER: %s\n", buffer);

    //sscanf(buffer, TEMPLATE, &recv_command.flag, temp);
    //flag = recv_command.flag;

    //printf("FLAG: %s", flag);
}



int get_dfs_socket(int port) {
    int sockfd;
    struct sockaddr_in sin;
    int optval = 1;

    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed to start socket");
        exit(1);
    }

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(sin)) < 0) {
        perror("Failed to reuse address");
        exit(1);
    }

    if(bind(sockfd, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("Failed to bind to socket");
        exit(1);
    }

    if(listen(sockfd, 10) < 0) {
        perror("Failed to listen on socket");
        exit(1);
    }

    return sockfd;
}



void assign_new_user_config(char* line, server_config_struct* server_config) {
    char* ptr;
    int len, i;
    ptr = find_substring_after_needle(line, " ");
    len = ptr - line - 1;

    i = server_config->user_no++;

    server_config->users[i] = (user_struct*)malloc(sizeof(user_struct));

    server_config->users[i]->username = strndup(line, len);
    server_config->users[i]->password = strdup(ptr);
    printf("DFS -> New user assigned -> Username: %s / Password: %s\n",
      server_config->users[i]->username, server_config->users[i]->password);
}



void read_config_file(char* file_path, server_config_struct* server_config) {
    FILE* fp;
    char line[BYTES];
    int len;

    printf("FILEPATH: %s\n", file_path);

    if((fp = fopen(file_path, "r")) <= 0) perror("Failed to open configuration file");
    else printf("DFS -> Configuration file successfully opened\n");

    while(fgets(line, sizeof(line), fp)) {
        len = strlen(line);
        line[len - 1] = (line[len - 1] == '\n') ? '\0' : line[len - 1];

        assign_new_user_config(line, server_config);
    }
}



void free_user_struct(user_struct* user) {
  free(user->username);
  free(user->password);
}



void free_server_config_struct( server_config_struct* server_config) {
      int i;
      i = server_config->user_no;

      while(i--) {
          free_user_struct(server_config->users[i]);
      }
}



int main(int argc, char** argv) {
    pid_t pid;
    server_config_struct server_conf;
    char* server_folder;
    int port, listenfd, connfd, stat;
    struct sockaddr_in remote_addrr;
    socklen_t addr_size = sizeof(struct sockaddr_in);

    memset(&server_conf, 0, sizeof(server_conf));
    memset(server_conf.users, 0, sizeof(server_conf.users));

    if(argc != 3) {
        fprintf(stderr, "USAGE: dfs <folder> <port>\n");
        exit(1);
    }

    server_folder = argv[1];
    port = atoi(argv[2]);

    read_config_file("dfs.conf", &server_conf);
    strcpy(server_conf.server_name, server_folder);
    printf("Server folder %s created\n", server_conf.server_name);

    listenfd = get_dfs_socket(port);

    while(1) {
        printf("Waiting to accept new connection...\n");
        if((connfd = accept(listenfd, (struct sockaddr*)&remote_addrr, &addr_size)) <= 0) {
            perror("Failed to accept connection");
            continue;
        }

        pid = fork();
        if(pid != 0) {
            close(connfd);
            waitpid(-1, &stat, WNOHANG);
        } else {
            int pid_no = getpid();
            printf("CHILD PROCESS: %d\n", pid_no);
            accept_command(connfd, &server_conf);
            close(connfd);
            break;
        }

    }

    free_server_config_struct(&server_conf);
    return 0;
}
