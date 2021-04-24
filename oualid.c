# include "minishell.h"

void ft_debbug (char *tty, char *str)
{
    int fd = open(tty, O_RDWR);
    ft_putendl_fd(str, fd);
}

int main(int ac, char **av)
{
    while (1)
    {
        execve("/bin/ls", av, NULL);
        puts("kkkkkkkk");
    }
    
}