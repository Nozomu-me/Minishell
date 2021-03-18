/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:50:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/18 22:11:00 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute_export(char **cmd, t_list *env, t_list *export_env)
{
    int     i;
    char    **split;

    i = 1;
    if (cmd[1] ==  NULL)
    {
        sort_list(export_env);
        print_list(export_env);
    }
    while(cmd[i] != NULL)
    {
        split = ft_split(cmd[i], '=');
        if (check_in_env(export_env, split[0]) == 1)
            mod_env(export_env, split[0], cmd[i]);
        if (check_in_env(env, split[0]) == 1)
            mod_env(env, split[0], cmd[i]);
        else
            ft_lstadd_back(&export_env, ft_lstnew(ft_strdup(cmd[i])));
        free_tab(split);
        i++;
    }
}
