/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:29:11 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/16 19:44:31 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#define PATH_MAX = 1024
#define BUFFER_SIZE 1024
#define USERS "/Users"

#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <time.h> 
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "libft/libft.h"
#include "gnl/get_next_line.h"

int exit_status;
// typedef struct			s_builtins
// {
// 	char		*cd_path;
// 	char		**env;
// 	t_list      *list;
// }						t_builtins;
typedef struct s_env
{
	char	*value;
    struct s_env    *next;
}t_env;
typedef enum e_type
{
    WRITE,
    READ,
    APPEND,
    PIPE,
    END
}t_type;

typedef struct s_info
{
    char *oldpwd;
    int error_return;
    char *latest_command;
}t_info;

typedef struct s_file
{
    char *name;
    t_type type;
    struct s_file *next;
}t_file;

typedef struct s_cmd
{
    t_list *args;
    t_file  *files;
    t_type type;
}t_cmd;

char			*ft_strndup(char *s, size_t len);
void			ft_putstr(char *s);
char			*ft_strncpy(char *str, int n);
int				ft_maxlen(char *s1, char *s2);
void			free_tab(char **s);
int				ft_strcmp(char *s1, char *s2);
void			ft_sort_tab(char **tab);
char			*search_replace(char *str, char *org, char *rep);
// char			**set_environ(char **environ);
// char			**ft_getenv(char *name, char **env);
// void			modify_env(char **environ, char *name,char *var);
void			sort_list(t_list *list);
int				ft_sort_str(char *s1, char *s2);
void          	sig_handler(int sig);
void			free_tab(char **s);

char            **init_cmd(char *cmd);
void			execute_cmd(char **cmd, t_list *env);
/*
** execute builtins
*/
void			execute_builtins(char **cmd, t_list *env);
int				check_isbuiltin(char *cmd);
void    		execute_pwd();
void			execute_cd(char **cmd, t_list *env);
/*
** error functions
*/
void   			error_pwd(char  *str, int err);
void            error_cd(char *path, int err);
/*
** environ functions
*/
void            mod_env(t_list *env, char *name,char *var);
int             check_in_env(t_list *env);
t_list          *init_environ(char **environ);
char			**ft_getenv(char *name, t_list *env);

#endif