#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <errno.h>

/* ledtest /dev/myled on
 * ledtest /dev/myled off
*/
int main(int argc, char** argv)
{
    int status;
    if (argc != 3)
    {
        printf("Usage: %s /dev/myled on|off\n", argv[0]);
        return -1;
    }

    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL)
    {
        perror("fopen");
        return -1;
    }

    if( strcmp(argv[2], "on") == 0)
    {
        status = 1;
        fputc(&status, fp);
    }
    else if( strcmp(argv[2], "off") == 0)
    {
        status = 0;
        fputc(&status, fp);
    }
    else
    {
        printf("Usage: %s /dev/myled on|off\n", argv[0]);
        return -1;
    }
    return 0;
}