#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    char buf[256];
    int len, len2;
    int count;

    while ((len = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
    {
        count = 0;
        while (count < len)
        {
            if ((len2 = write(STDOUT_FILENO, buf, len)) < 0 ) {
                perror("write");
                return 1;
            }
        }
        count += len2;
    }
    if (len < 0) {
        perror("read");
        return 1;
    }


    return 0;
}
