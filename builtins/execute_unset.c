/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:16:31 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/27 13:39:25 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute_unset(t_minishell *mini)
{
    int     i;

    i = 1;
    if (mini->cmds->cmd[1] == NULL)
        return ;
    while (mini->cmds->cmd[i] != NULL)
    {
        if (ft_strncmp(mini->cmds->cmd[i], "OLDPWD", 6) == 0)
        {
            mini->glob.oldpwd = NULL;
            mini->glob.oldpwd_env = 1;
        }
        if (ft_strncmp(mini->cmds->cmd[i], "SHLVL", 5) == 0)
            mini->glob.shlvl = 1;
        if (check_syntax_unset(mini->cmds->cmd[i]) == 1)
            error_unset(mini->cmds->cmd[i], mini);
        else
        {
            delete_node(mini->env,mini->cmds->cmd[i]);
            delete_node(mini->export_env,mini->cmds->cmd[i]);
        }
        i++;
    }
}