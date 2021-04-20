/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_shell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:45:39 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/20 11:46:05 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     check_permission(char *path)
{
    struct stat     buf;
    int             status;

    status = stat(path, &buf);
    if(status == 0)
    {
        if ((buf.st_mode & S_IXUSR) != 0)
            return (1);
        else
            return (2);
    }
    else
        return(3);
}

void    get_path(t_mini *mini, char **split, char **path, int *perm, char *tmp)
{
    int     i;

    i = 0;
    while (split[i] != NULL)
    {
        tmp = ft_strjoin(split[i],"/");
        if (mini->cmds.cmd[0] != NULL)
            *path = ft_strjoin(tmp, mini->cmds.cmd[0]);
        *perm = check_permission(*path);
        if (*perm == 1)
        {
            free(tmp);
            break;
        }
        free(tmp);
        if (*path != NULL)
        {
            free(*path);
            *path = NULL;
        }
        i++;
    }
}