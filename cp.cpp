#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 4096
#define MODE 0644

void oops(char*, char*);

int main(int argc, char* argv[])
{
    int open_fd, creat_fd, count;
    char* buf[BUFFERSIZE];
    if (argc != 3)
    {
        fprintf(stderr, "usage:%s source file destination file\n", argv[0]);
        return -1;
    }
        
    if ((open_fd = open(argv[1], O_RDONLY)) == -1)
        oops("open source file error", argv[1]);
    if ((creat_fd = creat(argv[2], MODE)) == -1)
        oops("creat destination file error", argv[2]);
    
    while ((count = read(open_fd, buf, BUFFERSIZE)) > 0)
        if ((write(creat_fd, buf, count)) != count)
            oops("write destination error", argv[2]);
    if (count == -1)
        oops("read source file error", argv[1]);

    if (close(open_fd) == -1 || close(creat_fd))
        oops("close file error", "");
    return 0;
}

void oops(char* arg1, char* arg2)
{
    fprintf(stderr, "ERROR: %s ", arg1);
    perror(arg2);
}
