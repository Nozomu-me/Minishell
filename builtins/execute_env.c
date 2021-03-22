/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:48:36 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/22 16:45:21 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void    execute_env(t_minishell *mini)
{
    if (mini->cmd[1] != NULL && ft_strcmp(mini->cmd[1], "#") != 0)
    {
        ft_putstr("env: ");
        ft_putstr(mini->cmd[1]);
        ft_putendl_fd(": No such file or directory", 1);
    }
    else
        print_list(mini->env);
}