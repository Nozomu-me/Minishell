#ifndef PARSING_H
#define PARSING_H

# include "libft/libft.h"

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

void		ft_lstadd_back(t_cmds **alst, t_cmds *new);
t_cmds		*ft_lstnew(char **v_cmd, char *v_type, char *f_name, char *f_type);
void		affichage(char *line, t_cmds *cmds);
t_cmds		*parser(t_cmds *cmds, char *line);
# endif
