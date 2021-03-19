/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:50:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/19 12:49:19 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int     check_if_unseted(t_list *unset)
{
    t_list      *tmp;
    tmp = unset;
    if (tmp == NULL)
        return (1);
    while (tmp != NULL)
    {
        printf("%s\n", tmp->content);
        tmp = tmp->next;
    }
    return (0);
}

int     check_valid(char *str)
{
    int     i;

    i = 0;
    while(str[i] != '\0')
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}
void    execute_export(t_minishell *mini)
{
    int     i;
    char    **split;

    i = 1;
    // check_if_unseted(mini->unset);
    if (mini->cmd[1] ==  NULL)
    {
        sort_list(mini->export_env);
        print_list(mini->export_env);
    }
    while(mini->cmd[i] != NULL)
    {
        split = ft_split(mini->cmd[i], '=');
        if (check_in_env(mini->export_env, split[0]) == 1 && check_valid(mini->cmd[i]) == 1)
        {
            mod_env(mini->export_env, split[0], mini->cmd[i]);
        }
        if (check_in_env(mini->env, split[0]) == 1 && check_valid(mini->cmd[i]) == 1)
        {
            mod_env(mini->env, split[0], mini->cmd[i]);
        }
        else if (check_in_env(mini->env, split[0]) != 1)
        {
            ft_lstadd_back(&mini->export_env, ft_lstnew(ft_strdup(mini->cmd[i])));
        }
        free_tab(split);
        i++;
    }
}