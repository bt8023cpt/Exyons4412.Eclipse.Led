#include <stdio.h>

int main(int argc, char**argv)
{
        int fd;

        fd = open("/dev/exyons4412_led", 2);
        if(fd < 0)
        {
                printf("open fail!\n");
                return -1;
        }

        int i;
        for(i = 3; i > 0; i--)
        {
                write(fd, &i, 4);
                sleep(1);
                read(fd, &i, 4);
                sleep(1);
        }

        close(fd);
        return 0;
}
