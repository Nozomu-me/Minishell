#ifndef PARSING_H
#define PARSING_H

# include "libft/libft.h"

# define ERROR 1
# define ON 1
# define OFF 0
# define GREEN	"\e[1;32m"
# define RED	"\e[0;31m"
# define WHITE	"\033[0m"
# define BLUE "\e[0;34m"
# define MINISHELL "\n\e[1;32m$minishel\033[1;34m=>\033[0m"

typedef struct  s_global
{
	char    *oldpwd;
	char    **commands;
	int     exit_status;
}               t_global;

typedef struct	s_file
{
	char *name;
	char *filetype;
	struct s_file *next;
}				t_file;

typedef struct  s_cmds
{
	char **cmd;
	char *type;
	t_file *file;
	struct s_cmds *next;
}               t_cmds;

typedef	struct	s_symbol
{
	int	semi;
	int	pipe;
	int	d_quote;
	int	s_quote;
	int	great;
	int	less;
}				t_symbol;

void		ft_lstadd_back(t_cmds **alst, t_cmds *new);
t_cmds		*ft_lstnew(char **v_cmd, char *v_type, char *f_name, char *f_type);
void		affichage(char *line, t_cmds *cmds);
t_cmds		*parser(t_cmds *cmds, char *line);

//error
void	ft_error(char *str, char *first_color, char *second_color, int *error);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
# endif
