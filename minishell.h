/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:29:11 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/21 15:00:11 by amouassi         ###   ########.fr       */
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

int exit_status;
int mini_ret;
int b_exit;
typedef struct      s_minishell
{
    t_list	*env;
	t_list	*export_env;
	t_list	*unset;
	char	**cmd;
}                   t_minishell;
/*
** utils
*/
char			*ft_strndup(char *s, size_t len);
void			ft_putstr(char *s);
char			*ft_strncpy(char *str, int n);
int				ft_maxlen(char *s1, char *s2);
int     		check_isnumeriq(char *str);
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
/*
** execute builtins
*/
void			execute_builtins(t_minishell *mini);
int				check_isbuiltin(char *cmd);
void    		execute_pwd();
void			execute_cd(t_minishell *mini);
void            execute_env(t_minishell *mini);
void            execute_export(t_minishell *mini);
void            execute_unset(t_minishell *mini);
void			execute_echo(char **cmd);
void    		execute_exit(t_minishell *mini);
/*
** error functions
*/
void   			error_pwd(char  *str, int err);
void            error_cd(char *path, int err);
/*
** environ functions
*/
void            mod_env(t_list *env, char *name,char *var);
int             check_in_env(t_list *env, char *str);
t_list          *init_environ(char **environ);
char			**ft_getenv(char *name, t_list *env);
#endif