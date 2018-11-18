#include <sys/time.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 

int main()
{
    int        fd;
    char    buf[255];
    int        state; 

    struct    timeval tv; 
    fd_set    readfds, writefds;
    fd = fileno(stdin);
    FD_ZERO(&readfds);

    for (;;)
    {
        FD_SET(fd, &readfds);

        tv.tv_sec = 3;
        tv.tv_usec = 0;

        state = select(fd + 1, &readfds, (fd_set *)0, (fd_set *)0, &tv);
        switch(state)
        {
            case -1:
                perror("select error : ");
                exit(0);
                break;    
            case 0:
                printf("Time over\n");            
                close(fd);
                exit(0);
                break;
            default:
                fgets(buf, 255, stdin);
                printf("%s", buf);
                break;
        }
    }    

}