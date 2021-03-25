/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:50:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/25 18:53:52 by amouassi         ###   ########.fr       */
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
            ft_putstr("\n");
        tmp = tmp->next;
        free_tab(split);
    }
}

void    help_execute_export(t_minishell *mini, char *cmd)
{
    char    **split;
    
    split = ft_split(cmd, '=');
    // printf("%s\n",mini->glob.oldpwd);
    if (ft_strncmp(cmd, "OLDPWD", 6) == 0)
    {
        // printf("here2\n");
        if (mini->glob.oldpwd != NULL && check_in_env(mini->env, split[0]) == 0)
            ft_lstadd_back(&mini->env, ft_lstnew(ft_strjoin("OLDPWD=",mini->glob.oldpwd)));
        mini->glob.oldpwd_env = 0;
    }
    if (ft_strncmp(cmd, "OLDPWD", 6) == 0 &&  mini->glob.oldpwd != NULL)
    {
        // printf("here1\n");
        if (mini->glob.oldpwd != NULL && check_in_env(mini->export_env, split[0]) == 0)
            ft_lstadd_back(&mini->export_env, ft_lstnew(ft_strjoin("OLDPWD=", mini->glob.oldpwd)));
        mini->glob.oldpwd_env = 0;
    }
    if (check_in_env(mini->export_env, split[0]) == 1 && check_valid(cmd) == 1)
    {
        // printf("here3\n");
        mod_env(mini->export_env, split[0], cmd);
    }
    else if (check_in_env(mini->export_env, split[0]) != 1)
    {
        // printf("here5\n");
        ft_lstadd_back(&mini->export_env, ft_lstnew(ft_strdup(cmd)));
    }
    if (check_in_env(mini->env, split[0]) == 1 && check_valid(cmd) == 1)
    {
        // printf("here4\n");
        mod_env(mini->env, split[0], cmd);
    }
    else if (check_in_env(mini->env, split[0]) != 1 && check_valid(cmd) == 1)
    {
        // printf("here6\n");
        ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(cmd)));
    }
    free_tab(split);
}

void    execute_export(t_minishell *mini)
{
    int     i;

    i = 1;
    if (mini->cmd[1] ==  NULL)
    {
        sort_list(mini->export_env);
        print_export(mini->export_env);
    }
    while(mini->cmd[i] != NULL)
    {
        if (check_syntax_export(mini->cmd[i]) == 1)
            error_export(mini->cmd[i], mini);
        else
            help_execute_export(mini, mini->cmd[i]);
        i++;
    }
}