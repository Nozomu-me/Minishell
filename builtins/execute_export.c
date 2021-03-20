/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:50:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/20 15:36:42 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void    print_export(t_list *export)
{
    t_list      *tmp;
    char        **split;
    
    tmp = export;
    while(tmp != NULL)
    {
        split = ft_split(tmp->content, '=');
        ft_putstr("declare -x ");
        ft_putstr(split[0]);
        if (split[1] != NULL)
        {
            ft_putstr("=");
            if (split[1][0] != '\"')
                ft_putstr("\"");
            ft_putstr(split[1]);
            if (split[1][0] != '\"')
                ft_putstr("\"");
            ft_putstr("\n");
        }
        else
        {
            ft_putstr("\n");
        }
        tmp = tmp->next;
        free_tab(split);
    }
}

void    execute_export(t_minishell *mini)
{
    int     i;
    char    **split;

    i = 1;
    if (mini->cmd[1] ==  NULL)
    {
        sort_list(mini->export_env);
        print_export(mini->export_env);
    }
    while(mini->cmd[i] != NULL)
    {
        split = ft_split(mini->cmd[i], '=');
        if (check_in_env(mini->export_env, split[0]) == 1 && check_valid(mini->cmd[i]) == 1)
            mod_env(mini->export_env, split[0], mini->cmd[i]);
        if (check_in_env(mini->env, split[0]) == 1 && check_valid(mini->cmd[i]) == 1)
            mod_env(mini->env, split[0], mini->cmd[i]);
        else if (check_in_env(mini->export_env, split[0]) != 1)
            ft_lstadd_back(&mini->export_env, ft_lstnew(ft_strdup(mini->cmd[i])));
        else if (check_in_env(mini->env, split[0]) != 1 && check_valid(mini->cmd[i]) == 1)
            ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(mini->cmd[i])));
        free_tab(split);
        i++;
    }
}