#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

int main(int argc, char* *argv) {
  struct stat fileStat;
  char filepath[] = "makefile";

  printf("HELLO\n");

  if(stat(filepath, &fileStat) < 0) {
    perror("NOT A VALID PATH\n");
	  return 1;
  }

  printf("Information for %s\n",filepath);
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

  printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

  if(S_ISDIR(fileStat.st_mode)) printf("Valid directory\n");
  else printf("Not a valid directory\n");

  return 0;
}
