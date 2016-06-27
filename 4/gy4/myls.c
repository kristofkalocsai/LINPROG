#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main()
{
    DIR* dir;
    struct dirent* elem;

    if ((dir = opendir(".")) == NULL) {
        perror("opendir");
        return 1;
    }

    while ((elem = readdir(dir)) != NULL) {
        printf("%s\n", elem->d_name);
    }

    if (errno) {
        perror("readdir");
        return 1;
    }

    closedir(dir);
    return 0;
}
