/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 12:09:18 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/26 13:05:44 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    shlvl(t_minishell *mini)
{
    char    *lvl;
    char    *join;
    
    lvl = ft_itoa(mini->glob.shlvl);
    join = ft_strjoin("SHLVL=",lvl);
    // printf("%s\n",lvl);
    if (check_in_env(mini->env, "SHLVL") == 1)
    {
        // printf("here1\n");
        mod_env(mini->env, "SHLVL", join);
    }
    if (check_in_env(mini->export_env, "SHLVL") == 1)
    {
        // printf("here1\n");
        mod_env(mini->export_env, "SHLVL", join);
    }
    free(lvl);
}