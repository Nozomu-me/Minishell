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
    t_file      	*file;
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
}               t_cmds;
*/

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

typedef	struct	s_ready_to_push
{
	char	*cmd;
	struct s_ready_to_push	*next;
}				t_ready_to_push;

typedef	struct	s_parse
{
	char			**s_semi;
	char			**s_pipe;
	char			**env;
	char			*check_env;
	char			*under_score;
	int 			already_pipe;
	t_cmds			*cmds;
	t_symbol		*smbl;
	t_command		*command;
	t_ready_to_push	*ready_p;
}				t_parse;

void		affichage(char *line, t_cmds *cmds);
t_cmds		*parser(t_cmds *cmds, char *line);

//syntax error
int 	count_back(char *line);
void	ft_error(t_symbol *smbl, char *str, char *first_color, char *second_color);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*partition_stage(t_symbol *smbl, char *line);
char	*check_space(t_symbol *smbl, char *line, int i);

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
char	*ft_substr2(char *s, unsigned int start, size_t len);
void	push_to_struct(t_parse *parse, char *line);

/*struct*/
void    			file_lstadd_back(t_file **alst, t_file *new);
t_file  			*file_lst_new(void *filename, int filetype);
t_cmds				*ft_lstnew(char **v_cmd, int v_type, char *f_name, int f_type);
t_command			*ft_lstnew_cmd(char *v_cmd, int type);
void				ft_lstadd_back_cmd(t_command **alst, t_command *new);
t_ready_to_push		*ft_lstnew_cmd_to_push(char *new_cmd);
void				ft_lstadd_back_to_push(t_ready_to_push **alst, t_ready_to_push *new);

/* dollar */
char	*dollar(t_parse *parse, char *line);
char	*check_dollr(t_parse *parse, char *line);

/*redirection */
char	*sort_redirection(char *line);

char    *search_replace(char *str, char *org, char *rep);
// void	push_to_struct(t_parse	*parse, char *line);
# endif
