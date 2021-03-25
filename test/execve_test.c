/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 10:27:46 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/23 14:26:02 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char *argv[])
{
    extern char **environ;
    char* file=argv[1];
    // char *path;
    // path = getenv("PATH");
    printf("hello\n");
    char* arguments[] = {"ls", NULL };
    // execve("/usr/bin/clear", arguments,environ);
    
    // execv("/bin", arguments);  
}

typedef struct s_file
{
    char *name;
    char *filetype;
}t_file;

typedef struct s_cmds
{
    char **cmd;
    char type;
    t_file filename;
    struct s_cmds *next;
}t_cmds;
