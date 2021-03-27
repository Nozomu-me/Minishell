/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:50:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/27 13:39:09 by amouassi         ###   ########.fr       */
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
char    *get_export_value(char *name)
{
    int     i;
    char    *value;
    i = 0;
    while (name[i] != '\0')
    {
        if (name[i] == '=')
            break ;
        i++;
    }
    value = ft_substr(name, i + 1, ft_strlen(name) - i);
    return (value);
}
void    print_export(t_list *export)
{
    t_list      *tmp;
    char        **split;
    char        *value;

    tmp = export;
    while(tmp != NULL)
    {
        split = ft_split(tmp->content, '=');
        ft_putstr("declare -x ");
        ft_putstr(split[0]);
        if (check_valid(tmp->content) == 1)
        {
            ft_putstr("=\"");
            value = get_export_value(tmp->content);
            ft_putstr(value);
            ft_putstr("\"\n");
            free(value);
        }
        else
            ft_putchar_fd('\n', 1);
        tmp = tmp->next;
        free_tab(split);
    }
}

void    help_execute_export(t_minishell *mini, char *cmd)
{
    char    **split;
    char    *lvl;
    char    *join;
    
    split = ft_split(cmd, '=');
    lvl = ft_itoa(mini->glob.shlvl);
    join = ft_strjoin("SHLVL=",lvl);
    // printf("%s\n",mini->glob.oldpwd);
    if (ft_strncmp(cmd, "SHLVL", 5) == 0)
    {
        if (check_in_env(mini->env, split[0]) == 0)
        {
            ft_lstadd_back(&mini->env, ft_lstnew(ft_strjoin("SHLVL=",lvl)));
            ft_lstadd_back(&mini->export_env, ft_lstnew(ft_strjoin("SHLVL=",lvl)));
        }
        else
        {
            mod_env(mini->export_env, "SHLVL", join);
            mod_env(mini->env, "SHLVL", join);
        }
    }
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
    if (mini->cmds->cmd[1] ==  NULL)
    {
        sort_list(mini->export_env);
        print_export(mini->export_env);
    }
    while(mini->cmds->cmd[i] != NULL)
    {
        if (check_syntax_export(mini->cmds->cmd[i]) == 1)
            error_export(mini->cmds->cmd[i], mini);
        else
            help_execute_export(mini, mini->cmds->cmd[i]);
        i++;
    }
}