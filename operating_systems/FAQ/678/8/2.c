#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <limits.h>
#include <sys/wait.h>


int 
main(void)
{
    int pid;
    int pfd12[2];
    int pfd23[2];
    char buf[100];
    assert(pipe(pfd12) == 0);
    assert(pipe(pfd23) == 0);
    if ((pid = fork() == 0)) {
//           close(STDIN_FILENO );
          dup2(pfd12[0], STDIN_FILENO);
          close(pfd12[0]); close(pfd12[1]);
          assert(read(pfd12[0], buf, sizeof(buf)) >= 0);
          puts(buf);
          if((pid = fork() != 0)) {
//               close(STDOUT_FILENO);
              dup2(pfd23[1], STDOUT_FILENO);
              close(pfd23[0]); close(pfd23[1]);        
              assert(write(pfd23[0], buf, sizeof(buf)) >= 0); 
          } else if (pid == 0) {
//               close(STDIN_FILENO);
              dup2(pfd23[0], STDIN_FILENO);
              close(pfd23[0]); close(pfd23[1]);
              assert(read(pfd12[0], buf, sizeof(buf)) >= 0);
              puts(buf);
          }
    } else if(pid != 0) {
//         close(STDOUT_FILENO);
        dup2(pfd12[1], STDOUT_FILENO);
        close(pfd12[0]); close(pfd12[1]);        
        execlp("time", "time", NULL); 
    }
    close(pfd12[0]); close(pfd12[1]);
    close(pfd23[0]); close(pfd23[1]);
    wait(NULL); wait(NULL);
    return 0;
}
