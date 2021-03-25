/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:33:48 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/25 11:13:46 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    help_execute_exit(t_minishell *mini)
{
    long long     status;

    status = ft_atoi(mini->cmd[1]);
    if (status > 255)
    {
        mini->glob.exit_status = status % 256;
        mini->glob.mini_ret = status % 256;
    }
    else
    {
        if (status == -1)
            error_exit(mini->cmd[1]);
        mini->glob.exit_status = status;
        mini->glob.mini_ret = status;
    }
    ft_putstr("exit\n");
    mini->glob.b_exit = 1;
}

void    execute_exit(t_minishell *mini)
{
    if (mini->cmd[1] == NULL)
    {
        mini->glob.exit_status = 0;
        mini->glob.mini_ret = 0;
        ft_putstr("exit\n");
        mini->glob.b_exit = 1;
    }
    else
    {
        if (check_isnumeriq(mini->cmd[1]) == 0 && mini->cmd[2] == NULL)
            help_execute_exit(mini);
        else
        {
            if (check_isnumeriq(mini->cmd[1]) == 0 && mini->cmd[2] != NULL)
                ft_putstr("exit\nminishell: exit: too many arguments\n");
            else
            {
                mini->glob.exit_status = 255;
                mini->glob.mini_ret = 255;
                error_exit(mini->cmd[1]);
                mini->glob.b_exit = 1;
            }
            
        }
    }
}