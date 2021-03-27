/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 12:09:18 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/27 17:09:45 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    shlvl(t_minishell *mini)
{
    int     lvl;
    char    *join;
    char    **shlvl_env;
    
    if (check_in_env(mini->env, "SHLVL") == 1 &&
    check_in_env(mini->export_env, "SHLVL") == 1)
    {
        lvl = 1;
        shlvl_env = ft_getenv("SHLVL", mini->export_env);
        lvl += ft_atoi(shlvl_env[1]);
        join = ft_strjoin("SHLVL=", ft_itoa(lvl));
        mod_env(mini->env, "SHLVL", join);
        mod_env(mini->export_env, "SHLVL", join);
        free_tab(shlvl_env);
    }
    if (check_in_env(mini->export_env, "SHLVL") == 0)
    {
        ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup("SHLVL=1")));
        ft_lstadd_back(&mini->export_env, ft_lstnew(ft_strdup("SHLVL=1")));
    }
}