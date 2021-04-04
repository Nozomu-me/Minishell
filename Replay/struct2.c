/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:22:04 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/04 11:59:43 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft/libft.h"
# define GREEN	"\e[1;32m"
# define RED	"\e[0;31m"
# define WHITE	"\033[0m"
# define BLUE "\e[0;34m"

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
    char        **cmd;
    t_type      type;
    t_file      *filename;
}               t_cmds;
/*
t_file		*ft_lstnew_file(char *f_name, int f_type)
{
	t_file *new;

	new = (t_file*)malloc(sizeof(t_file));
	if (new)
	{
		new->filename = f_name;
		new->filetype = f_type;
		new->next = NULL;
	}
	return (new);
}

void		ft_lstadd_back_file(t_file **alst, t_file *new)
{
	t_file *list;

	list = NULL;
	if (!alst || !new)
		return ;
	if (*alst)
	{
		list = *alst;
		while (list && list->next)
			list = list->next;
		list->next = new;
	}
	else
		*alst = new;
}
*/

t_file  *file_lst_new(void *filename, int filetype)
{
    t_file *head;
    head = (t_file *)malloc(sizeof(t_file));
    if (head == NULL)
        return (NULL);
    head->filename = filename;
    head->filetype = filetype;
    head->next = NULL;
    return (head);
}

void    file_lstadd_back(t_file **alst, t_file *new)
{
    t_file      *temp;
    if (!alst || !new)
        return ;
    temp = *alst;
    if (temp != NULL)
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new;
        new->next = NULL;
    }
    else
    {
        *alst = new;
        new->next = NULL;
    }
}

t_cmds		*ft_lstnew(char **v_cmd, int v_type, char *f_name, int f_type)
{
	t_cmds *new;
	new = (t_cmds*)malloc(sizeof(t_cmds));
	new->filename = NULL;
	// new->filename = NULL;
	if (new)
	{
		new->cmd = v_cmd;
		new->type = v_type;
		file_lstadd_back(&new->filename, file_lst_new(f_name, f_type));
		new->filename->next = NULL;
	}
	return (new);
}

int main(int argc, char const *argv[])
{
	t_cmds *cmd;

	char *str = "FUTURE IS LOADING";
	char **splited = ft_split(str, ' ');
	cmd = NULL;
	cmd = ft_lstnew(splited, WRITE, "hello", READ);
	
	printf("CMDS => ");
	while (*cmd->cmd)
	{
		printf("|%s|\t", *cmd->cmd);
		cmd->cmd++;
	}
	printf("\nTYPE => |%d|\n", cmd->type);
	while (cmd->filename)
	{
		printf("FILE ==>  |%s|\t|%d|\n", cmd->filename->filename, cmd->filename->filetype);
		cmd->filename = cmd->filename->next;
	}
	return 0;
}