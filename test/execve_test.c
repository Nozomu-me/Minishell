/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 10:27:46 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/20 18:28:17 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char *argv[])
{
    extern char **environ;
    char* file=argv[1];
    // char *path;
    // path = getenv("PATH");
    // printf("%s\n",argv[1]);
    char* arguments[] = {"ls", NULL };
    execve("/Users/amouassi/Desktop/minishell_/ls", arguments,environ);
    // execv("/bin", arguments);  
}