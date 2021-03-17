/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:46:17 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/16 22:19:34 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char    **get_path(char **env, int b)
// {
//     char    **path;
//     char    cwd[PATH_MAX];

//     path = NULL;
//     if (b == 0)
//     {
//         getcwd(cwd, PATH_MAX);
//         modify_env(env, "OLDPWD", cwd);
//         path = ft_getenv("HOME",env);
//         if (path == NULL)
//         {
//             ft_putstr("minishell: cd: HOME not set");
//             exit_status = 1;
//             return (path);
//         }
//     }
//     else if (b == 1)
//     {
//         path = ft_getenv("OLDPWD",env);
// 		if (path == NULL)
//         {
// 			ft_putstr("minishell : cd: OLDPWD not set\n");
//             exit_status = 1;
//             return (NULL);
//         }
//         printf("%s\n", path[1]);
//         getcwd(cwd, PATH_MAX);
//         modify_env(env, "OLDPWD", cwd);
//     }
//     return (path);
// }
// void    execute_cd(char **cmd, char **env)
// {
//     char    **path;
//     char    *tmp_path;
//     int     check_dir;
// 	char	cwd[PATH_MAX];

//     if (cmd[1] == NULL)
//     {
//         path = get_path(env, 0);
//         check_dir = chdir(path[1]);
// 		if (check_dir == -1)
//         {
// 			error_cd(path[1], errno);
//             exit_status = errno;
//         }
//     }
//     else if (ft_strcmp(cmd[1], "~") == 0)
//     {
//         path = get_path(env, 0);
//         tmp_path = search_replace(cmd[1], "~", path[1]);
//         check_dir = chdir(tmp_path);
// 		if (check_dir == -1)
//         {
// 			error_cd(tmp_path, errno);
//             exit_status = errno;
//         }
//     }
//     else if (ft_strcmp(cmd[1], "-") == 0)
//     {
//         path = get_path(env, 1);
//         if (path != NULL)
//         {
//             check_dir = chdir(path[1]);
//             if (check_dir == -1)
//             {
//                 error_cd(path[1], errno);
//                 exit_status = errno;
//             }
//         }
//     }
//     else
//     {
//         getcwd(cwd, PATH_MAX);
//         modify_env(env, "OLDPWD", cwd);
//         check_dir = chdir(cmd[1]);
// 		if (check_dir == -1)
//         {
// 			error_cd(cmd[1], errno);
//             exit_status = errno;
//         }
//     }
// }


void    mod_oldpwd(t_list *env)
{
    char    cwd[PATH_MAX];
    char    *oldpwd;
    
    getcwd(cwd, PATH_MAX);
    oldpwd = ft_strjoin("OLDPWD=", cwd);
    if (check_in_env(env) == 0)
        ft_lstadd_back(&env, ft_lstnew(oldpwd));
    else
        mod_env(env, "OLDPWD", oldpwd);
}
char    *get_path(t_list *env, int b)
{
    char    **path;
    char    cwd[PATH_MAX];

    path = NULL;
    if (b == 0)
    {
        mod_oldpwd(env);
        path = ft_getenv("HOME",env);
        if (path == NULL)
        {
            ft_putstr("minishell: cd: HOME not set\n");
            exit_status = 1;
            return (NULL);
        }
    }
    else if (b == 1)
    {
        path = ft_getenv("OLDPWD",env);
		if (path == NULL)
        {
			ft_putstr("minishell : cd: OLDPWD not set\n");
            exit_status = 1;
            return (NULL);
        }
        printf("%s\n", path[1]);
        mod_oldpwd(env);
    }
    free(path[0]);
    return (path[1]);
}
void    execute_cd(char **cmd, t_list *env)
{
    char    *path;
    char    *tmp_path;
    int     check_dir;
	char	cwd[PATH_MAX];

    if (cmd[1] == NULL)
    {
        path = get_path(env, 0);
        check_dir = chdir(path);
    }
    else if (ft_strcmp(cmd[1], "~") == 0)
    {
        path = get_path(env, 0);
        mod_oldpwd(env);
        tmp_path = search_replace(cmd[1], "~", path);
        check_dir = chdir(tmp_path);
		if (check_dir == -1)
        {
			error_cd(tmp_path, errno);
            exit_status = errno;
        }
    }
    else if (ft_strcmp(cmd[1], "-") == 0)
    {
        path = get_path(env, 1);
        if (path != NULL)
        {
            check_dir = chdir(path);
            if (check_dir == -1)
            {
                error_cd(path, errno);
                exit_status = errno;
            }
        }
    }
    else
    {
        mod_oldpwd(env);
        check_dir = chdir(cmd[1]);
		if (check_dir == -1)
        {
			error_cd(cmd[1], errno);
            exit_status = errno;
        }
    }
}