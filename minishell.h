/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:29:11 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/27 17:11:51 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#define PATH_MAX = 1024
#define BUFFER_SIZE 1024

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
#include <sys/stat.h>
int status;
int	shell_level;

typedef struct	s_global
{
	int			exit_status;
	int			mini_ret;
	int			b_exit;
	char		**home;
	char		*oldpwd;
	t_list		*commands;
	int			oldpwd_env;
	char		*pwd;
	int			shlvl;
}				t_global;

typedef struct s_file
{
    char		*name;
    char		*filetype;
    struct		s_file *next;
}t_file;

typedef struct s_cmds
{
    char		**cmd;
    char		type;
    t_file		filename;
}t_cmds;

typedef struct      s_minishell
{
	t_cmds			*cmds;
    t_list			*env;
	t_list			*export_env;
	t_list			*unset;
	t_global 		glob;
}                   t_minishell;
/*
** utils
*/
char			*ft_strndup(char *s, size_t len);
void			ft_putstr(char *s);
char			*ft_strncpy(char *str, int n);
int				ft_maxlen(char *s1, char *s2);
int     		check_isnumeriq(char *str);
int   			check_spec_char(char *str);
int     		check_syntax_export(char *cmd);
int     		check_syntax_unset(char *cmd);
void			free_tab(char **s);
int				ft_strcmp(char *s1, char *s2);
void			ft_sort_tab(char **tab);
char			*search_replace(char *str, char *org, char *rep);
int				ft_sort_str(char *s1, char *s2);
void			free_tab(char **s);
/*
** list utils
*/
void			sort_list(t_list *list);
void            print_list(t_list *list);
t_list          *init_list();
void            delete_node(t_list *list, char *name);
char    		**list_to_tab(t_list *list);
/*
** execute cmd
*/
void          	sig_handler(int sig);
char            **init_cmd(char *cmd);
void			execute_cmd(t_minishell *mini);
void 		    execute_shell(t_minishell *mini);
void    		shlvl(t_minishell *mini);
/*
** execute builtins
*/
void			execute_builtins(t_minishell *mini);
int				check_isbuiltin(char *cmd);
void			execute_cd(t_minishell *mini);
void    		execute_echo(char **cmd, t_minishell *mini);
void            execute_env(t_minishell *mini);
void    		execute_exit(t_minishell *mini);
void            execute_export(t_minishell *mini);
void    		execute_pwd(t_minishell *mini);
void            execute_unset(t_minishell *mini);
/*
** error functions
*/
void   			error_pwd(char  *str, int err);
void			error_export(char *str, t_minishell *mini);
void            error_cd(char *path, int err);
void			error_unset(char *str, t_minishell *mini);
void			error_exit(char *str);
/*
** environ functions
*/
void            mod_env(t_list *env, char *name,char *var);
int             check_in_env(t_list *env, char *str);
t_list          *init_env_environ(char **environ);
t_list          *init_export_environ(char **environ);
char			**ft_getenv(char *name, t_list *env);
#endif