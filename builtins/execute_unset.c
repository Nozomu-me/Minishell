/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:16:31 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/19 17:03:50 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute_unset(t_minishell *mini)
{
    int     i;

    i = 1;
    if (mini->cmd[1] == NULL)
        return ;
    while (mini->cmd[i] != NULL)
    {
        delete_node(mini->env,mini->cmd[i]);
        delete_node(mini->export_env,mini->cmd[i]);
        i++;
    }
}