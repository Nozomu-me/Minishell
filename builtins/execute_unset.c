/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:16:31 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/19 12:58:45 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute_unset(t_minishell *mini)
{
    int     i;
    char    *join;

    i = 1;
    if (mini->cmd[1] == NULL)
        return ;
    while (mini->cmd[i] != NULL)
    {
        join = ft_strjoin(mini->cmd[i], "=");
        if (check_in_env(mini->env, join) == 1)
        {
            ft_lstadd_back(&mini->unset, ft_lstnew(ft_strdup(mini->cmd[i])));
        }
        delete_node(mini->env,mini->cmd[i]);
        delete_node(mini->export_env,mini->cmd[i]);
        i++;
    }
    print_list(mini->unset);
}