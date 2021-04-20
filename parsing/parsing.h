/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 10:56:23 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/20 14:02:59 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>

# define ERROR 1
# define ON 1
# define OFF 0
# define GREEN	"\e[1;32m"
# define RED	"\e[0;31m"
# define WHITE	"\033[0m"
# define BLUE "\e[0;34m"
# define MINISHELL "\n\e[1;32m$minishel\033[1;34m=>\033[0m"

/////////////////////////
typedef	struct s_env
{
	char		*name;
	char		*value;
	struct s_env *next;
}				t_env;

////////////

// typedef struct s_global
// {
// 	char	*oldpwd;
// 	char	**f_cmds;
// 	int		exit_status;
// }				t_global;

// typedef enum e_type
// {
// 	WRITE,
// 	READ,
// 	APPEND,
// 	PIPE,
// 	END
// }				t_type;

// typedef struct s_file
// {
// 	char			*filename;
// 	t_type			filetype;
// 	struct s_file	*next;
// }					t_file;

// typedef struct s_cmds
// {
// 	char		**args;
// 	t_type		type;
// 	t_file		*file;
// }				t_cmds;

// typedef struct s_f_cmd
// {
// 	char			*cmd;
// 	t_type			type;
// 	struct s_f_cmd	*next;
// }					t_cflist;

// typedef struct s_symbol
// {
// 	int	semi;
// 	int	pipe;
// 	int	d_quote;
// 	int	s_quote;
// 	int	less;
// 	int	great;
// 	int	d_great;
// 	int	error;
// 	int already_pipe;
// }					t_symbol;

// typedef struct s_parse
// {
// 	char			**s_semi;
// 	char			**s_pipe;
// 	char			**split;
// 	char			**env;
// 	char			*check_env;
// 	char			*under_score;

// 	int				cp;
// 	int				src_i;
// 	int				src_count;
// 	int				src_len1;
// 	int				src_len2;
// 	char			*src_new;
// 	char			*new;
// 	char			*file_nme;
// 	t_cmds			*cmds;
// 	t_symbol		*smbl;
// 	t_cflist		*f_cmd;
// 	t_env			*env2;
// }					t_parse;

// void		affichage(char *line, t_cmds *cmds);
// t_cmds		*parser(t_cmds *cmds, char *line);

//syntax error
// void		error_red(t_symbol *smbl, char *error, char c);
// int			count_back(char *line);
// void		ft_error(t_symbol *smbl, char *str);
// void		ft_putstr_fd(char *s, int fd);
// void		ft_putendl_fd(char *s, int fd);
// char		*partition_stage(t_symbol *smbl, char *line);
// char		*check_space(t_symbol *smbl, char *line, int i);

// /* symbols */
// void		initial_symbol(t_symbol *sbl);
// char		*check_symbols(t_symbol *smbl, char *line, int i);
// char		*check_d_quote(t_symbol *smbl, char *line, int i);
// char		*check_s_quote(t_symbol *smbl, char *line, int i);
// char		*check_semicolone(t_symbol *smbl, char *line, int i);
// char		*check_semi_off(t_symbol *smbl, char *line, int i);
// char		*check_pipe_off(t_symbol *smbl, char *line, int i);
// char		*check_pipe(t_symbol *smbl, char *line, int i);
// int			redirection(t_symbol *smbl);
// char		*check_redirection(t_symbol *smbl, char *line, int i, int *type);
// int			check_flags(t_symbol *smbl);
// void		off_flags(t_symbol *smbl);

// /* command */
// char		*reverse_cmd(t_parse *parse, char *line, int i, int j);
// char		*ft_substr2(char *s, unsigned int start, size_t len);
// void		push_to_struct(t_parse *parse, char *line);
// int			compare(char *str, char *str2);

// /*struct*/
// void		file_lstadd_back(t_file **alst, t_file *new);
// t_file		*file_lst_new(void *filename, int filetype);
// // t_cmds		*ft_lstnew(char **v_cmd, int v_type, char *f_name, int f_type);
// // t_cflist		*lstnew_cmd(char *v_cmd, int type);
// // void		lstadd_cmd(t_cflist **alst, t_cflist *new);

// /* free struct */
// void		free_cmds_struct(t_parse *cmds);
// void		ft_free_tab(char **s);
// void		ft_free(t_parse *parse);

// /* dollar */
// char		*dollar(t_parse *parse, char *line);
// char		*check_dollr(t_parse *parse, char *line);
// char		*ft_turn_dollar(t_symbol *smbl, char *line, int i);

// /*redirection */
// char		*sort_redirection(char *line);
// int			redirection(t_symbol *smbl);
// char		*check_redirection(t_symbol *smbl, char *line, int i, int *type);

// char		*search_replace(t_parse *parse, char *str, char *org, char *rep);
#endif
