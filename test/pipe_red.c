/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 10:43:56 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/28 15:27:24 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int main()
// {
//     int p[2];
//     extern char **environ;
//     char* arguments[] = {"ls", NULL };
//     char* arguments2[] = {"wc", NULL };
//     pipe(p);
//       if (fork() == 0) {
//       dup2(p[1], 1);
//       close(p[0]);
//       execve("/bin/ls",arguments, environ);
//       exit(1);
//     }
//     if (fork() == 0) {
//     dup2(p[0], 0);

//     close(p[1]);
//     execve("/usr/bin/wc",arguments2, environ);
//     exit(1);
//     }
//     else { /* Parent */
//         /*  so Close both ends of pipe */
//     close(p[0]);
//     close(p[1]);
// }
// }

// int main(){
//     extern char **environ;
//     char* arguments[] = {"echo","hello", NULL };
//     close(1); // Release fd no - 1
//     // int fd = open("foo.txt", O_CREAT | O_RDONLY); 
//     open("amal",O_RDWR); // Open a file with fd no = 1
//     // Child process
//     if (fork() == 0) {

//         execve("/bin/echo",arguments, environ);
//     //     // exec("cmd1"); // By default, the program writes to stdout (fd no - 1). ie, in this case, the file
//     }
// }
// char    **set_args(char *argv)
// {
//     char    **split;
//     split = ft_split(argv, ' ');
//     return split;
// }
// int main(int argc, char **argv)
// {
//     extern char **environ;
//     char    *path;
//     char    **split;
//     struct stat     *buf;
//     int             i= 0;
//     int             j = 1;
//     char            **tab;
//     int             check;
//     char            cwd[PATH_MAX];
//     int pid;
//     int status;
//     char *realpath;
//     char *tmppath;
//     char **arguments;
//     int p[2];
    
//     path = getenv("PATH");
//     buf = malloc(sizeof(struct stat));
//     split = ft_split(path, ':');
//     pipe(p);
//     i = 0;
//     // while(split[i] != NULL)
//     // {
//     //     printf("%s\n",split[i]);
//     //     i++;
//     // }
//     while(argv[j] != NULL)
//     {
//         i = 0;
//         while (split[i] != NULL)
//         {
//             if (stat(split[i], buf) == 0)
//             {
//                 pid = fork();
//                 status = 0;
//                 tmppath = ft_strjoin(split[i],"/");
//                 realpath = ft_strjoin(tmppath, argv[j]);
//                 arguments = ft_split(argv[j], ' ');
//                 if (pid == -1)
//                 {
//                     ft_putstr_fd(strerror(errno), 1);
//                 }
//                 if (pid == 0)
//                 {
//                     dup2(p[1], 1);
//                     close(p[0]);
//                     execve(realpath,arguments, environ);
//                     exit(1);
//                 }
//                 // if (pid == 0)
//                 // {
//                 //     dup2(p[0], 0);
//                 //     close(p[1]);
//                 //     execve(realpath,arguments, environ);
//                 //     exit(1);
//                 // }
//                 else
//                 {
//                     close(p[0]);
//                     close(p[1]);
//                         // waitpid(pid,&status,0);
//                 }
//             }
//             i++;
//         }
//         j++;
//     }
// }


t_list    *create_list()
{
  t_list *list;

  list = ft_lstnew(strdup("ls"));
  ft_lstadd_back(&list, ft_lstnew(strdup("grep pipe")));
  ft_lstadd_back(&list, ft_lstnew(strdup("wc")));
  return (list);

}
void    loop_pipe(t_list *list) 
{
  int   p[2];
  pid_t pid;
  int   fd_in = 0;
  int status;
  extern char **environ;
  char *path = getenv("PATH");
  t_list *cmd;
  struct stat     *buf;
  buf = malloc(sizeof(struct stat));
  char **tab;
  cmd = list;
  int i;
  char **split = ft_split(path, ':');
  while (cmd != NULL)
  {
    printf("%s\n",cmd->content);
    i = 0;
    while (split[i] != NULL)
    {
        if (stat(split[i], buf) == 0)
        {
          pipe(p);
          if ((pid = fork()) == -1)
          {
              exit(EXIT_FAILURE);
          }
          else if (pid == 0)
          {
              dup2(fd_in, 0); //change the input according to the old one 
              if (cmd->next != NULL)
                dup2(p[1], 1);
              close(p[0]);
              tab = ft_split(cmd->content, ' ');
              printf("%s\n",tab[0]);
              printf("%s\n",tab[1]);
              execve(split[i],tab, environ);
              exit(EXIT_FAILURE);
          }
          else
          {
              wait(NULL);
              close(p[1]);
              fd_in = p[0]; //save the input for the next command
              cmd++;
          }
        }
        i++;
    }
    cmd = cmd->next;
}
}

int main()
{
  char *ls[] = {"ls", NULL};
  char *grep[] = {"grep", "pipe", NULL};
  char *wc[] = {"wc", NULL};
  char **cmd[] = {ls, grep, wc, NULL};

  t_list *list;
  list = create_list();
  loop_pipe(list);
  return (0);
}