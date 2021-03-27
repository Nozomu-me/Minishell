/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:48:36 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/27 13:38:16 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void    execute_env(t_minishell *mini)
{
    if (mini->cmds->cmd[1] != NULL && ft_strcmp(mini->cmds->cmd[1], "#") != 0)
    {
        if(strcmp(mini->cmds->cmd[1],"=") == 0 || strcmp(mini->cmds->cmd[1], "==") == 0)
        {
            printf("env: setenv %s: Invalid argument\n", mini->cmds->cmd[1]);
            mini->glob.exit_status = 1;
        }
        else
        {
            ft_putstr("env: ");
            ft_putstr(mini->cmds->cmd[1]);
            ft_putendl_fd(": No such file or directory", 1);
            mini->glob.exit_status = 127;
        }
    }
    else
        print_list(mini->env);
}