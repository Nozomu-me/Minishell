/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:50:42 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/04 14:34:24 by amouassi         ###   ########.fr       */
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

typedef struct			s_export
{
	char				*var;
	struct s_export		*next;
}						t_export;

typedef struct			s_builtins
{
	char		*cd_path;
	char		**env;
	t_export	*export;
}						t_builtins;

char			*ft_strndup(char *s, size_t len);
void			ft_putstr(char *s);
char			*ft_strncpy(char *str, int n);
int				ft_maxlen(char *s1, char *s2);
char			*ft_strfcpy(char *str, int n);
void			free_tab(char **s);
int				ft_strcmp(char *s1, char *s2);
void			ft_sort_tab(char **tab);
char			*search_replace(char *str, char *org, char *rep);
char			**set_environ(char **environ);
char			**ft_getenv(char *name, char **env);
void			modify_env(char **environ, char *name,char *var);
void			init_builtins(t_builtins *builtins, char **env);
void			free_builtins(t_builtins *builtins);
void			error_pwd(char  *str, int err);
void 			execute_pwd();
void			error_cd(char *path, int err);
void			parse_cd(char *line, t_builtins *builtins);
void    		execute_cd(t_builtins *builtins);
void			parse_env(char *line, t_builtins *builtins);
void			execute_env(t_builtins *builtins, char **split, int i);
void			parse_export_unset(char *line, t_builtins *builtins);
void			execute_export(t_builtins *builtins, int b);
t_export		*ft_lstnew();
void			ft_lstadd_back(t_export **alst, t_export *new);
int				ft_lstsize(t_export *lst);
void    		print_export(t_builtins *builtins);
void			sort_list(t_export *export);
void    		print_list(t_export *export);
int				ft_sort_str(char *s1, char *s2);
void			error_export(char *str);
void			parse_export(char *line, t_builtins *builtins);
void			ft_lstclear(t_export *lst);
void			ft_lstdelone(t_export *lst);
int     		check_caract(char *str, char c);

#endif