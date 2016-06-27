#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    struct stat st;


    if(argc < 2)
    {
        printf("usage: %s filename\n", argv[0]);
        return 1;
    }

    if(stat(argv[1], &st) < 0){
        perror("stat");
        return 1;
    }

    printf("dev=%lu\n", st.st_dev);
    printf("mode=%#o\n", st.st_mode);
    printf("uid=%u\n", st.st_uid);
    printf("gid=%u\n", st.st_gid);
    printf("size=%zu\n", st.st_size);
    printf("bs=%lu\n", st.st_blksize);
    printf("blocks=%lu\n", st.st_blocks);

    return 0;
}
