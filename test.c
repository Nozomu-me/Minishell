#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
  
// int main()
// {
//     int file_desc = open("tricky.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
      
//     // here the newfd is the file descriptor of stdout (i.e. 1)
//     dup2(file_desc, 1) ; 
//     printf("I will be printed in the file tricky.txt\n");
          
//     // All the printf statements will be written in the file
//     // "tricky.txt"
      
// return 0;
// }

void    loop_pipe(char ***cmd) 
{
  int   p[2];
  pid_t pid;
  int   fd_in = 0;

  while (*cmd != NULL)
    {
      pipe(p);
      if ((pid = fork()) == -1)
        {
          exit(EXIT_FAILURE);
        }
      else if (pid == 0)
        {
            printf("child\n");
          dup2(fd_in, 0); //change the input according to the old one 
          if (*(cmd + 1) != NULL)
            dup2(p[1], 1);
          close(p[0]);
          execvp((*cmd)[0], *cmd);
          exit(EXIT_FAILURE);
        }
      else
        {
            printf("parent\n");
          wait(NULL);
            printf("parent2\n");
          close(p[1]);
          fd_in = p[0]; //save the input for the next command
          cmd++;
        }
    }
}

int main()
{
  char *ls[] = {"ls", NULL};
  char *grep[] = {"grep", "pipe", NULL};
  char *wc[] = {"wc", NULL};
  char **cmd[] = {ls, wc, NULL};

  loop_pipe(cmd);
  return (0);
}