/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 13:33:48 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/21 17:39:41 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute_exit(t_minishell *mini)
{
    int     status;

    if (mini->cmd[1] == NULL)
    {
        exit_status = 0;
        mini_ret = 0;
        ft_putstr("exit\n");
        b_exit = 1;
    }
    else
    {
        if (check_isnumeriq(mini->cmd[1]) == 0 && mini->cmd[2] == NULL)
        {
            status = ft_atoi(mini->cmd[1]);
            if (status > 255)
            {
                exit_status = status % 256;
                mini_ret = status % 256;
            }
            else
            {
                exit_status = status;
                mini_ret = status;
            }
            ft_putstr("exit\n");
            b_exit = 1;
        }
        else
        {
            if (check_isnumeriq(mini->cmd[1]) == 0 && mini->cmd[2] != NULL)
                ft_putstr("exit\nminishell: exit: too many arguments\n");
            else
            {
                exit_status = 255;
                mini_ret = 255;
                ft_putstr("exit\nminishell: exit: ");
                ft_putstr(mini->cmd[1]);
                ft_putstr(": numeric argument required\n");
                b_exit = 1;
            }
            
        }
    }
    // printf("%d\n",b_exit);
}