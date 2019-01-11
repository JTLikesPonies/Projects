#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <openssl/md5.h>
#include <stdbool.h>

#define BYTES 256
#define SEG 512

typedef struct server_struct {
    char* name;
    char* address;
    int port;
} server_struct;

typedef struct user_struct {
  char* username;
  char* password;
} user_struct;

typedef struct client_config_struct {
    server_struct* servers[4];
    user_struct* user;
    int server_no;
} client_config_struct;

typedef struct split_struct {
    int id;
    u_char* content;
    int content_len;
} split_struct;

typedef struct split_file_struct {
    char* filename;
    split_struct* pieces[4];
    int split_no;
} split_file_struct;

typedef struct file_location_struct {
    char remote_file[BYTES];
    char remote_folder[BYTES];
    char local_file[BYTES];
    char local_folder[BYTES];
} file_location_struct;

typedef struct server_chunks_struct {
    char file_names[BYTES][BYTES];
    bool chunks[BYTES][4];
    int no_files;
} server_chunks_struct;



char* find_substring_after_needle(char* haystack, char* needle) {
    char* ptr;

    if(haystack == NULL || needle == NULL) return NULL;

    ptr = strstr(haystack, needle);
    ptr += (ptr) ? strlen(needle) : 0;

    return ptr;
}



char* find_needle(char* haystack, char* needle) {
    if(haystack == NULL || needle == NULL) return NULL;
    else return strstr(haystack, needle);
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



char* get_token(char* string, char* delim, int offset) {
    char* ptr = find_substring_after_needle(string, delim);
    int len;
    char *token[2], *temp;

    temp = malloc(strlen(string));
    strcpy(temp, string);

    if(ptr == NULL) {
        if(strlen(string) != 0 && offset == 0) return strdup(string);
        else return NULL;
    }

    token[0] = strtok(temp, " ");
    token[1] = strtok(NULL, " ");
    for(int i = 0; i < 2; i++) {
        if(i == offset) {
          return token[i];
        }
    }
}



void get_file_and_folder(char* buffer, file_location_struct* file_loc, char* location) {
    char* ptr;
    int length, temp_len;
    //printf("BUFFER: %s\n", buffer);

    if(buffer == NULL) exit(1);
    length = strlen(buffer);

    ptr = strrchr(buffer, '/'); ++ptr;
    //printf("POINTER: %s\n", ptr);
    if(location == "local") {
        if(ptr) {
            strcpy(file_loc->local_file, ptr);
            printf("Local file: %s\n", file_loc->local_file);
            temp_len = ptr - buffer;
            strncpy(file_loc->local_folder, buffer, temp_len);
            printf("Local folder: %s\n", file_loc->local_folder);
        } else {
            if((ptr = find_needle(buffer, "/")) != 0) {
                strcpy(file_loc->local_folder, buffer);
                printf("Local file: %s\n", file_loc->local_folder);
            } else {
                strcpy(file_loc->local_file, buffer);
                printf("Local folder: %s\n", file_loc->local_file);
            }
        }
    } else if(location == "remote") {
        if(ptr) {
            strcpy(file_loc->remote_file, ptr);
            printf("Remote file: %s\n", file_loc->remote_file);
            temp_len = ptr - buffer;
            strncpy(file_loc->remote_folder, buffer, temp_len);
            printf("Remote folder: %s\n", file_loc->remote_folder);
        } else {
            if((ptr = find_needle(buffer, "/")) != 0) {
                strcpy(file_loc->remote_folder, buffer);
                printf("Remote folder: %s\n", file_loc->remote_folder);
            } else {
                strcpy(file_loc->remote_file, buffer);
                printf("Remote file: %s\n", file_loc->remote_file);
            }
        }
    }
}



int no_of_char_in_string(char* string, char character) {
    int count = 0, i;

    if(string == NULL) return 0;
    for(i = 0; i < strlen(string); i++) {
        if(string[i] == character) count++;
    }

    return count;
}



bool does_dir_exist(char* path) {
    struct stat fileStat;

    if(stat(path, &fileStat) < 0)
  	  return false;

    /*printf("Information for %s\n",path);
    printf("---------------------------\n");
    printf("File Size: \t\t%ld bytes\n",fileStat.st_size);
    printf("Number of Links: \t%ld\n",fileStat.st_nlink);
    printf("File inode: \t\t%ld\n",fileStat.st_ino);

    printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");

    printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");*/

    if(S_ISDIR(fileStat.st_mode)) {
        printf("Valid directory\n");
        return true;
    } else {
        printf("Invalid directory\n");
        return false;
    }
    //else printf("Not a valid directory\n");
}



bool does_file_exist(char* folder, char* file) {
    char filepath[256];
    memset(filepath, 0, sizeof(filepath));

    //printf("FOLDER: %s FILE: %s\n", folder, file);

    sprintf(filepath, "%s%s", folder, file);
    //printf("FILEPATH: %s\n", filepath);

    if(access(filepath, F_OK) != -1) {
        printf("File exists in local directory\n");
        return true;
    } else {
        printf("Cannot find file in local directory\n");
        return false;
    }
}



bool validate_filepath(char* message, file_location_struct* file_loc, user_struct* user, char* request) {
    char *file, *folder;
    folder = file_loc->remote_folder;
    file = file_loc->remote_file;

    if(request == "get") {
        folder = (strlen(folder) > 0) ? folder : "/";
        if(strlen(file) == 0) return false;

        if(!does_dir_exist(file_loc->local_folder)) return false;

    } else if(request == "put") {
        folder = (strlen(folder) > 0) ? folder: "/";
        if(strlen(file) == 0) return false;

        if(!does_dir_exist(file_loc->local_folder))  return false;
        if(!does_file_exist(file_loc->local_folder, file_loc->local_file)) return false;

    } else if(request == "list") {
        folder = (strlen(folder) > 0) ? folder : "/";
        file = (strlen(file) > 0) ? file : "NULL";

    } else if(request == "mkdir") {
        if(strlen(folder) == 0) return false;
        if(strlen(file) > 0) return false;

        file = "NULL";

    }
    return true;
}



bool validate_request(char* message, char* request, file_location_struct* file_loc) {
    char *token, temp_buff[BYTES];
    int no_of_spaces, length;
    length = strlen(message);

    memset(temp_buff, 0, sizeof(temp_buff));
    no_of_spaces = no_of_char_in_string(message, ' ');


    if(request == "get" || request == "put") {
        if(no_of_spaces != 2) {
            if(request == "get") printf("'get' request requires 2 file locations\n");
            else if(request == "put") printf("'put' request requires 2 file locations\n");

            return false;
        }

        for(int j = 0; j < 2; j++) {
            token = get_token(message, " ", j);
            //printf("TOKEN: %s\n", token);

            memset(temp_buff, 0, sizeof(temp_buff));
            strcpy(temp_buff, token);
            //printf("TEMP_BUFF: %s\n", temp_buff);
            //free(token);

            get_file_and_folder(temp_buff, file_loc, (j == 0) ? "local" : "remote");
        }
    } else if(request == "list") {
        if(length == 0 || length == no_of_spaces) {
            message[0] = '/';
            length = 1;
        }

        get_file_and_folder(message, file_loc, "remote");
    } else if(request == "mkdir") {
        if(no_of_spaces != 1) {
            printf("'mkdir'request requires exactly one file location\n");
            return false;
        }

        if(message[length -1] != '/') {
            message[length] = '/';
            ++length;
        }

        get_file_and_folder(message, file_loc, "remote");
    } else {
        printf("---UNKNOWN COMMAND---\n");
    }

    return true;
}


int get_dfc_socket(server_struct* server) {
    int sockfd;
    struct sockaddr_in serv_addr;
    struct timeval tv;
    memset(&tv, 0, sizeof(tv));
    tv.tv_sec = 1;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed to start socket");
        exit(1);
    }

    if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(struct timeval)) < 0) {
        perror("Failed to set timeout");
        exit(1);
    }

    memset(&serv_addr, 9, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server->port);

    if(inet_pton(AF_INET, server->address, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(1);
    }

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Failed to connect");
        return -1;
    }

    return sockfd;
}


void terminate_dfc_to_dfs(int* socket, client_config_struct* client_config) {

}


bool connect_dfc_to_dfs(int* socket, client_config_struct* client_config) {
    bool connected = false;

    if(((socket) = (int*)malloc(client_config->server_no * sizeof(int))) == NULL)
        printf("Failed to allocate space for socket\n");

    for(int i = 0; i < client_config->server_no; i++) {
        socket[i] = get_dfc_socket(client_config->servers[i]);
        //printf("SOCKET: %d\n", socket[i]);
        if(socket[i] <= 0) perror("Socket failed to connect");
        else connected = true;
    }

    return connected;
}



/*void get_socket_value(int socketfd, int* value) {
    u_char* pl[4];
    int read = 0, temp;

    while((read += recv(socketfd, read + value, 4 - read, 0)) < 0) {
        //printf("SENTINEL\n");
        perror("Unable to receive payload on socket");
        exit(1);

        if(read == 0) break;
    }


    decode_int_from_uchar(*pl, value);
}*/



int send_to_socket(int socket, u_char* payload, int pl_size) {
    int sent = 0;

    while(sent != pl_size) {
        //printf("SENTINEL\n");
        if((sent += send(socket, payload + sent, pl_size - sent, 0)) < 0) {
            perror("Failed to send entire payload via socket");
            exit(1);
        }
    }

    return sent;
}



void send_socket_value(int socketfd, int buff_size) {
    u_char payload[4];

    encode_int_to_uchar(payload, buff_size);
    send_to_socket(socketfd, payload, 4);
}



bool send_command(int* sockets, char* message, int connections) {
    bool ret_val = false;
    int i, buff_size;
    buff_size = strlen(message);

    for(i = 0; i < connections; i++) {
        if(sockets[i] == -1)
          continue;

        //printf("SOCKET: %d\n", sockets[i]);

        //send_socket_value(sockets[i], buff_size);
        send_to_socket(sockets[i], message, buff_size);
        ret_val = true;
    }


    return ret_val;
}



void execute_command(int* sockets, char* message, int connections,
  file_location_struct* file_loc, char* request, client_config_struct* client_config) {
    char filepath[BYTES];
    split_file_struct split_file;
    server_chunks_struct server_chunks;
    bool sent, error;

    memset(filepath, 0, sizeof(filepath));
    memset(&split_file, 0, sizeof(split_file));
    memset(&server_chunks, 0, sizeof(server_chunks));

    printf("Sending command to remote servers\n");
    sent = send_command(sockets, message, connections);

}



void handle_dfc_request(int* socket, char* request, char* buffer, client_config_struct* client_config) {
    file_location_struct file_loc;
    char message[SEG];
    bool built, connected;
    memset(message, 0, sizeof(message));
    memset(&file_loc, 0, sizeof(file_loc));

    if(validate_request(buffer, request, &file_loc)) {
        if(request == "get") {
            built = validate_filepath(message, &file_loc, client_config->user, "get");
        } else if(request == "put") {
            built = validate_filepath(message, &file_loc, client_config->user, "put");
        } else if(request == "list") {
            built = validate_filepath(message, &file_loc, client_config->user, "list");
        } else if(request == "mkdir") {
            built = validate_filepath(message, &file_loc, client_config->user, "mkdir");
        }

        if(!built) {
            perror("Error building request");
        } else {
            printf("Connecting to servers...\n");
            if(connected = connect_dfc_to_dfs(socket, client_config)) {
                for(int j = 0; j < 4; j++) {
                    printf("SOCKET: %d\n", socket[j]);
                }


                execute_command(socket, message, client_config->server_no, &file_loc, request, client_config);
                printf("Disconnecting from servers...\n");
                terminate_dfc_to_dfs(socket, client_config);
            } else printf("Failed to connect to any server\n");
        }
    } else printf("Request was invalid\n");
}



void assign_new_user_config(char* line, client_config_struct* client_config, int flag) {
    char* ptr;
    ptr = find_substring_after_needle(line, " ");

    client_config->user = (user_struct*)malloc(sizeof(user_struct));

    if(flag == 1) {
        client_config->user->username = strdup(ptr);
        printf("User '%s' found in .conf file\n", client_config->user->username);
    } else {
        client_config->user->password = strdup(ptr);
        printf("Password '%s' found in .conf file\n", client_config->user->password);
    }
}



void assign_new_server(char* line, client_config_struct* client_config) {
    char *ptr1, *ptr2;
    int len, i;

    ptr1 =find_substring_after_needle(line, " ");
    ptr2 =find_substring_after_needle(ptr1, " ");
    len = ptr2 - ptr1 - 1;


    i = client_config->server_no++;
    client_config->servers[i] = (server_struct*)malloc(sizeof(server_struct));
    client_config->servers[i]->name = strndup(ptr1, len);
    ptr1 =find_substring_after_needle(ptr2, ":");

    len = ptr1 - ptr2 - 1;
    client_config->servers[i]->address = strndup(ptr2, len);
    client_config->servers[i]->port = atoi(ptr1);

    printf("DFC -> Server %s started on port %d\n", client_config->servers[i]->name,
      client_config->servers[i]->port);
    /*printf("DFC -> NAME -> %s\n", client_config->servers[i]->name);
    printf("DFC -> ADDRESS -> %s\n", client_config->servers[i]->address);
    printf("DFC -> PORT -> %d\n", client_config->servers[i]->port);*/
}



void read_config_file(char* filepath, client_config_struct* client_config) {
    FILE* fp;
    char line[BYTES];
    int line_len;
    if((fp = fopen(filepath, "r")) <= 0) {
        perror("DFC -> Error opening file ");
        exit(1);
    } else printf("DFC -> Configuration file successfully opened\n");


    while(fgets(line, sizeof(line), fp)) {
        line_len = strlen(line);
        line[line_len - 1] = (line[line_len - 1] == '\n') ? '\0' : line[line_len - 1] ;

        if(find_needle(line, "Server")) assign_new_server(line, client_config);
        else if(find_needle(line, "Username")) assign_new_user_config(line, client_config, 1);
        else if(find_needle(line, "Password")) assign_new_user_config(line, client_config, 0);
    }
}



void free_server_config_struct(server_struct* server) {
    free(server->name);
    free(server->address);
}



void free_user_struct(user_struct* user) {
    free(user->username);
    free(user->password);
}



void free_client_config_struct(client_config_struct* client_config) {
    int i;

    free_user_struct(client_config->user);

    while(i--) {
        free_server_config_struct(client_config->servers[i]);
    }
}



int main(int argc, char** argv) {
    char *file_path, buffer[BYTES], *ptr;
    client_config_struct client_config;
    int *socketfds, buff_len;
    //split_file_struct split_file;

    memset(&client_config, 0, sizeof(client_config));
    memset(&client_config.servers, 0, sizeof(client_config.servers));


    if(argc != 2) {
        printf("USAGE -> dfc <conf_file>\n");
        exit(1);
    }

    file_path = argv[1];
    read_config_file(file_path, &client_config);

    while(1) {
        memset(buffer, 0, sizeof(buffer));
        //memset(&split_file, 0, sizeof(split_file));
        //memset(split_file.pieces, 0, sizeof(split_file.pieces));

        fprintf(stdout, "Enter command -> ");
        fgets(buffer, BYTES, stdin);
        buff_len = strlen(buffer);
        if(buffer[buff_len-1] == '\n') buffer[--buff_len] = '\0';

        socketfds = (int*)malloc(client_config.server_no * sizeof(int));

        if(ptr = find_substring_after_needle(buffer, "get")) {
            handle_dfc_request(socketfds, "get", ptr, &client_config);
        }
        else if(ptr = find_substring_after_needle(buffer, "put")) {
            handle_dfc_request(socketfds, "put", ptr, &client_config);
        }
        else if(ptr = find_substring_after_needle(buffer, "list")) {
            handle_dfc_request(socketfds, "list", ptr, &client_config);
        }
        else if(ptr = find_substring_after_needle(buffer, "mkdir")) {
            handle_dfc_request(socketfds, "mkdir", ptr, &client_config);
        }
        else printf("Invalid request\n");

        memset(buffer, 0, sizeof(buffer));
        free(socketfds);
    }
    free_client_config_struct(&client_config);
    return 0;
}
