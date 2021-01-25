#include "server.h"
#include "sys/stat.h"

static void pre_daemon(pid_t pid) {
    if (pid != 0)
        printf("pid of server = %d\n", pid);
}

int mx_daemon(void) {
    pid_t pid = fork();

    pre_daemon(pid);
    if (pid < 0)
        perror("ush: fork");
    else if (pid == 0) {
        if(setsid() < 0)
            exit(EXIT_FAILURE);
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
    }
    else
        exit(EXIT_SUCCESS);
    return 0;
}
