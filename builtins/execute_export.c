/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:50:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/18 12:56:34 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute_export(char **cmd, t_list *env, t_list *my_env)
{
    int     i;

    i = 0;
    while(cmd[i] != NULL)
    {
        // ft_lstclear(&my_env, free);
        ft_lstadd_back(&my_env, ft_lstnew(ft_strdup(cmd[i])));
        // printf("%s\n", cmd[i]);
        i++;
    }
    print_list(my_env);
}