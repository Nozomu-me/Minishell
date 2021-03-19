#include "minishell.h"

t_list   *init_env(char **environ)
{
    t_list   *env;
    int     i;

    i = 1;
    env = ft_lstnew(strdup(environ[0]));
    while(environ[i] != NULL)
    {
        // if (strncmp(environ[i], "OLDPWD", 6) != 0)
            ft_lstadd_back(&env, ft_lstnew(strdup(environ[i])));
        i++;
    }
    return (env);
}

void    mod_env(t_list *env, char *name,char *var)
{
    t_list  *tmp;

    tmp = env;
    while (env != NULL)
    {
        if (strncmp(env->content, name, strlen(name)) == 0)
        {
            free(env->content);
            env->content = strdup(var);
            printf("mod_env=%s\n",env->content);
        }
        env = env->next;
    }
}
void    print_list(t_list *env)
{
    t_list *tmp;

    tmp = env;
    while (tmp != NULL)
    {
        printf("%s\n",tmp->content);
        tmp = tmp->next;
    }
}

char **ft_getenv(char *name, t_list *env)
{
    char **find;
    t_list *tmp;

    tmp = env;
    if (name == NULL || env == NULL)
		return (NULL);
    while(tmp != NULL)
    {
        find = ft_split(tmp->content, '=');
        if (strcmp(find[0], name) == 0)
        {
            return (find);
        }
        // free_tab(find);
        tmp = tmp->next;
    }
    return (NULL);
}

int    check_in_env(t_list *env)
{
    t_list     *tmp;

    tmp = env;
    while (tmp != NULL)
    {
        if (strncmp(tmp->content, "OLDPWD", 6) == 0)
            return (1);
        tmp = tmp->next;
    }
    return (0);
    
}

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
int main()
{
    extern char **environ;
    t_list *env;
    env = init_env(environ);
    // print_list(env);
    // mod_env(env, "PWD","PWD=AMAL");
    // printf("\n----------------------------------------------------------------\n");
    // print_list(env);
    // ft_lstclear(&env,free);
    mod_oldpwd(env);
    print_list(env);

    // char **str;

    // str = ft_getenv("PWD",env);
    // printf("%s\n", str[1]);
}



// void    mod_oldpwd(t_list *env)
// {
//     char    cwd[PATH_MAX];
//     char    *oldpwd;
    
//     getcwd(cwd, PATH_MAX);
//     oldpwd = ft_strjoin("OLDPWD=", cwd);
//     if (check_in_env(env) == 0)
//         ft_lstadd_back(&env, ft_lstnew(oldpwd));
//     else
//         mod_env(env, "OLDPWD", oldpwd);
// }
// char    *get_path(t_list *env, int b)
// {
//     char    **path;
//     char    cwd[PATH_MAX];

//     path = NULL;
//     if (b == 0)
//     {
//         mod_oldpwd(env);
//         path = ft_getenv("HOME",env);
//         if (path == NULL)
//         {
//             ft_putstr("minishell: cd: HOME not set\n");
//             exit_status = 1;
//             return (NULL);
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
//         mod_oldpwd(env);
//     }
//     free(path[0]);
//     return (path[1]);
// }
// void    execute_cd(char **cmd, t_list *env)
// {
//     char    *path;
//     char    *tmp_path;
//     int     check_dir;
// 	char	cwd[PATH_MAX];

//     // ft_putstr("in cd\n");
//     if (cmd[1] == NULL)
//     {
//         path = get_path(env, 0);
//         // ft_putstr("here\n");
//         // printf("path=%s\n",path);
//         check_dir = chdir(path);
//     }
//     else if (ft_strcmp(cmd[1], "~") == 0)
//     {
//         path = get_path(env, 0);
//         mod_oldpwd(env);
//         tmp_path = search_replace(cmd[1], "~", path);
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
//         mod_oldpwd(env);
//         if (path != NULL)
//         {
//             check_dir = chdir(path);
//             if (check_dir == -1)
//             {
//                 error_cd(path, errno);
//                 exit_status = errno;
//             }
//         }
//     }
//     else
//     {
//         getcwd(cwd, PATH_MAX);
//         mod_oldpwd(env);
//         check_dir = chdir(cmd[1]);
// 		if (check_dir == -1)
//         {
// 			error_cd(cmd[1], errno);
//             exit_status = errno;
//         }
//     }
// }