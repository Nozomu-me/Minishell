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

typedef enum e_type
{
    WRITE,
    READ,
    APPEND,
    PIPE,
    END
}           t_type;

typedef struct  s_file
{
    char        *filename;
    t_type      filetype;
    struct      s_file *next;
}               t_file;

typedef struct  s_cmds
{
    char        	**cmd;
    t_type      	type;
    t_file      	file;
}               t_cmds;

typedef	struct	s_command
{
	char				*command;
	t_type				type;
	struct s_command	*next;
}				t_command;

/*
typedef struct	s_file
{
	char *filename;
	char *filetype;
	struct s_file *next;
}				t_file;

typedef struct  s_cmds
{
	char **cmd;
	char *type;
	t_file *file;
	struct s_cmds *next;
}               t_cmds;*/

typedef	struct	s_symbol
{
	int	semi;
	int	pipe;
	int	d_quote;
	int	s_quote;
	int	less;
	int	great;
	int	d_great;
	int error;
}				t_symbol;

typedef	struct	s_parse
{
	char		**s_semi;
	char		**s_pipe;
	char		**env;
	char		*check_env;
	t_cmds		*cmds;
	t_symbol	*smbl;
	t_command	*command;
}				t_parse;

void		ft_lstadd_back(t_cmds **alst, t_cmds *new);
t_cmds		*ft_lstnew(char **v_cmd, char *v_type, char *f_name, char *f_type);
void		affichage(char *line, t_cmds *cmds);
t_cmds		*parser(t_cmds *cmds, char *line);

//syntax error
int 	count_back(char *line);
void	ft_error(t_symbol *smbl, char *str, char *first_color, char *second_color);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*partition_stage(t_symbol *smbl, char *line);

/* symbols */
char	*check_d_quote(t_symbol *smbl, char *line, int i);
char	*check_s_quote(t_symbol *smbl, char *line, int i);
char	*check_semicolone(t_symbol *smbl, char *line, int i);
char	*check_pipe(t_symbol *smbl, char *line, int i);
int		redirection(t_symbol *smbl);
char	*check_redirection(t_symbol *smbl, char *line, int i, int *type);
void	off_flags(t_symbol *smbl);

/* command */
char	*check_command(t_parse *parse, char *line);

/*struct*/
t_command	*ft_lstnew_cmd(char *v_cmd, int type);
void		ft_lstadd_back_cmd(t_command **alst, t_command *new);

/* dollar */
char	*dollar(t_parse *parse, char *line);
char	*check_dollr(t_parse *parse, char *line);
# endif
