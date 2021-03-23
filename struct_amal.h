#ifndef STRUCT_H
#define STRUCT_H

typedef struct  s_global
{
    char *oldpwd;
    char **commands;
    int	exit_status;
}               t_global;

typedef struct	s_file
{
    char *name;
    char *filetype;
    struct s_file *next;
}				t_file;

typedef struct s_cmds
{
    char **cmd;
    char *type;
    t_file file;
    struct s_cmds *next;
}t_cmds;

# endif