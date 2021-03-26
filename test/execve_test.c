/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 10:27:46 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/26 13:03:01 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char *argv[])
{
    extern char **environ;
    char* file=argv[1];
    // char *path;
    // path = getenv("PATH");
    // printf("hello\n");
    char* arguments[] = {"/minishell", NULL };
    execve("../minishell", arguments,environ);
    
    // execv("/bin", arguments);  
}