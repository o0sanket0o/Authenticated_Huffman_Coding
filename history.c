#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void loginHistory(bool change) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[164];
    size_t ret = strftime(s, sizeof(s), "%c", tm);

    if (ret == 0) {
        perror("strftime failed");
        return;
    }

    printf("%lu\n", strlen(s));
    printf("%s\n", s);

    int fd = open("history.txt", O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("open");
        return;
    }

    char info[200];
    if(change) strcpy(info, "Password updated on: ");
    else strcpy(info, "Successful login on: ");
    strcat(info, s);
    strcat(info, "\n");

    ssize_t sz = write(fd, info, strlen(info));
    if (sz < 0) {
        perror("write");
    }

    close(fd);  //File Descriptor closed
}

